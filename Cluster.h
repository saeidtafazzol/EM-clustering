/*
 * Cluster.h
 *
 *  Created on: Nov 2, 2017
 *      Author: potato
 */
#include "Color.h"
#include <vector>
#include <armadillo>


#ifndef CLUSTER_H_
#define CLUSTER_H_

class Cluster {
public:
	Cluster(std::vector<std::vector<Color> > data,int initIndex,int k);
	Cluster();

	virtual ~Cluster();
	Color mean;
	arma::Mat<double> cov;//rgbXrgb
	float p;
	int components;
//	void fillLikelihood(std::vector<std::vector<Color>> data,std::vector<float> & likelihood);
//	void updateCluster(std::vector<std::vector<Color>> data,std::vector<float>likelihood);
	float cal_prob(Color data);


};

#endif /* CLUSTER_H_ */
