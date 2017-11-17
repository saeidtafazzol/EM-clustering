/*
 * Color.cpp
 *
 *  Created on: Oct 25, 2017
 *      Author: potato
 */

#include "Color.h"
#include <stdlib.h>
#include <math.h>
Color::Color():R(0),B(0),G(0) {

	// TODO Auto-generated constructor stub
}

Color::Color(double R_,double G_,double B_):R(R_),B(B_),G(G_){

}

Color Color::operator*(double oth){
	Color * ans = new Color();
	ans->R=R*oth;
	ans->B=B*oth;
	ans->G=G*oth;
	return *ans;
}
Color Color::operator/(double oth){
	Color * ans = new Color();
	ans->R=R/oth;
	ans->B=B/oth;
	ans->G=G/oth;
	return *ans;
}
Color Color::operator+(const Color & oth){
	Color * ans = new Color();
	ans->R=R+oth.R;
	ans->B=B+oth.B;
	ans->G=G+oth.G;
	return *ans;
}
void Color::makeRandom(){
	R=rand()%256;
	G=rand()%256;
	B=rand()%256;
}


double Color::colorDistance(Color oth){
	return sqrt(pow(R - oth.R,2)+pow(G - oth.G,2)+pow(B - oth.B,2));
}


Color::~Color() {
	// TODO Auto-generated destructor stub
}

