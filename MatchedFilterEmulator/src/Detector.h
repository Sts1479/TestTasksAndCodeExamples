/*
 * Detector.h
 *
 *  Created on: 10 февр. 2021 г.
 *      Author: user
 */

#ifndef DETECTOR_H_
#define DETECTOR_H_
#include "BaseParams.h"
#include <stdint.h>
class Detector: public BaseParams {
private:
	uint8_t _packcount = 0;
	//bool _trig = false;
	uint16_t _ncount = 0;
	float _x_old = 0;
	float _s_old = 0;
	float _delta = 0.001;
	bool _flg = true;
	float _highLev = HighLev+0.1;
public:
	Detector(){};
	virtual ~Detector(){};
	uint8_t PackCounter(const float &x, float *y);
	bool AmpPack(const float &x, float *y);
	bool DeriveDetect(const float &s);
};

#endif /* DETECTOR_H_ */
