#pragma once

#include <vector>

class Pos {
public:
	Pos();
	Pos(const int dim);
	Pos(const Pos& t);

public:
	Pos operator+(const Pos& t) const;
	Pos operator-(const Pos& t) const;
	Pos operator*(const double f) const;

public:
	Pos& operator=(const Pos& t);
	Pos& operator+=(const Pos& t);
	Pos& operator*=(const double f);

public:
	double& operator[](const unsigned int i);

public:
	void setZero();
	double length() const;
	double eucDis() const;
	int getDim() const;

private:
	int dim;
	std::vector<double> pos;
};