#pragma once
#include <math.h>
#include <vector>
#include <map>

class CycloidGear
{
public:
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


	double Rz;
	double Za;
	double rz;
	double e;
	std::vector<std::pair<double, double>> zeiss;
	std::vector<double> zeiss_ang;


	double Zb = Za + 1.0;
	double k1 = e * Zb / Rz;
};

