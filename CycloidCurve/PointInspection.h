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


	bool SwitchInitialPoint(std::vector<std::pair<double, double>>& zeiss, std::vector<std::pair<double, double>>& zeiss_ang, const int Z) {
		double maxradium = zeiss_ang[0].first;
		int argmax = 0, i = zeiss_ang.size() - zeiss_ang.size()/ (0.9 * Z);
		for (auto itr = zeiss_ang.cend() - zeiss_ang.size() / (0.9 * Z); itr != zeiss_ang.cend(); ++itr) {
			if (maxradium < itr->first) {
				argmax = i;
				maxradium = itr->first;
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

	bool DuplicateInspection(std::vector<std::pair<double, double>>& zeiss) {
		double prev = 0.0, curr = 0.0;
		auto itr1 = zeiss.cbegin();
		auto itr2 = ++zeiss.cbegin();
		prev = Distance(*(itr1++), *(itr2++));
		curr = Distance(*(itr1++), *(itr2++));
		for (; itr2 != zeiss.cend();) {
			if (curr <= 0.2 * prev)
				break;
			prev = curr;
			curr = Distance(*(itr1++), *(itr2++));
		}
		if (itr2 != zeiss.cend()) {
			std::cout << "The #" << itr1 - zeiss.cbegin() + 1 << " and #" << itr2 - zeiss.cbegin() + 1 << " are duplicated!" << std::endl;
			std::cout << "Please deal with duplicated points before the conversion!" << std::endl;
			return true;
		}
		if (Distance(*(zeiss.cbegin()), *(--zeiss.cend())) <= 0.5 * prev) {
			std::cout << "The #1  and #" << zeiss.size() << " are duplicated!" << std::endl;
			std::cout << "Please deal with duplicated points before the conversion!" << std::endl;
			return true;
		}

		return false;
	}

	bool DisorderInspection(std::vector<std::pair<double, double>>& zeiss_pol) {
		auto itr1 = zeiss_pol.cbegin(), itr2 = ++zeiss_pol.cbegin();
		for (; itr2 != zeiss_pol.cend();++itr1, ++itr2) {
			if (itr2->second - itr1->second < 0 && itr2->second - itr1->second > -3.14)
				break;
		}
		if (itr2 != zeiss_pol.cend()) {
			std::cout << "The #" << itr1 - zeiss_pol.cbegin() + 1 << " OR #" << itr2 - zeiss_pol.cbegin() + 1 << " may disordered!" << std::endl;
			std::cout << "Please deal with disorder points before the conversion!" << std::endl;
			return false;
		}
		if (zeiss_pol.cbegin()->second < (--zeiss_pol.cend())->second) {
			std::cout << "The #1 OR #" << zeiss_pol.size() << " may disordered!" << std::endl;
			std::cout << "Please deal with disorder points before the conversion!" << std::endl;
			return false;
		}
		return true;
	}

	double Distance(const std::pair<double, double> point1, const std::pair<double, double> point2) {
		double distance = 0.0;
		double dx = point1.first - point2.first;
		double dy = point1.second - point2.second;
		distance = sqrt(dx * dx + dy * dy);
		return distance;
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

