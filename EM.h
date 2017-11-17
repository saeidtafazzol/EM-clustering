/*
 * EM.h

 *
 *  Created on: Nov 2, 2017
 *      Author: potato
 */


#include <opencv2/core/core.hpp>
#include <opencv2/highgui/highgui.hpp>
#include "Color.h"
#include "Cluster.h"
#include <iostream>
#include <vector>
#include <map>

using namespace std;
using namespace cv;
#ifndef EM_H_
#define EM_H_

class EM {
public:
	EM(string file,int clusters_);
	virtual ~EM();
	void execute();
private:
	void EStep();
	void MStep();
	void show(bool wait);
	vector<vector<Color> > pixels;
	Mat image;
	Cluster * clusters;
	int countClusters;
	map<pair<pair<int,int>,int >,float > likelihood;


};

#endif /* EM_H_ */
