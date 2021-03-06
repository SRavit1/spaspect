    // Copyright 2020 The Konect SpaSpect Authors. All Rights Reserved.
// This file is part of Konect SpaSpect technology.
//  ___            ___              _   
// / __|_ __  __ _/ __|_ __  ___ __| |_ 
// \__ \ '_ \/ _` \__ \ '_ \/ -_) _|  _|
// |___/ .__/\__,_|___/ .__/\___\__|\__|
//     |_|            |_|               

#include <algorithm>

#include "CVUtils.h"
#include "Track.h"
#include "DashboardInfo.h"

using namespace std;


bool DashboardInfo::dashboard::add_tracked_object(Track::TrackedEntity* object) {
	//TODO: Add checks
	this->objects.push_back(object);
	return true;
}

bool DashboardInfo::dashboard::remove_tracked_object(Track::TrackedEntity* object) {
	int obj_pos = find(objects.begin(), objects.end(), object) - objects.begin();
	if (obj_pos != objects.size()-1) {
		objects.erase(objects.begin() + obj_pos-1);
		return true;
	}
	return false;
}

void DashboardInfo::dashboard::track(Track::TrackedEntity* object, std::vector<Track::locationInfo*> newObjects) {
	object->updateTime();

	//minimum overlap between tracked object and bbox to count as same object
	float minThresholdIOU = 0.3;

	//making vector containing the indices of elements in newObjects to be added as new objects
	//	(appropriate index is deleted everytime it is added as an update to an existing object)
	vector<int> newBoxes;
	for (int i = 0; i < newObjects.size(); i++) {
		newBoxes.push_back(i);
	}

	//Calculating IoU values between existing Tracked Objects and bboxes in newObjects
	//	Appropriate values are then appended to the map allIOUValues.
	// TODO: TrackedEntity doesn't have support for less than operator
	map<Track::TrackedEntity*, map<int, float>> allIOUValues;
	for (auto currentEntity : this->objects) {
		int* predictedBox = currentEntity->estimateBB();
		map<int, float> IOUValues;
		for (int i = 0; i < newObjects.size(); i++) {
			auto newObject = newObjects[i];
			float IOU = CVUtils::compute_IoU(predictedBox, newObject->boundingBox);
			IOUValues[i] = IOU;
		}

		//sort(IOUValues.begin(), IOUValues.end(), greater<float>());
		allIOUValues[currentEntity] = IOUValues;
	}
	

	while (1) {
		//If there are no remaining TrackedEntity instances that haven't been assigned a new bounding box
		//	all bounding boxes in newObjects which don't have a parent tracked object are assigned a new
		//	TrackedEntity
		if (allIOUValues.begin()->second.empty())
			break;

		//Going through the matrix of all IoU values (intersection between existing tracked objects and 
		//	bounding boxes). Finding the maximum IoU value and corresponding TrackingEntity object.
		Track::TrackedEntity* maximumTracking = allIOUValues.begin()->first;
		Track::locationInfo maximumLocation = maximumTracking->history.end()->second;
		int maximum_newObjects = 0;
		float maximum_iou = 0.;
		for (map<Track::TrackedEntity*, map<int, float>>::iterator i = allIOUValues.begin(); i != allIOUValues.end() ; i++) {
			int maximum_currObject = 0;
			//Must find the maximum value in the current trackedentity
			float iou = 0;
			for (map<int, float>::iterator j = i->second.begin(); j != i->second.end() ; j++) {
				if (j->second > iou) {
					maximum_currObject = j->first;
					iou = j->second;
				}
			}
			
			if (iou>maximum_iou) {
				Track::TrackedEntity* trackingObj = i->first;
				Track::locationInfo objLocation = trackingObj->history.end()->second;

				maximumTracking = trackingObj;
				maximumLocation = objLocation;
				maximum_newObjects = maximum_currObject;
				maximum_iou = iou;
			}
		}
		
		//if the greatest iou left is lower than the minimum threshold
		//	let all remaining bounding boxes to be created as new objects
		if (maximum_iou < minThresholdIOU)
			break;

		//if not, we update the latest box and repeat
		else {
			Track::locationInfo* location = newObjects[maximum_newObjects];
			maximumTracking->addNext(*location);

			//Deleting the row and column of the maximum IoU
			allIOUValues.erase(maximumTracking);
			for (auto trackingKey : allIOUValues)
				trackingKey.second.erase(maximum_newObjects);
			newBoxes.erase(newBoxes.begin()+maximum_newObjects);
		}
	}

    //making a new object
	for (auto newBoxIndex : newBoxes) {
		string name1 = "randomID"; //generate random ID
		string label = "person";
		Track::locationInfo* newLocationInfo = newObjects[newBoxIndex];
		
		Track::TrackedEntity* newObject = new Track::TrackedEntity();
		newObject->addNext(*newLocationInfo);
		add_tracked_object(newObject);
	}

	//Pruning objects that haven't been accessed in past 5 frames
	std::vector<Track::TrackedEntity*> to_delete;
	int updateThreshold = 5;
	
	for(auto tracked_key : this->objects){
    	int tracked_key_pos = find(this->objects.begin(), this->objects.end(), tracked_key) - this->objects.begin();
    	auto tracked = this->objects[tracked_key_pos];
    	if(tracked_key->currTime - tracked->lastUpdate > updateThreshold){
        	to_delete.push_back(tracked_key);
    	}
	}
	for(auto delete_i : to_delete){
    	int delete_i_pos = find(this->objects.begin(), this->objects.end(), delete_i)- this->objects.begin();
    	this->objects.erase(this->objects.begin() + delete_i_pos-1);
	}

	return;
}