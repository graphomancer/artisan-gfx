#pragma once
#include <limits>
#include <set>
#include <vector>
#include <iostream>
#include "artisan/file/ppm.h"

namespace artisan_gfx {

class ZBuffer  {
	int length;
	int height;
	std::vector<std::vector<double>> buffer;
	public:
		ZBuffer(); 
		ZBuffer(int len, int hgt);
		PPM DumpToPPM(int mcv);
		bool CordInBounds(const int x, const int y);
		bool PutIfGreater(const int x, const int y, const double z);
		void Set(const int x, const int y, const double z);
		double Get(const int x, const int y);
		int GetLength();
		int GetHeight();
};

} // namespace artisan_gfx
