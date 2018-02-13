/*
 * main.cpp
 *
 *  Created on: Oct 25, 2017
 *      Author: potato
 */
#include <stdlib.h>
#include <time.h>
#include "EM.h"
int main(){
	srand(time(NULL));
	EM("Lenna.png",2).execute();


}
