#include "stdafx.h"
#include "PP_Vector.h"

// define point to point vector operations

PP_Vector::PP_Vector()
{
	// redefine vector initialization later as necessary
	_start.x = 0.0f;
	_start.y = 0.0f;
	_end.x = 0.0f;
	_end.y = 0.0f;
	_polar.rad = 0.0f;
	_polar.theta = 0.0f;
}

PP_Vector::~PP_Vector()
{
}

void PP_Vector::set(Point start, Point end)
{
	_start = start;
	_end = end;

	calc_polar();
}

void PP_Vector::set_polar(Point start, double radius, double theta)
{
	_start = start;
	_polar.rad = radius;
	_polar.theta = theta;

	calc_cartesian();
}

void PP_Vector::calc_polar()
{
	double dx, dy;

	dx = _end.x - _start.x;
	dy = _end.y - _start.y;

	_polar.rad = sqrt(dx*dx + dy*dy);

	dx = dx / _polar.rad;
	dy = dy / _polar.rad;

	if (dy >= 0)
	{
		if (dy < 0.5f)
		{
			_polar.theta = asin(dy);
			if (dx < 0.0f) _polar.theta = PI - _polar.theta;
		}
		else
			_polar.theta = acos(dx);

	}
	else
	{
		if (dy > -0.5f)
		{
			_polar.theta = asin(dy);
			if (dx < 0.0f) _polar.theta = -PI - _polar.theta;
		}
		else
			_polar.theta = -acos(dx);

	}
}

void PP_Vector::calc_cartesian()
{
	_end.x = _start.x + _polar.rad*cos(_polar.theta);
	_end.y = _start.y + _polar.rad*sin(_polar.theta);
}

void PP_Vector::print()
{
	std::cout << std::endl << "vector start:\t" << _start.x << ", " << _start.y << std::endl;
	std::cout << "vector radius:\t" << _polar.rad << std::endl;
	std::cout << "vector theta:\t" << _polar.theta * 180 / PI << "'" << std::endl;

}

// return start of the vector
Point PP_Vector::get_start()
{
	return _start;
}

// return end of the vector
Point PP_Vector::get_end()
{
	return _end;
}

// set the vector to the average of two vectors in polar coordinates
void PP_Vector::set_average(const PP_Vector& vec1, const PP_Vector& vec2)
{
	_start = vec1._start;

	_polar.theta = 0.5f*(vec1._polar.theta + vec2._polar.theta);
	_polar.rad = 0.5f*(vec1._polar.rad + vec2._polar.rad);

	calc_cartesian();
}

// rotate by angle in polar coordinates
void PP_Vector::rotate(double theangle)
{
	_polar.theta += theangle;

	// FIT TO -PI +PI INTERVAL
	if (_polar.theta > PI)
		_polar.theta = _polar.theta - 2 * PI;

	if (_polar.theta < -PI)
		_polar.theta = _polar.theta + 2 * PI;

	calc_cartesian();
}

double PP_Vector::get_radius()
{
	return _polar.rad;
}

double PP_Vector::get_theta()
{
	return _polar.theta;
}

// exchange start and end
void PP_Vector::flip()
{
	Point temp;

	temp = _start;
	_start = _end;
	_end = temp;

	if (_polar.theta == PI)
		_polar.theta = 0;
	else if (_polar.theta == 0)
		_polar.theta = PI;
	else if (_polar.theta > 0)
		_polar.theta -= PI;
	else if (_polar.theta < 0)
		_polar.theta += PI;

}
