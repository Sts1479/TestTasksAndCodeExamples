/*
 * BaseParams.h
 *
 *  Created on: 10 февр. 2021 г.
 *      Author: user
 */

#ifndef BASEPARAMS_H_
#define BASEPARAMS_H_
const int ADC_VCC = 3.3; // питание, В
const int ADC_BIT = 4095; // (2^12 - 1)
const int ADC_COEFF = ADC_BIT/ADC_VCC; // 12 бит АЦП, множитель
const int AMP_COEFF = 1/ADC_COEFF;
struct BaseParams {
	const float Fs = 1000000; // частота сэмплирования, Гц
	const float Tpack = 0.02; // длительность пачки импульсов, c
	const float Tper = 3; // расстояние между пачками, с
	const float Fpack = 20000; // частота заполнения, Hz
	const float HighLev = 2.5; // верхний предел,  В
	const float LowLev = 0.2; // нижний предел,  В
};

#endif /* BASEPARAMS_H_ */
