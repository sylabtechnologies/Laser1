#pragma once

// define point to point vector interface
class PP_Vector
{
private:
	Point _start;
	Point _end;
	Polar _polar;
protected:
	void calc_polar();
	void calc_cartesian();
public:
	PP_Vector();
	~PP_Vector();
	void set(Point, Point);
	void set_polar(Point, double, double);
	void print();
	Point get_start();
	Point get_end();
	double get_radius();
	double get_theta();
	void set_average(const PP_Vector&, const PP_Vector&);
	void rotate(double);
	void flip();
};

