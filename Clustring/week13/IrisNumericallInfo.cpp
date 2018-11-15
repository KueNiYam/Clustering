#include "clustering.h"

double IrisNumericalInfo::getSepalLength() const
{
	return sepalLength;
}

double IrisNumericalInfo::getSepalWidth() const
{
	return sepalWidth;
}

double IrisNumericalInfo::getPetalLength() const
{
	return petalLength;
}

double IrisNumericalInfo::getPetalWidth() const
{
	return petalWidth;
}

void IrisNumericalInfo::setSepalLength(double value)
{
	sepalLength = value;
}

void IrisNumericalInfo::setSepalWidth(double value)
{
	sepalWidth = value;
}

void IrisNumericalInfo::setPetalLength(double value)
{
	petalLength = value;
}

void IrisNumericalInfo::setPetalWidth(double value)
{
	petalLength = value;
}

void IrisNumericalInfo::divide(int num)
{
	if (num == 0)
		throw("Error: can't divide by zero\n");

	sepalLength /= num;
	sepalWidth /= num;
	petalLength /= num;
	petalWidth /= num;
}

void IrisNumericalInfo::initByZero()
{
	setSepalLength(0);
	setSepalWidth(0);
	setPetalLength(0);
	setPetalWidth(0);
}

void IrisNumericalInfo::show() const
{
	cout << getSepalLength() << '\t' << getSepalWidth() << '\t' << getPetalLength() << '\t'
		<< getPetalWidth() << endl;
}

IrisNumericalInfo& IrisNumericalInfo::operator+=(const IrisNumericalInfo& other)
{
	sepalLength += other.getSepalLength();
	sepalWidth += other.getSepalWidth();
	petalLength += other.getPetalLength();
	petalWidth += other.getPetalWidth();

	return *this; //< make object in heap memory
}

double IrisNumericalInfo::operator-(const IrisNumericalInfo& other) const
{
	double a, b, c, d;
	a = sepalLength - other.sepalLength;
	a *= a;
	b = sepalWidth - other.sepalWidth;
	b *= b;
	c = petalLength - other.petalLength;
	c *= c;
	d = petalWidth - other.petalWidth;
	d *= d;

	return ::sqrt(a + b + c + d);
}

IrisNumericalInfo& operator<<(IrisNumericalInfo& object, ifstream& fin)
{
	char buff[max_buff] = { 0, };
	fin.getline(buff, max_buff, ',');
	object.sepalLength = ::atof(buff);
	fin.getline(buff, max_buff, ',');
	object.sepalWidth = ::atof(buff);
	fin.getline(buff, max_buff, ',');
	object.petalLength = ::atof(buff);
	fin.getline(buff, max_buff, ',');
	object.petalWidth = ::atof(buff);

	return object;
}

