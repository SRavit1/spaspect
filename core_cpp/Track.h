// Copyright 2020 The Konect SpaSpect Authors. All Rights Reserved.
// This file is part of Konect SpaSpect technology.
//  ___            ___              _   
// / __|_ __  __ _/ __|_ __  ___ __| |_ 
// \__ \ '_ \/ _` \__ \ '_ \/ -_) _|  _|
// |___/ .__/\__,_|___/ .__/\___\__|\__|
//     |_|            |_|               
#pragma once

#include <map>
#include <ctime>
#include <vector>

//#include "DashboardInfo.h"

using namespace std;

namespace Track {
	class dashboard;
	//Data structure that location and pixel bounding box information
	struct locationInfo {
		int boundingBox[4];
		int _3DCoordinate[3];
		int lonlatCoordinate[2];
	};

	//Data structure that stores information about the object
	struct entityInfo {
		struct locationInfo location;
		bool distanced;
		bool masked;
	};
	class TrackedEntity {
	public:
		static float currTime;

		float lastUpdate;
		float velocity[2];
		map<int, locationInfo> history;

		TrackedEntity():lastUpdate(currTime), velocity{0, 0}, history(std::map<int, locationInfo>()) {}

		void addNext(float time, locationInfo &newLocationInfo);

		int* estimateBB();
		static void updateTime();

		static void track(dashboard* dash, std::vector<locationInfo*>);
		static void prune(dashboard* dash);
	};
}; // namespace Track