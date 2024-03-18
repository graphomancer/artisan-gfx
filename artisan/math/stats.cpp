#include "stats.h"
#include <random>
#include <cstdlib>

namespace artisan_gfx {

double RandomDouble(double min, double max) {
				/*static std::uniform_real_distribution<double> distribution(min, max);
				static std::mt19937 generator;
				return distribution(generator);*/
				double r =  ((double) rand()) / RAND_MAX;
				return min + (max - min) * r;
}

} // namespace artisan_gfx
