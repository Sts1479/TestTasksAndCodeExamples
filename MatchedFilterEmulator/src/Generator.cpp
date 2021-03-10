/*
 * Generator.cpp
 *
 *  Created on: 9 февр. 2021 г.
 *      Author: user
 */

#include "Generator.h"
#include <math.h>
#include <cstdlib>
/**
 * \brief Генератор сигнала
 */
float Generator::GenPackStep(){
	static float tt = 0;
	static float tt1 = 0;
	static float tt2 = 0;
	float Xout = 0;
	float RandNoise;
	if (tt1 < Tper){
	    RandNoise = GenParams.Arandom*static_cast<float>(rand())/static_cast<float>(RAND_MAX);
		Xout = GenParams.Abase*sinf(2*tt*M_PI*GenParams.Fbase)+GenParams.Aconst + RandNoise;
	}
	else{
		if (tt2 < Tpack){
		    RandNoise = GenParams.Arandom*static_cast<float>(rand())/static_cast<float>(RAND_MAX);
			Xout = HighLev*sinf(2*M_PI*tt2*Fpack)+GenParams.Abase*sinf(2*tt*M_PI*GenParams.Fbase)+GenParams.Aconst + RandNoise;
			tt2 += _td;
		}
		else{
            tt1 = 0;
            tt2 = 0;
		}
	}
	tt1 += _td;
	tt +=_td;
	return Xout;
}


