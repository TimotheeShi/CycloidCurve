#pragma once
#include <math.h>
#include <vector>
#include <utility>
#include "Preprocess.h"
#include "PointInspection.h"

class CycloidGear
{
public:
	CycloidGear() = default;
	double CalTheoreticalCurve(double theta) {
		double x0, y0;
		x0 = Rz * (sin(theta) - k1 / Zb * sin(Zb * theta));
		y0 = Rz * (cos(theta) - k1 / Zb * cos(Zb * theta));
		double c_gamma, s_gamma;
		double temp = sqrt(1 + k1 * k1 - 2 * k1 * cos(Zb * theta));
		c_gamma = (k1 * sin(Zb * theta) - sin(theta)) / temp;
		s_gamma = -(k1 * cos(Zb * theta) + cos(theta)) / temp;
		double x1, y1;
		x1 = x0 + rz * c_gamma;
		y1 = y0 + rz * s_gamma;
		return sqrt(x1 * x1 + y1 * y1);
	}

	// variables with the postfix "0" is the theoretical value.
	double Rz = 0, Rz0 = 0;
	double Za = 0;
	double rz = 0, rz0 = 0;
	double e = 0, e0 = 0;
	std::vector<std::pair<double, double>> zeiss;
	//std::vector<double> zeiss_ang;
	std::vector<std::pair<double, double>> zeiss_pol;
	std::vector<int> addendum;
	std::vector<int> root;


	double Zb = Za + 1.0;
	double k1 = e * Zb / Rz;
};

