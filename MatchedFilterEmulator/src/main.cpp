//============================================================================
// Name        : Tavrida_test.cpp
// Author      : Me
// Version     :
// Copyright   : Your copyright notice
// Description : Hello World in C++, Ansi-style
//============================================================================

#include <iostream>
using namespace std;
#include "CircBuffer.h"
#include "Generator.h"
#include "BaseParams.h"
#include "Detector.h"
#include "Filter.h"
#include <vector>
#include <math.h>

#define PC_EMU // если эмулируем на PC
//..иначе компилируется и исполняется код для контроллера

uint64_t rdtsc(){  // для вычисления быстродействия функций
    unsigned int lo,hi;
    __asm__ __volatile__ ("rdtsc" : "=a" (lo), "=d" (hi));
    return ((uint64_t)hi << 32) | lo;
}


int main() {

#ifdef PC_EMU
	float adcout;
	/**
	 * В BaseParams все базовые значения,
	 * которые обозначены в задании.
	 */
	BaseParams bp;
	Generator gen; // создаем генератор
	/**
	 * Параметры генератора (обязательно!)
	 */
	gen.GenParams.Abase = 0.5; // Амплитуда аналогового сигнала
	gen.GenParams.Fbase = 500; // Частота
	gen.GenParams.Aconst = 1; // Постоянная составляющая
	gen.GenParams.Arandom = 0.05; // макс амплитуда шума
	/**
	 * Число точек на период 20 кГц/размер буфера для окна фильтра.
	 * В данном случае NpackPoints = bp.Fs/ bp.Fpack = 50
	 * bp.Fs = 1 МГц - частота сэмплирования АЦП
	 * bp.Fpack = 20 кГц - частота синусоид, заполняющих пачку
	 */
    int16_t NpackPoints = bp.Fs/bp.Fpack;
	//..создаем объект и инициализурем буфер фильтра
	Filter fl(NpackPoints);
	Detector det;
	uint8_t packNum = 0;
	uint8_t packNum_old = 0;
	float yout_init = 0;
	float *yout = &yout_init;
	/*
	 * Цикл эмуляции. Fs = 1 МГц (частота сэмпл. АЦП)
	 * 10 сек реального времени = 10e6 отсчетов
	 * Генератор выдаст 3 пачки по 20 мс
	 * Тип сигнала: Гармонический сигнал 50 Гц с амплитудой 0.5
	 * + пачки синусоид амлитудой 2.5, длительностью
	 * 20 мс, которые идут через 3 сек.
	 */
    for (int i = 0; i<10e6; i++){
    	adcout = gen.GenPackStep(); //эмулируем сигнал с ADC
    	int pp = adcout*ADC_COEFF;
		fl.Fb.put(pp); // вносим в буфер новое значение
		/* фильтрация и получение амплитудного значения пачки
		 *  гармонических сигналов
		 */
		uint64_t cyc1 = rdtsc();
		float filterout = fl.Matched();
		filterout = filterout/ADC_COEFF;
		//cout << filterout << endl;
		uint64_t cyc2 = rdtsc();
		cout << cyc2 - cyc1 << endl;
		/**
		 * Детектируем пачки и считаем количество пачек в сигнале
		 * используем отфильтрованное менее точное значение
		 * поскольку фильтрация происходит с задержкой и
		 * истинные амплитудные значения пачки появляются не сразу
		 */

		/*
	    if (det.DeriveDetect(filterout)){
	    	cout << "Амплитуда синусоид по производной: " << filterout << endl;
			cout << "Время на момент детектирования, с: " <<i/bp.Fs << endl;
	    }
	    */
		packNum = det.PackCounter(filterout,yout);

		if (packNum != packNum_old){
			cout << "Амплитуда синусоид пачки: " << *yout << endl;
			cout << "Номер пачки: " << (int)packNum << endl;
			cout << "Время на момент детектирования, с: " <<i/bp.Fs << endl;
		}
		packNum_old = packNum;
    }

	cout << "END" << endl;
#else
	// код для микроконтроллера
#endif
    return 0;


}
