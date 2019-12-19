#include "type.h"
#include <iostream>

using namespace std;

Pos::Pos()
	: dim(0)
{
}

Pos::Pos(const int dim)
	: dim(dim), pos(dim, 0.0)
{
}

Pos::Pos(const Pos& t)
	: dim(t.dim), pos(t.pos)
{
}

Pos Pos::operator+(const Pos& t) const
{
	Pos r(dim);
	for (int i = 0; i < dim; ++i)
		r.pos[i] = pos[i] + t.pos[i];
	return r;
}

Pos Pos::operator-(const Pos& t) const
{
	Pos r(dim);
	for (int i = 0; i < dim; ++i)
		r.pos[i] = pos[i] - t.pos[i];
	return r;
}

Pos Pos::operator*(const double f) const
{
	Pos r(dim);
	for (int i = 0; i < dim; ++i)
		r.pos[i] = pos[i] * f;
	return r;
}

Pos& Pos::operator=(const Pos& t)
{
	dim = t.dim;
	pos = t.pos;
	return *this;
}

Pos& Pos::operator+=(const Pos& t)
{
	for (int i = 0; i < dim; ++i)
		pos[i] += t.pos[i];
	return *this;
}

Pos& Pos::operator*=(const double f)
{
	for (double& i : pos)
		i *= f;
	return *this;
}

double& Pos::operator[](const unsigned int i)
{
	return pos[i];
}

void Pos::setZero()
{
	pos.assign(dim, 0);
}

double Pos::length() const
{
	double r = 0;
	for (double i : pos)
		r += i * i;
	return sqrt(r);
}

int Pos::getDim() const
{
	return dim;
}
