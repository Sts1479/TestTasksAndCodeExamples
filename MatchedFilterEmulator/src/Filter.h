/*
 * Filter.h
 *
 *  Created on: 9 февр. 2021 г.
 *      Author: user
 */

#ifndef FILTER_H_
#define FILTER_H_
#include "BaseParams.h"
#include "CircBuffer.h"

//#define NF(x) x


class Filter: public BaseParams {
private:
	size_t _Nf;
	float _x_old;
	float _delta = 0.001; // величина, опред. точность получения амплитуды
public:
	CircBuffer<int16_t> Fb; // инициализируем циклический буфер
	// через конструктор передаем размер буфера, который равен окну фильтра
	CircBuffer <int16_t> SinArr;
	CircBuffer <int16_t> CosArr;
	Filter(size_t nf):Fb(nf),SinArr(nf),CosArr(nf){ _Nf = nf;
	InitSinCosArr();}
	virtual ~Filter(){};
	float Matched();
	float AmplVal(const int16_t &x);
	void InitSinCosArr();
};

#endif /* FILTER_H_ */
