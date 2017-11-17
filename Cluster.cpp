/*
 * Cluster.cpp
 *
 *  Created on: Nov 2, 2017
 *      Author: potato
 */

#include "Cluster.h"
#include <stdlib.h>
#include <vector>
#include <math.h>
#include <iostream>
#include <armadillo>





using namespace arma;
using namespace std;
Cluster::Cluster(vector<vector<Color> > data,int initIndex,int k) {

	mean = Color(data[initIndex/data[0].size()][initIndex%data[0].size()]);
	cout<<mean.R<<endl;
	cout<<mean.G<<endl;
	cout<<mean.B<<endl;



	cov = Mat<double>(3,3,fill::zeros);

	double Rmean=0,Gmean=0,Bmean=0,Rsum=0,Gsum=0,Bsum=0;

	for(int i = 0;i<data.size();i++){
		for(int j = 0;j<data[i].size();j++){
			Rsum+=data[i][j].R;
			Gsum+=data[i][j].G;
			Bsum+=data[i][j].B;
		}
	}



	Rmean=Rsum/(data.size()*data[0].size());
	Gmean=Gsum/(data.size()*data[0].size());
	Rmean=Bsum/(data.size()*data[0].size());


	Mat<double> datmat(data.size()*data[0].size(),3,fill::zeros);
	Mat<double> meansSub(data.size()*data[0].size(),3,fill::zeros);
	for(int i = 0;i<data.size();i++){
		for(int j = 0;j<data[i].size();j++){
			meansSub(i*data[i].size()+j,0)=Rmean;
			meansSub(i*data[i].size()+j,1)=Gmean;
			meansSub(i*data[i].size()+j,2)=Bmean;

			datmat(i*data[i].size()+j,0)=data[i][j].R;
			datmat(i*data[i].size()+j,1)=data[i][j].G;
			datmat(i*data[i].size()+j,2)=data[i][j].B;
		}

	}

	datmat = datmat-meansSub;



	cov = datmat.t()*datmat/(data.size()*data[0].size());
	cov.print();
	p = 1.0/k;

	components=k;


	// TODO Auto-generated constructor stub

}
Cluster::Cluster() {

}

Cluster::~Cluster() {
	// TODO Auto-generated destructor stub
}


float Cluster::cal_prob(Color data){
	Mat<double> temp(1,3,fill::zeros);
	temp(0,0)=data.R-mean.R;
	temp(0,1)=data.G-mean.G;
	temp(0,2)=data.B-mean.B;
	double d = det(cov);
	Mat<double> s = (temp*cov.i()*temp.t());
	cout<<"CALPROB::::::"<<1/sqrt(pow(2*M_PI,3)*d)*exp(-0.5*s(0,0))<<endl;
	return 1/sqrt(pow(2*M_PI,3)*d)*exp(-0.5*s(0,0));



}
