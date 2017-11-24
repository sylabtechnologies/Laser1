#pragma once

// define cartesian ellipse (a, b), a < b
class Ellipse
{
private:
	double _a;
	double _b;
	double _c;
	Point  _ftop;
	Point  _fbottom;

public:
	Ellipse(double, double);
	~Ellipse();
	bool it_fits(Point);
	Point top_focus();
	Point bottom_focus();
	PP_Vector reflect_laser(const PP_Vector&);
	PP_Vector intersect(PP_Vector vec);
};

