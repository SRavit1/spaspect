// Copyright 2020 The Konect SpaSpect Authors. All Rights Reserved.
//
// This file is part of Konect SpaSpect technology.

#include <iostream>
#include <string>
#include <opencv2/opencv.hpp>

#include "PixelMapper.h"
#include "TrackedObject.h"
#include "utils.h"
using namespace std;
// THERE IS A WAY TO ADD FIREBASE

//Ravit Uncomment:
//cred = credentials.Certificate('/home/ravit/Downloads/spaspect-dashboard-firebase-adminsdk-bip9h-4407f5fe40.json')

//Santript Uncomment:
string cred = credentials.Certificate('/home/santript/ImportantProjects/Files/spaspect-dashboard-firebase-adminsdk-bip9h-8efff333dc.json');
firebase_admin.initialize_app(cred);

string root_dir = "/home/santript/ImportantProjects/spaspect/visualization";
db = firestore.client() //WHAT TYPE IS THIS?
string dashboard = "d3c4fd41-8892-453b-bc00-64d1f494284b";

int main() {
    map<string,double,int> dashboardDoc = db.collection(u'dashboards').document(dashboard);
	map<string,double,int> dashboardInfo = dashboardDoc.get().to_dict();

	//streamLink = dashboardInfo["streamlink"]

	string streamLink = "/home/santript/ImportantProjects/Files/NewClearPeople.mp4";


	// Ravit Uncomment:
	//imagePath = "/home/ravit/Pictures/Frame.jpg"
	//streamLink = "/home/ravit/Downloads/TimesSquare.mp4"

	// Santript Uncomment:
	string imagePath = "/home/santript/ImportantProjects/Frames/Frame.jpg";
	//streamLink = "/home/santript/ImportantProjects/Files/TimesSquare2.mp4"

	void cap = cv2.VideoCapture(); //ARE THESE VOID?
	void cap.open(streamLink);

	map<string,double,int> calibration = dashboardInfo["calibration"];
	map<string,double,int> dashboardOutput = dashboardInfo["output"];
	double pixelX[] = calibration["pixelX_vals"];
	double pixelY[] = calibration["pixelY_vals"];
	int pixelXLen = sizeof(pixelX);
	for(int i = 0 ; i < pixelXLen ; i++){
    	double pixel_array[] = {pixelX[i], pixelY[i]};
	}
	double lat[] = calibration["lat_vals"];
	double lon[] = calibration["lon_vals"];
	int latLen = sizeof(lat);
	for(int i = 0 ; i < latLen ; i++){
    	double lonlat_array[] = {lat[i], lon[i};
	}
	map<string,double,int> pm = PixelMapper.PixelMapper(pixel_array, lonlat_array, calibration["lonlat_origin"]);

	bool video = false;
	double frame_rate = cv2.CAP_PROP_FPS;
	int frame_index = 0;
	
	for(int x = 0 ; x < 10 ; x++){
    	cap.read();
	}
	
	while(true){
    	cout<<"FRAME "<<frame_index<<"##############"<<endl;
    	bool read, imageX = cap.read(); //IDK BOUT THIS
		if (!read){
    		cout<<"END"<<endl;
    		break;
		}

		bool cv2.imwrite(imagePath, imagX);
		map<string,double,int> output = pred.predict(imagePath);

		map<string,double,int> predOutput = utils.makeVisualizationOutput(pm, output);

		//print("predOutput:",predOutput)
		//print(predOutput["tracked"])

		        
		frame_index += 1;

		dashboardOutput["X3D_vals"] = predOutput["X3D_vals"];
		dashboardOutput["Y3D_vals"] = predOutput["Y3D_vals"];
		dashboardOutput["Z3D_vals"] = predOutput["Z3D_vals"];
		dashboardOutput["lat_vals"] = predOutput["lat_vals"];
		dashboardOutput["lon_vals"] = predOutput["lon_vals"];
		dashboardOutput["masked"] = predOutput["masked"];
		dashboardOutput["distanced"] = predOutput["distanced"];
		dashboardOutput["tracked"] = predOutput["tracked"];
        
		cout<<"New Dashboard: "<<dashboardInfo<<endl;
        
		dashboardDoc.set(dashboardInfo);
		/*
		for tracked_obj in predOutput["tracked"].values():
			id = float(tracked_obj["name"])
			color = (int((id%1)*255), int((id*100%1)*255), int((id*10000%1)*255))
			current_pos = tracked_obj["history"][str(tracked_obj["lastUpdate"])]
			current_pos = [int(elem) for elem in current_pos]
			image = cv2.rectangle(image, (current_pos[0], current_pos[1]), (current_pos[2], current_pos[3]), color, 2)
			for i in range(len(list(tracked_obj["history"]))-1):
				pos_c = tracked_obj["history"][list(tracked_obj["history"])[i]]
				pos_n = tracked_obj["history"][list(tracked_obj["history"])[i+1]]

				midpoint_c = (int((pos_c[0] + pos_c[2])/2),int((pos_c[1] + pos_c[3])/2))
				midpoint_n = (int((pos_n[0] + pos_n[2])/2),int((pos_n[1] + pos_n[3])/2))

				image = cv2.line(image, midpoint_c, midpoint_n, color, 2)
		cv2.imwrite("/home/santript/ImportantProjects/Frames/frame" + str(frame_index) + ".jpg", image)	
		*/
		return 0;
	}
	sys.exit(main(dashboard));
}