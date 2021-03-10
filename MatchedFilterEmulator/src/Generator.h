/*
 * Generator.h
 *
 *  Created on: 9 февр. 2021 г.
 *      Author: user
 */

#ifndef GENERATOR_H_
#define GENERATOR_H_
#include "BaseParams.h"
/**
 * Класс для эмуляции сигнала с АЦП
 */
class Generator: BaseParams {
private:
	float _td = 1/Fs;
public:
	Generator(){};
	virtual ~Generator(){};
	float GenPackStep ();
	struct GenParams {
		float Abase;
		float Fbase;
		float Arandom;
		float Aconst;
	}GenParams;
};

#endif /* GENERATOR_H_ */
