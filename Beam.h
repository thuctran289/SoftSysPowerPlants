#include "Point.h"

using namespace std;

class Beam {
	public:
		Point* p1;
		Point* p2;
		double k;
		double r;
		Beam(Point* _p1, Point* p2);
	private: 
};

Beam::Beam(Point* _p1, Point* _p2) {
  p1 = _p1;
  p2 = _p2;
}