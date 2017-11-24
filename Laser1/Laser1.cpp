// LaserBeam.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include <algorithm>
#include <limits>
#include <vector>
#include <iomanip>
#include <fstream>
using namespace std;

#define CARTESIAN_A 5
#define CARTESIAN_B 10

typedef vector<Point> LaserPoints;
typedef LaserPoints::iterator LP_Iter;

int main()
{
	fstream point_file;

	bool top_is_hit;
	LaserPoints mypoints;
	Ellipse myellipse(CARTESIAN_A, CARTESIAN_B);

	// define initial laser vector in reverse
	Point p0 = { 0, -10.0 };
	Point p1 = { 0, 10.1 };
	PP_Vector v0, v;

	cout.precision(6);
	cout << fixed;

	cout << "cartesian ellipse: " << CARTESIAN_A << " x " << CARTESIAN_B << endl << endl;

	cout << "initial vector:";
	v0.set(p0, p1);
	v0.print();
	cout << endl;

	v = v0;

	// main loop
	// reflect the vector
	do
	{
		mypoints.push_back(v.get_start());

		v = myellipse.reflect_laser(v);
		v.flip();

		if (fabs(v.get_start().x) > 0.01f)
		{
			top_is_hit = false;
		}
		else
		{
			if (v.get_start().y > myellipse.top_focus().y)
				top_is_hit = true;
			else
				top_is_hit = false;
		}

	} while (!top_is_hit && mypoints.size() < 500);

	point_file.open("points.txt", ios::out);
	if (!point_file)
	{
		cout << "Cannot open points.txt" << endl;
		exit(EXIT_FAILURE);
	}

	point_file.precision(6);
	point_file << fixed;

	point_file << "cartesian ellipse: " << CARTESIAN_A << " x " << CARTESIAN_B << endl;

	for (LP_Iter iter = mypoints.begin(); iter != mypoints.end(); ++iter)
	{
		point_file << iter->x << ",\t" << iter->y << endl;
	}

	point_file << "Number of reflections: " << mypoints.size() << endl;
	point_file.close();

	cout << "Number of reflections: " << mypoints.size() << endl;

	return 0;
}

