#include "stdafx.h"
#include "Ellipse.h"

Ellipse::Ellipse(double x_width, double y_width) : _a(x_width), _b(y_width)
{
	// compute distance to focal points, assume b > a
	_c = sqrt(_b*_b - _a*_a);

	_ftop.x = 0.0f;
	_ftop.y = _c;

	_fbottom.x = 0.0f;
	_fbottom.y = -_c;
}

Ellipse::~Ellipse()
{
}

// test if the point is on the ellipse
bool Ellipse::it_fits(Point p)
{
	double result, x1, y1;

	x1 = p.x / _a;
	y1 = p.y / _b;
	result = x1*x1 + y1*y1 - 1.0f;

	return (result < TOLERANCE) ? true : false;
}

// return focus y > 0, b > a
Point Ellipse::top_focus()
{
	return _ftop;
}

// return focus y < 0, b > a
Point Ellipse::bottom_focus()
{
	return _fbottom;
}

// reflect the laser beam
PP_Vector Ellipse::reflect_laser(const PP_Vector& laser)
{
	PP_Vector myvector;

	myvector = laser;

	// test it fits
	if (!it_fits(myvector.get_start()))
	{
		std::cout << "Warning! This vector out of bounds!" << std::endl;
		myvector.print();
	}

	// construct vectors to foci
	PP_Vector f1, f2, average;
	f1.set(myvector.get_start(), _ftop);
	f2.set(myvector.get_start(), _fbottom);

	// find the  normal to the surface
	average.set_average(f1, f2);
	// find the angle
	double theangle = average.get_theta() - myvector.get_theta();
	// rotate the result by 2*difference
	PP_Vector result;
	result = myvector;
	result.rotate(2 * theangle);

	// return  the intersection to the ellipse

	return intersect(result);
}

// intersect ellipse and vector
PP_Vector Ellipse::intersect(PP_Vector vec)
{
	double newrad, bsquare, asquare;
	double mysine, mycos;
	Point mystart;
	PP_Vector result;

	asquare = _a*_a;
	bsquare = _b*_b;

	mysine = sin(vec.get_theta());
	mycos = cos(vec.get_theta());

	mystart = vec.get_start();

	newrad = -2.0f*(bsquare*mystart.x*mycos + asquare*mystart.y*mysine);
	newrad = newrad / (bsquare*mycos*mycos + asquare*mysine*mysine);

	result.set_polar(mystart, newrad, vec.get_theta());

	return result;
}
