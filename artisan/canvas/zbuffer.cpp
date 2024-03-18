#include "zbuffer.h"

namespace artisan_gfx {

ZBuffer::ZBuffer() {}
ZBuffer::ZBuffer(int len, int hgt) : length(len), height(hgt) {
	const double lowest_double = std::numeric_limits<double>::lowest();
	for(int y = 0; y < hgt; y++) {
		std::vector<double> row;
		for (int x = 0; x < len; x++) {
			row.push_back(lowest_double);
		}
		buffer.push_back(row);
	}
}

PPM ZBuffer::DumpToPPM(int mcv) {
	const double lowest_double = std::numeric_limits<double>::lowest();
	const double biggest_double = -1 * std::numeric_limits<double>::lowest();
	double max_z = lowest_double;
	double min_z = biggest_double;
	for(int i = 0; i < buffer.size(); i++) {
		for(int j = 0; j < buffer[0].size(); j++) {
			if(buffer[i][j] == lowest_double) {
				continue;
			}
			if (buffer[i][j] > max_z) {
				max_z = buffer[i][j];
			}
			if (buffer[i][j] < min_z) {
				min_z = buffer[i][j];
			}
		}
	}
	double denominator = max_z - min_z;
	// makes dump all black instead of error if no z variaton;
	if(denominator == 0) {
		denominator = 1;
	}
	PixelGrid pg;
	for(int i = 0; i < buffer.size(); i++) {
		PixelRow pr;
		for(int j = 0; j < buffer[0].size(); j++) {
			double numerator = buffer[i][j] - min_z;
			if(buffer[i][j] == lowest_double) {
				numerator = 0;
			}
			int intensity = (numerator/denominator) * mcv;
			pr.push_back(Pixel{intensity, intensity, intensity});	
		}
		pg.push_back(pr);
	}
	return PPM(pg, mcv);
}

bool ZBuffer::CordInBounds(const int x, const int y) {
	bool xInBounds = x >= 0 && x < length;
	bool yInBounds = y >= 0 && y < height;
	return xInBounds && yInBounds;
}

bool ZBuffer::PutIfGreater(const int x, const int y, const double z) {
	if (!CordInBounds(x,y)) {
		return false;
	}
	if ( z > buffer[y][x] ) {
		buffer[y][x] = z;
		return true;
	}
	return false;
}

void ZBuffer::Set(const int x, const int y, const double z) {
	if(CordInBounds(x,y)) {
		buffer[y][x] = z;
	}
}

double ZBuffer::Get(const int x, const int y) {
	if (!CordInBounds(x,y)) {
		return std::numeric_limits<double>::lowest();
	}
	return buffer.at(y).at(x);
}

int ZBuffer::GetLength() { return length; } 
int ZBuffer::GetHeight() { return height; }


} // namespace artisan_gfx
