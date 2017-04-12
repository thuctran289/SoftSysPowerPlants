#include "Point.h"

using namespace std;

class Beam {
	public:
		Point* p1;
		Point* p2;
		double k;
		double r;
		short beamType;
		Beam(Point* _p1, Point* _p2, double _r);
		Beam(Point* _p1, Point* _p2, double _r, short _beamType);
	private: 
};

Beam::Beam(Point* _p1, Point* _p2, double _r) {
  p1 = _p1;
  p2 = _p2;
  k = 100000.0;
  r = _r;
  beamType = 0;

}

Beam::Beam(Point* _p1, Point* _p2, double _r, short _beamType)
{
	p1 = _p1;
	p2 = _p2;
	k = 100000.0;
	r = _r;
	beamType = _beamType;
}