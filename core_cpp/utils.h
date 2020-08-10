// Copyright 2020 The Konect SpaSpect Authors. All Rights Reserved.
// This file is part of Konect SpaSpect technology.
//  ___            ___              _   
// / __|_ __  __ _/ __|_ __  ___ __| |_ 
// \__ \ '_ \/ _` \__ \ '_ \/ -_) _|  _|
// |___/ .__/\__,_|___/ .__/\___\__|\__|
//     |_|            |_|               
#pragma once

#include <map>
#include <iostream>
#include <string>
#include <cmath>
#include <opencv2/opencv.hpp>
//#include "tensorflow/tensorflow/cc/saved_model/loader.h"
#include <cassert>
#include <array>
#include <algorithm>
//#include <cv.h>
#include "xtensor/xarray.hpp"
#include "xtensor/xio.hpp"
#include <vector>
#include "NumCpp.hpp"
#include <opencv2/core/types.hpp>


using namespace std;
using namespace cv;
/*
namespace Track {
    
    struct locationInfo {
        int boundingBox[4];
        int _3DCoordinate[3];
        int lonlatCoordinate[2];
    };
	class TrackedEntity {
	public:
		float lastUpdate;
		float velocity[2];
		map<int, locationInfo> history;
		void addNext(float time, locationInfo &newLocationInfo) {
			history[time] = newLocationInfo;
			// TODO: Update velocity
		}
		//Computes the prediction of the next bounding box using velocity and current position
		int * estimateBB() {
			//TODO
		}
	};
    
    struct dashboard {
        
    };
    struct DashboardInfo {
    };
    
	float time;

	void updateTime() {
		//TODO
	}

	void track(vector<DashboardInfo::locationInfo*> vec, dashboard &dash) { //ERR HERE --> the vector param is wrong
		//TODO
	}

	void prune(dashboard &dash) {
		//TODO
	}
} //namespace Track

namespace DashboardInfo {
	//Data structure that stores information about the object
	class locationInfo {
	public:
		float coordinate[3];
		float boundingbox[4];
		float latlon[2];
		bool distanced;
		bool masked;
	};

	//Data structure that represents the dashboard
	class dashboard {
	public:

	
		string streamlink;
		string name;
		vector<Track::TrackedEntity*> objects;

		class {
		public:
			float lon_vals[4];
			float lat_vals[4];			
			float lonlat_origin[2];
			int pixelX_vals[4];
			int pixelY_vals[4];
		} calibration;

		bool addTrackedObject(Track::TrackedEntity* object) {
			//TODO: Add checks
			objects.push_back(object);
			return true;
		}

		bool removeTrackedObject(Track::TrackedEntity* object) {
			int obj_pos = find(begin(objects), end(objects), object) - begin(objects);
			//cout<<obj_pos<<endl;
			if (obj_pos != end(objects)) {
				objects.erase(obj_pos);
				return true;
			}
			return false;
		}
	};

} //namespace DashboardInfo
*/
namespace PixelMapper {
class PixelMapperConfig {
public:
  Point2f pixel_array[4];
  Point2f lonlat_array[4];
  //int pixel_array[4][2];
  //int lonlat_array[4][2];

  int lonlat_origin[2];

  float lat_const = 111320;

  Mat M = getPerspectiveTransform(pixel_array, lonlat_array);
  Mat invM = getPerspectiveTransform(lonlat_array, pixel_array);
  
  void setPA(Point2f (&pixel_array)[4]){
      std::copy(begin(this->pixel_array), end(this->pixel_array), begin(pixel_array));
  }
  void setLA(Point2f (&lonlat_array)[4]){
      std::copy(begin(this->lonlat_array), end(this->lonlat_array), begin(lonlat_array));
  }
  void setLO(int (&lonlat_origin)[2]){
      std::copy(begin(this->lonlat_origin), end(this->lonlat_origin), begin(lonlat_origin));
  }
  
