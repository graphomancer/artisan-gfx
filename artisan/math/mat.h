#pragma once
#include "vec.h"
#include <optional>
#include <cmath>
#include <vector>
#include <array>
#include <initializer_list>
#include <stdexcept>
#include "artisan/triangle/triangle.h"
#include "artisan/triangle/vertex.h"

namespace artisan_gfx {

template <class G, unsigned int R, unsigned int C>
class Mat {
	std::array<Vec<G,C>,R> elems;
public:
	Mat() = default;

	Mat(std::array<std::array<G,C>,R> input) {
		for (unsigned int i = 0; i < R; i++) {
			elems[i] = Vec<G,C>(input[i]);
		}
	}

	G RowMajor(int i) const {
		return elems[i / C][i % C];
	}

	void SetRowMajor(int i, G v) {
		Vec<G,C>& elemsRow = elems[i / C];
		elemsRow[i % C] = v;
	}

	Vec<G,C> operator[] (int i) const {
		return elems[i];
	}

	Vec<G,C>& operator[] (int i) {
		return elems[i];
	}

	Vec<G,R> operator* (Vec<G,C> iv) const {
		std::array<G,R> out;
		for (unsigned int r = 0; r < R; r++) {
			out[r] = elems[r] * iv;
		}
		return out;
	}

	Vertex<G,R> operator* (Vertex<G,R> ivx) const {
		return Vertex<G,R>(
			*this * ivx.GetCords(),
			ivx.GetProperties()
		);
	}

	Mat<G, R, C> operator*(G v) const {
		std::array<std::array<G,C>,R> mdata;
		for (unsigned int r =0; r < R; r++) {
			for (unsigned int c = 0; c < C; c++) {
				mdata[r][c] = elems[r][c] * v;
			}
		}
		return Mat<G,R,C>(mdata);
	}

	Mat<G, R, C> operator/(G v) const {
		std::array<std::array<G,C>,R> mdata;
		for (unsigned int r =0; r < R; r++) {
			for (unsigned int c = 0; c < C; c++) {
				mdata[r][c] = elems[r][c] / v;
			}
		}
		return Mat<G,R,C>(mdata);
	}

	bool operator==(Mat<G, R, C> other) const {
		for (unsigned int r = 0; r < R; r++) {
			for (unsigned int c = 0; c < C; c++) {
				if(other[r][c] != elems[r][c]) {
					return false;
				}
			}
		}
		return true;
	}

	Mat<G,C,R> transpose() const {
		std::array<std::array<G,R>,C> tdata;
		for (unsigned int r = 0; r < R; r++) {
			for (unsigned int c = 0; c < C; c++) {
				tdata[c][r] = elems[r][c];
			}	
		}
		return Mat<G,C,R>(tdata);
	}

	template <unsigned int L>
	Mat<G,R,L> operator* (Mat<G,C,L>& im) const {
		std::array<std::array<G,L>,R> mdata;
		Mat<G,L,C> imTrans = im.transpose();
		for(unsigned int r = 0; r < R; r++) {
			for(unsigned int l = 0; l < L; l++) {
				mdata[r][l] = elems[r] * imTrans[l];
			}
		}	
		return Mat<G,R,L>(mdata);
	}

	Triangle<Vertex<G, C>> operator* (Triangle<Vertex<G, C>> t) const {
		return Triangle<Vertex<G, C>>(
				*this * t.GetA(),
				*this * t.GetB(),
				*this * t.GetC()
			);
	}

};
template <class G, unsigned int D>
Mat<G,D,D> identity() {
	std::array<std::array<G,D>,D> elems;
	for(int i = 0; i < D; i++) {
		for(int j = 0; j < D; j++) {
			elems[i][j] = 0;
		}
		elems[i][i] = 1;
	}
	return Mat<G,D,D>(elems);
}

typedef Mat<double, 4, 4> Mat4;

std::optional<Mat4> Mat4Inverse(Mat4 m);

} // namespace artisan_gfx
