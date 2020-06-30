import numpy as np
import math
import cv2
import json

"""
Create an object for converting pixels to geographic coordinates,
using four points with known locations which form a quadrilteral in both planes
"""
class PixelMapper(object):
	def __init__(self, pixel_array, lonlat_array, lonlat_origin):
		pixel_array = np.array(pixel_array)
		lonlat_array = np.array(lonlat_array)

		assert pixel_array.shape==(4,2), "Need (4,2) input array"
		assert lonlat_array.shape==(4,2), "Need (4,2) input array"
		self.M = cv2.getPerspectiveTransform(np.float32(pixel_array),np.float32(lonlat_array))
		self.invM = cv2.getPerspectiveTransform(np.float32(lonlat_array),np.float32(pixel_array))

		self.lonlat_origin = lonlat_origin
		self.lon_const = 40075000 * math.cos(lonlat_origin[0]*math.pi/180) / 360
		self.lat_const = 111320
	
	@classmethod
	def fromfile(cls, filename):
		with open(filename, "r") as f:
			config = json.loads(f.read())
			info = cls(config["pixel"], config["lonlat"], config["lonlat_origin"])
			return info
        
	def pixel_to_lonlat(self, pixel):
		"""
		Convert a set of pixel coordinates to lon-lat coordinates
		"""
		if type(pixel) != np.ndarray:
			pixel = np.array(pixel).reshape(1,2)
		assert pixel.shape[1]==2, "Need (N,2) input array" 
		pixel = np.concatenate([pixel, np.ones((pixel.shape[0],1))], axis=1)
		lonlat = np.dot(self.M,pixel.T)

		return (lonlat[:2,:]/lonlat[2,:]).T.tolist()
    
	def lonlat_to_pixel(self, lonlat):
		"""
		Convert a set of lon-lat coordinates to pixel coordinates
		"""
		if type(lonlat) != np.ndarray:
			lonlat = np.array(lonlat).reshape(1,2)
		assert lonlat.shape[1]==2, "Need (N,2) input array" 
		lonlat = np.concatenate([lonlat, np.ones((lonlat.shape[0],1))], axis=1)
		pixel = np.dot(self.invM,lonlat.T)

		return (pixel[:2,:]/pixel[2,:]).T.tolist()

	def lonlat_to_3D(self, lonlat):
		"""
		Convert a set of lon-lat coordinates to 3D coordinates
		"""
		lon_d = lonlat[0] - self.lonlat_origin[0]
		lat_d = lonlat[1] - self.lonlat_origin[1]

		lon_m = lon_d * self.lon_const
		lat_m = lat_d * self.lat_const

		return [lat_m, lon_m, 0]

	def _3D_to_lonlat(self, _coords3D):
		"""
		Convert a set of 3D coordinates to lon-lat coordinates
		"""
		lon_m = _coords3d[1]
		lat_m = _coords3d[0]
		
		lon_d = lon_m / self.lon_const
		lat_d = lat_m / self.lat_const
		
		lon_coord = lat_d + self.lonlat_origin[0]
		lat_coord = lon_d + self.lonlat_origin[1]
		
		return [lon_d, lat_d]

def makeVisualizationOutput(pm, output, distance_threshold=2, score_threshold = 0.80):
	coords3D = []
	long_lats = []
	for i in range(len(output["boxes"])):
		if (output["scores"][i] < score_threshold):
			break
		box = output["boxes"][i]
		
		midpoint = [int((box[0]+box[2])/2), box[3]]

		long_lat = pm.pixel_to_lonlat(midpoint)[0]
		coord3D = pm.lonlat_to_3D(long_lat)

		long_lats.append(long_lat)
		coords3D.append(coord3D)

	if (coords3D != []):
		long_lats = np.swapaxes(np.asarray(long_lats), 0, 1).tolist()
		coords3D = np.asarray(coords3D).tolist()

	safe = [1] * len(coords3D)
	for i in range(len(coords3D)):
		for j in range(i+1, len(coords3D)):
			if (safe[i] == 0 and safe[j] == 0):
				continue
			assert len(coords3D[i]) == len(coords3D[j])
			distance = math.sqrt(sum(e**2 for e in [coords3D[i][k]-coords3D[j][k] for k in range(2)]))
			if (distance < distance_threshold):
				safe[i] = 0
				safe[j] = 0
	
	predOutput = {"3DCoordinates":coords3D, "lat-long":long_lats, "safe":safe}
	return predOutput
