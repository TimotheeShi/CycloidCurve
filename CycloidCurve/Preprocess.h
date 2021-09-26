#pragma once
#include <vector>
#include <map>
#include <string>
#include <fstream>
#include <iostream>
#include <math.h>
#include <cctype>
#include <sstream>
#include <algorithm>
class Preprocess
{
public:
	bool readData(std::string file_name, std::vector<std::pair<double, double>> zeiss, std::vector<double> zeiss_ang) {
		double x = 0;
		double y = 0;
		bool flag = false;
		std::ifstream ifs(file_name);
		if (!ifs) {
			std::cout << "File input error!" << std::endl;
			return flag;
		}
		std::string line;
		getline(ifs, line);
		while (getline(ifs, line) && line != "$END" && !line.empty()) {
			std::pair<double, double> point = transfer(line);
			zeiss.push_back(point);
			zeiss_ang.push_back(CalAngle(x, y));
		}
		Info(zeiss);
		flag = true;
		return flag;
	}

private:

	double CalAngle(double x, double y) {
		return std::atan2(x, y);
	}

	void Info(std::vector<std::pair<double, double>> zeiss) {
		std::cout << "There are " << zeiss.size() << " points in the file." << std::endl;
	}

	std::pair<double, double> transfer(const std::string& str) {
		std::string num, xs, ys;
		for(auto c : str) {
			if (isdigit(c))
				num.push_back(c);
			if (c == ',' || isspace(c))
				num.push_back('*');
			if (c == '.')
				num.push_back('.');
		}
		auto itr = std::find(num.cbegin(), num.cend(), '*');
		for (auto i = num.cbegin(); i != itr; ++i)
			xs.push_back(*i);
		auto itr1 = std::find(++itr, num.cend(), '*');
		for (auto i = itr; i != itr1; ++i)
			ys.push_back(*i);
		double x = str2num(xs);
		double y = str2num(ys);
		return std::pair<double, double>(x, y);
	}

	double str2num(std::string str) {
		double result = 0;
		double res1 = 0;
		double res2 = 0;
		auto itr = std::find(str.cbegin(), str.cend(), '.');
		for(auto itr1 = str.cbegin(); itr1 != itr; ++itr1) {
			double addend = (*itr1) - '0';
			res1 = res1 * 10 + addend;
		}
		for (auto itr2 = --str.cend(); itr2 != itr; --itr2) {
			double addend = (*itr2) - '0';
			res2 = 0.1 * res2 + addend;
		}
		
		result = res1 + 0.1 * res2;

		return result;
	}
};
