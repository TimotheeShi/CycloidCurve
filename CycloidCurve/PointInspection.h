#pragma once
#include <vector>
#include <utility>
#include <iostream>

class PointInspection
{
public:
	PointInspection() = default;

	bool AxisToAddendum(std::vector<std::pair<double, double>>& zeiss, std::vector<std::pair<double, double>>& zeiss_ang) {
		int argmin = 0;
		/*double minang = zeiss_ang[0].second * zeiss_ang[0].second;
		for (int ang = minang, i = 0; i != zeiss_ang.size(); ++i) {
			if (minang > (ang = zeiss_ang[i].second * zeiss_ang[i].second)) {
				minang = ang;
				argmin = i;
			}
		}
		double rot_ang = -zeiss_ang[argmin].second;
		PointRotation(zeiss, zeiss_ang, rot_ang);
		*/
		int p1 = argmin + 19, p2 = argmin - 19;
		if (argmin <= 20) {
			p1 = argmin + 20;
			p2 = zeiss_ang.size() - 20;
		}
		if (argmin >= zeiss_ang.size() - 20) {
			p1 = 20;
			p2 = argmin - 20;
		}
		auto itr1 = zeiss_ang[p1];
		auto itr2 = zeiss_ang[p2];
		double x_point = zeiss_ang[argmin].first;
		bool test1 = x_point > itr1.first;
		bool test2 = x_point > itr2.first;
		if (test1 != test2) std::cout << "Inspection Failed: Points are disordered!" << std::endl;
		if (test1) std::cout << "Axis X is pointing to the Addendum!" << std::endl;
		else std::cout << "Axis X is pointing to the Root!" << std::endl;
		return test1;
	}

	bool SwitchInitialPoint(std::vector<std::pair<double, double>>& zeiss, std::vector<std::pair<double, double>>& zeiss_ang) {
		double maxradium = zeiss_ang[0].first;
		double radium = 0;
		int argmax = 0, i = zeiss_ang.size() - 100;
		for (auto itr = zeiss_ang.cend() - 100; itr != zeiss_ang.cend(); ++itr) {
			if (maxradium < (radium = itr->first)) {
				argmax = i;
				maxradium = radium;
			}
			i++;
		}
		std::vector<std::pair<double, double>> new_zeiss;
		std::vector<std::pair<double, double>> new_zeiss_ang;
		for (int i = argmax; i != zeiss.size(); i++) {
			new_zeiss.push_back(zeiss[i]);
			new_zeiss_ang.push_back(zeiss_ang[i]);
		}
		for (int i = 0; i < argmax; i++) {
			new_zeiss.push_back(zeiss[i]);
			new_zeiss_ang.push_back(zeiss_ang[i]);
		}
		std::swap(zeiss, new_zeiss);
		std::swap(zeiss_ang, new_zeiss_ang);
		return true;
	}

	bool PointRotation(std::vector<std::pair<double, double>>& zeiss, std::vector<std::pair<double, double>>& zeiss_ang, double rot_ang = 0.0) {
		std::vector<std::pair<double, double>> new_zeiss;
		for (auto& point : zeiss_ang) {
			point.second += rot_ang;
			std::pair<double, double> new_car;
			new_car.first = point.first * cos(point.second);
			new_car.second = point.first * sin(point.second);
			new_zeiss.push_back(new_car);
		}
		std::swap(zeiss, new_zeiss);
		return true;
	}
};

