/*
 * draw.hpp
 *
 *  Created on: 27 янв. 2021 г.
 *      Author: user
 */

#ifndef DRAW_HPP_
#define DRAW_HPP_

#include <stdio.h>
#include <iostream>
#include <stdexcept>
#include <memory>

using namespace std;

// 4ая задача ------------------------------------------------------------------

struct TPoint
{
	double X;
    double Y;
};

enum FeatureType {eUnknown, eCircle, eTriangle, eSquare};

// Базовый класс
class TDrawBase
{
	public:
		virtual ~TDrawBase()= default;
		virtual void Draw() = 0;
		static unique_ptr<TDrawBase> CreateGeom(istream &FileData);
};

// Круг
class TCircle: public TDrawBase
{
	public:
		TCircle(istream &FileData)
		{
			FileData.read(reinterpret_cast<char*>(&Geometry), sizeof(TCircleData));
			if (FileData.gcount() != sizeof(TCircleData))
				throw invalid_argument("Bad data!");
		}
		void Draw() override
		{
			// Рисуем по Geometry
			// . . .
		}

	private:
		struct TCircleData
		{
			TPoint Center;      // Координата центра
			double Raduis;      // Радиус
		};

		TCircleData Geometry;
};

// Квадрат / прямоугольник
class TSquare: public TDrawBase
{
	public:
		TSquare(istream &FileData)
		{
			FileData.read(reinterpret_cast<char*>(&Geometry), sizeof(TSquareData));
			if (FileData.gcount() != sizeof(TSquareData))
				throw invalid_argument("Bad data!");
		}
		void Draw() override
		{
			// Рисуем по Geometry
			// . . .
		}

	private:
		struct TSquareData
		{
			TPoint LeftUp;      // Координата верхней левой грани
			TPoint RightDown;   // Координата правой нижней грани
		};

		TSquareData Geometry;
};

// Треугольник
class TTriangle: public TDrawBase
{
	public:
		TTriangle(istream &FileData)
		{
			FileData.read(reinterpret_cast<char*>(&Geometry), sizeof(TTriangleData));
			if (FileData.gcount() != sizeof(TTriangleData))
				throw invalid_argument("Bad data!");
		}
		void Draw() override
		{
			// Рисуем по Geometry
			// . . .
		}

	private:
		struct TTriangleData
		{
			TPoint VertexA;      // Координата вершины A
			TPoint VertexB;      // Координата вершины B
			TPoint VertexC;      // Координата вершины C
		};

		TTriangleData Geometry;
};

unique_ptr<TDrawBase> TDrawBase::CreateGeom(istream &FileData)
{
    FeatureType type;
	FileData.read(reinterpret_cast<char*>(&type), sizeof(FeatureType));
	if (FileData.gcount() != sizeof(FeatureType))
		throw invalid_argument("Bad data!");
	switch (type)
	{
		case eCircle: return make_unique<TCircle>(FileData);
		case eTriangle: return make_unique<TTriangle>(FileData);
		case eSquare: return make_unique<TSquare>(FileData);
		default: throw invalid_argument("Unk geometry id!");
	}
}




#endif /* DRAW_HPP_ */
