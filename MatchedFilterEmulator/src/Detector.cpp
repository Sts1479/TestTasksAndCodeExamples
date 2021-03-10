/*
 * Detector.cpp
 *
 *  Created on: 10 февр. 2021 г.
 *      Author: user
 */

#include "Detector.h"
#include <math.h>
#include <iostream>

/**
 * \brief счетчик пакетов импульсов
 */
uint8_t Detector::PackCounter(const float &x, float *y){
	if (x <= _highLev and x >= LowLev ){
		_ncount++;

		//..спустя 1/8 длительности всей пачки амплитуда постоянная
		if (_ncount/Fs == Tpack/8){
			memcpy(y,&x,sizeof(float));
		}

		if (_ncount/Fs >= Tpack){
			_packcount++;
			_ncount = 0;
		}

	}
	else {
		_ncount = 0;
	}
	return _packcount;
}

bool Detector::DeriveDetect(const float &s){
	if (fabs(s - _s_old) > 0.01) {
	    _s_old = s;
		return true;
	}
    _s_old = s;
	return false;
}
