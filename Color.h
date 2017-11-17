/*
 * ColorMean.h
 *
 *  Created on: Oct 25, 2017
 *      Author: potato
 */

#ifndef COLORMEAN_H_
#define COLORMEAN_H_

class Color {
public:
	double R;
	double G;
	double B;
	Color();
	Color(double R_,double G_,double B_);
	Color operator*(double oth);
	Color operator+(const Color & oth);
	Color operator/(double oth);
	void makeRandom();
	double colorDistance(Color oth);


	virtual ~Color();
};

#endif /* COLORMEAN_H_ */
