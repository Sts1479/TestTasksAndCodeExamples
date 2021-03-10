//============================================================================
// Name        : example2_2.cpp
// Author      : Me
// Version     :
// Copyright   : Your copyright notice
// Description : Hello World in C++, Ansi-style
//============================================================================
#include "draw.hpp"
#include <iostream>
#include <fstream>
using namespace std;

int main()
{
	try
	{
		fstream file;
		file.open("features.dat", fstream::in | ios::binary);
		if (!file.is_open()) throw invalid_argument("Bad file name!");
		auto Feature = TDrawBase::CreateGeom(file);
		Feature->Draw();
	}
	catch (...)
	{
		return EXIT_FAILURE;
	}
	return EXIT_SUCCESS;
}