  float lon_const = 40075000 * cos(lonlat_origin[0] * M_PI / 180) / 360;
  
/*
  PixelMapperConfig(int (&pixel_array)[4][2], int (&lonlat_array)[4][2], int (&lonlat_origin)[2])
      : std::copy(begin(this->pixel_array), end(this->pixel_array), begin(pixel_array)), 
        std::copy(begin(this->lonlat_array), end(this->lonlat_array), begin(lonlat_array)),
        std::copy(begin(this->lonlat_origin), end(this->lonlat_origin), begin(lonlat_origin)) {
            lon_const = 40075000 * cos(lonlat_origin[0] * M_PI / 180) / 360;
        }
*/
};

// Convert a set of pixel coordinates to lon-lat coordinates
int * pixel_to_lonlat(PixelMapperConfig &config, int pixel_coordinates[][2]) {
	int N = *(&pixel_coordinates + 1) - pixel_coordinates;
    
	int pixel_matrix_transpose[3][N];
	for (int i = 0; i < N; ++i) {
		pixel_matrix_transpose[0][i] = *pixel_coordinates[0];
		pixel_matrix_transpose[1][i] = *pixel_coordinates[1];
		pixel_matrix_transpose[2][i] = 1;
	}

	// https://xtensor-blas.readthedocs.io/en/latest/reference.html#_CPPv4I00EN2xt6linalg3dotEDaRK11xexpressionI1TERK11xexpressionI1OE
	//nc::NdArray<double> cm = {config.M};
	Mat pixel_matrix_transpose_converted = Mat(3, N, CV_32F, pixel_matrix_transpose);
    Mat configM = config.M;
	
	Mat lonlat_matrix_transpose = configM * pixel_matrix_transpose_converted;
	//int lonlat_matrix_transpose[3][N] = cv::hal_ni_gemm32f(configM, pixel_matrix_transpose); //matmul(config.M, pixel_matrix_transpose); //TODO: Matmul implementation
	int lonlat_coordinates[N][2];

	for (int i = 0; i < N; ++i) {
		int scale_factor = lonlat_matrix_transpose.at<float>(3,i);
		lonlat_coordinates[i][0] = lonlat_matrix_transpose.at<float>(0,i) / scale_factor;
		lonlat_coordinates[i][1] = lonlat_matrix_transpose.at<float>(1,i) / scale_factor;
	}

	return *lonlat_coordinates;
}

// Convert a set of lon-lat coordinates to pixel coordinates
int * lonlat_to_pixel(PixelMapperConfig &config, int lonlat_coordinates[][2]) {
	int N = *(&lonlat_coordinates + 1) - lonlat_coordinates;

	int lonlat_matrix_transpose[3][N];
	for (int i = 0; i < N; ++i) {
		lonlat_matrix_transpose[0][i] = *lonlat_coordinates[0];
		lonlat_matrix_transpose[1][i] = *lonlat_coordinates[1];
		lonlat_matrix_transpose[2][i] = 1;
	}

	// https://xtensor-blas.readthedocs.io/en/latest/reference.html#_CPPv4I00EN2xt6linalg3dotEDaRK11xexpressionI1TERK11xexpressionI1OE
	//nc::NdArray<double> cmv = {config.invM};
	
	Mat lonlat_matrix_transpose_converted = Mat(3, N, CV_32F, lonlat_matrix_transpose);
	Mat configINVM = config.invM;
	
	Mat pixel_matrix_transpose = configINVM * lonlat_matrix_transpose_converted;
	//int pixel_matrix_transpose[3][N] = matmul(config.invM, lonlat_matrix_transpose); //TODO: Matmul implementation
	int pixel_coordinates[N][2];

	for (int i = 0; i < N; ++i) {
		int scale_factor = pixel_matrix_transpose.at<float>(3,i);
		pixel_coordinates[i][0] = pixel_matrix_transpose.at<float>(0,i) / scale_factor;
		pixel_coordinates[i][1] = pixel_matrix_transpose.at<float>(1,i) / scale_factor;
	}

	return *pixel_coordinates;
}

// Convert a set of lon-lat coordinates to 3D coordinates
int * lonlat_to_3D(PixelMapperConfig &config, int lonlat_coordinates[][2]) {
  // TODO

  float lon_d = *lonlat_coordinates[0] - config.lonlat_origin[0];
  float lat_d = *lonlat_coordinates[1] - config.lonlat_origin[1];

  float lon_m = lon_d * config.lon_const;
  float lat_m = lat_d * config.lat_const;

  int threeD[3] = {lat_m, lon_m, 0};
  
  return threeD;
}

// Convert a set of 3D coordinates to lon-lat coordinates
int * _3D_to_lonlat(PixelMapperConfig &config, int _3D_coordinates[][3]) {
  float lon_m = *_3D_coordinates[1];
  float lat_m = *_3D_coordinates[0];

  float lon_d = lon_m / config.lon_const;
  float lat_d = lat_m / config.lat_const;

  float lon_coord = lat_d + config.lonlat_origin[0];
  float lat_coord = lon_d + config.lonlat_origin[1];

  int lonlat[2] = {lon_d, lat_d};
  return lonlat;
}

} // namespace PixelMapper
/*
namespace CVOutput {
	namespace utils {
		int computeArea(int box[4]) {
			//TODO
			return 0;
		}
		int computeIntersection(int boxA[4], int boxB[4]) {
			//TODO
			return 0;
		}
		int computeIoU (int boxA[4], int boxB[4]) {
			//TODO
			return 0;
		}
		int computeIoA (int boxA[4], int boxB[4]) {
			//TODO
			return 0;
		}
	} //namespace utils
    
	void predict(cv::Mat &image, dashboard &dash) {
		//Running image through cv model --> person_boxes, scores, classes
		//Running image through mask detector --> face_boxes, masked
		float detection_scores[];
		string detection_classes[];
		int detection_boxes[][4];

		int face_boxes[][4];
		int masked[];

		//Remainder of code is spent filling in values for distanced
		//	and whether objects are masked
		/*
		PSEUDOCODE (needs to be reworked for cpp)
		for(int i = 0 ; i < detection_boxes.size() ; i++){
			if(detection_scores[i] < 0.8)
				break;
			if(!detection_classes[i] == "person")
				continue;

			double box[] = detection_boxes[i];

			double midpoint[2] = {(box[0]+box[2])/2, box[3]};

			double long_lat[] = pm.pixel_to_lonlat(midpoint)[0];
			double coord3D[] = pm.lonlat_to_3D(long_lat);

			//0=unsure, 1=wearing, 2=not wearing
			int wearingMask = 0;

			for(int i = 0; i<face_boxes.size(); ++i){
				double face_box = face_boxes[i];
				double mask = masked[i];
				faceBoxes_subList.insert(face_box);
				boxes_subList.insert(box);
				
				double IOA = utils::computeIOA(face_box, box);
				if(IOA > 0.9){
					if(mask > 0.7)
						wearingMask = 1;
					else if(mask < 0.7)
						wearingMask = 2;
					else
						break;
				}
			}
			lat_vals.insert(long_lat[0])
			lon_vals.insert(long_lat[1])
			X3D_vals.insert(coord3D[0])
			Y3D_vals.insert(coord3D[1])
			Z3D_vals.insert(coord3D[2])
			masked.insert(wearingMask)
		}

		TrackedObject.TrackedObject.track(boxes, X3D_vals, Y3D_vals, Z3D_vals);
		map<string,int>trackedObjects = TrackedObject.TrackedObject.objects;

		for(string key : trackedObjects.keys()){
			trackedObjectsDict[key] = trackedObjects[key].toDict();
		}
		int distanced[] = 1 * sizeof(X3D_vals); //WRONG
		int X3D_vals_len = sizeof(X3D_vals);
		for(int i = 0 ; i < X3D_vals_len ; i++){
			for(int j = 0 ; j < i+1 && X3D_vals_len ; j++){ //check if this is valid
				if(distanced[i] == 0 && distanced[j] ==0){
					continue;
				}
				double distance[] = {X3D_vals[i]-X3D_vals[j], Y3D_vals[i]-Y3D_vals[j], Z3D_vals[i]-Z3D_vals[j]};
				for(int element : distance){
					distance = sqrt(arraySum(pow(element,2.0))); //IS THE SUM RIGHT?
				}
				if(distance < distance_threshold){
					distanced[i] = 0;
					distanced[j] = 0;
				}
				if 1 not in distanced{ //HOW U DO THIS ON CPP???
					break;
				}
			}
		}
		map<string,double,int> predOutput = {"X3D_vals":X3D_vals, "Y3D_vals":Y3D_vals, "Z3D_vals":Z3D_vals,
		"lat_vals":lat_vals, "lon_vals":lon_vals, "masked":masked, "distanced":distanced,
		"tracked":trackedObjectsDict};
		*/
		//return;
/*
	}

}
*/