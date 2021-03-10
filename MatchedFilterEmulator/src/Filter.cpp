/*
 * Filter.cpp
 *
 *  Created on: 9 февр. 2021 г.
 *      Author: user
 */

#include "Filter.h"
#include <math.h>
#include <stdio.h>
#include <iostream>
/**
 * \brief согласованный фильтр
 * данные берутся из циклического буфера
 */
float Filter::Matched(){
	int16_t sumCos = 0;
	int16_t sumSin = 0;
	float amp;
	for (size_t n = 0; n < _Nf; n++){
		int16_t x = Fb.get();

		sumSin +=SinArr.get()*x;
		sumCos +=CosArr.get()*x;
	}
	amp = 2*sqrt(sumSin*sumSin + sumCos*sumCos)/_Nf;
	return amp;
}
void Filter::InitSinCosArr(){
	for (size_t n = 0; n < _Nf; n++){
		SinArr.put(sinf(2*M_PI*n*Fpack/Fs)*ADC_COEFF);
		CosArr.put(cosf(2*M_PI*n*Fpack/Fs)*ADC_COEFF);
		}
}


float Filter::AmplVal(const int16_t &x){
	  bool flg = true;
      if (fabs(x - _x_old) > _delta){
    	  flg = false;
      }
      else {
    	  flg = true;
      }
      _x_old = x;
      if (!flg){
    	  return 0;
      }
      return x;
}


