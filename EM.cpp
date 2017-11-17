/*
 * EM.cpp
 *
 *  Created on: Nov 2, 2017
 *      Author: potato
 */

#include "EM.h"
#include "Color.h"


#include <armadillo>


EM::EM(string file,int clusters_) {
	// TODO Auto-generated constructor stub
	image = imread(file,CV_LOAD_IMAGE_COLOR);

	imshow("real",image);
	if(! image.data )                              // Check for invalid input
	{
		//cout <<  "Could not open or find the image" << std::endl ;
	}
	//	means.resize(clusters_);
	//
	//	for(int i = 0;i<means.size();i++){
	//		means[i].makeRandom();
	//	}

	pixels.resize(image.rows);



	for(int i =0;i<image.rows;i++){
		pixels[i].resize(image.cols);

		for(int j = 0;j<image.cols;j++){
			//BGR

			pixels[i][j]=Color(image.at<Vec3b>(i,j)[2],image.at<Vec3b>(i,j)[1],image.at<Vec3b>(i,j)[0]);

		}

	}
	//	Mat result(image.rows,image.cols,CV_8UC3);
	//	//cout<<"2"<<endl;
	//	for(int i = 0;i<image.rows;i++)
	//		for(int j = 0;j<image.cols;j++){
	//			result.at<cv::Vec3b>(i,j)[1] = pixels[i][j].G;
	//			result.at<cv::Vec3b>(i,j)[2] = pixels[i][j].R;
	//			result.at<cv::Vec3b>(i,j)[0] = pixels[i][j].B;
	//		}

	//	imshow("real2",result);


	//clusters

	clusters = new Cluster[clusters_];
	countClusters = clusters_;

	for(int i = 0;i<clusters_;i++)
		clusters[i] = Cluster(pixels,rand()%(pixels.size()*pixels[0].size()),clusters_);

}
void EM::execute(){


	bool converged = false;
	while(!converged){
		//cout<<"not converged"<<endl;
		vector<Color>preVals;
		for(int i = 0;i<countClusters;i++)
			preVals.push_back(clusters[i].mean);

		show(false);
		EStep();
		//cout<<"ESTEP:::::"<<clusters[0].mean.R<<endl;

		MStep();
		//cout<<"MSTE:::::"<<clusters[0].mean.R<<endl;

		show(false);
		//cout<<"SHOW:::::"<<clusters[0].mean.R<<endl;

		converged = true;
		for(int i = 0;i<countClusters;i++)
			if( abs(preVals[i].B - clusters[i].mean.B) + abs(preVals[i].G - clusters[i].mean.G) + abs(preVals[i].R - clusters[i].mean.R) > 10){
				converged=false;
			}
	}
	show(true);
}

EM::~EM() {
	delete[] clusters;
	// TODO Auto-generated destructor stub
}
void EM::EStep(){
	for(int i = 0;i<image.rows;i++){
		for(int j = 0;j<image.cols;j++){
			float sum=0;
			float elements[countClusters];
			for(int k = 0;k<countClusters;k++){
				elements[k] = clusters[k].p * clusters[k].cal_prob(pixels[i][j]);
				sum+=elements[k];
			}

			for(int k = 0;k<countClusters;k++){
				if(sum!=0)
					likelihood[make_pair(make_pair(i,j),k)] = elements[k]/sum;//sum==0 ? :likelihood[make_pair(make_pair(i,j),k)] ;
				//cout<<"LIKLIHOOD::::"<<likelihood[make_pair(make_pair(i,j),k)]<<endl;
			}
		}
	}
}
void EM::MStep(){

	for(int k = 0;k<countClusters;k++){
		float psum = 0;
		float fisum=0;
		Color csum;
		arma::Mat<double> datmat(3,3,arma::fill::zeros);
		arma::Mat<double> meansSub(image.rows*image.cols,3,arma::fill::zeros);
		arma::Mat<double> cov_(3,3,arma::fill::zeros);
		for(int i = 0;i<image.rows;i++){
			for(int j = 0;j<image.cols;j++){
				psum+= likelihood[make_pair(make_pair(i,j),k)];
				fisum += likelihood[make_pair(make_pair(i,j),k)]/(image.rows*image.cols);
				csum=csum+ pixels[i][j]*likelihood[make_pair(make_pair(i,j),k)];
			}
		}
		//cout<<"CSUM::"<<csum.R<<endl;
		//cout<<"PSUM::"<<psum<<endl;
		clusters[k].p = fisum;
		clusters[k].mean = csum/psum;
		for(int i = 0;i<image.rows;i++){
			for(int j = 0;j<image.cols;j++){

				arma::Mat<double> tempmat(1,3,arma::fill::zeros);

				tempmat(0,0) = pixels[i][j].R - clusters[k].mean.R;
				tempmat(0,1) = pixels[i][j].G - clusters[k].mean.G;
				tempmat(0,2) = pixels[i][j].G - clusters[k].mean.B;

				datmat += likelihood[make_pair(make_pair(i,j),k)] * (tempmat.t()*tempmat);

			}
		}

		clusters[k].cov = datmat/psum;

		//		//cout<<clusters[k].cov.get(1,1)<<endl;


	}
}
void EM::show(bool wait){
	Mat result(image.rows,image.cols,CV_8UC3);

	for(int i = 0;i<result.rows;i++)
		for(int j = 0;j<result.cols;j++){
			Color final;
			float sum=0;
			float test=0;
			for(int k = 0;k<countClusters;k++){
				float x = clusters[k].p * clusters[k].cal_prob(pixels[i][j]);
				final = final + clusters[k].mean * x;

				sum+=x;
			}
			final = final/sum;
			result.at<cv::Vec3b>(i,j)[0] = final.B;
			result.at<cv::Vec3b>(i,j)[2] = final.R;
			result.at<cv::Vec3b>(i,j)[1] = final.G;




		}


	for(int i = 0;i<countClusters;i++){
		//cout<<i<<"::::::::::::::"<<clusters[i].mean.R<<","<<clusters[i].mean.G<<","<<clusters[i].mean.B<<endl;
	}



	imshow("result",result);
	if(wait){

		//cout<<"converged"<<endl;
		while(true)
			waitKey(0);

	}
	else
		waitKey(100);
}



