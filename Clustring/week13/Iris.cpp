#include "clustering.h"

void Iris::divide(int num)
{
	IrisNumericalInfo::divide(num);
}

void Iris::show() const
{
	cout << getSepalLength() << '\t' << getSepalWidth() << '\t' << getPetalLength() << '\t'
		<< getPetalWidth() << '\t' << name << endl;
}

void Iris::csvPrint(ofstream& fout) const
{
	fout << getSepalLength() << ',' << getSepalWidth() << ',' << getPetalLength() << ','
		<< getPetalWidth() << ',' << name << endl;
}

void Iris::initByZero()
{
	IrisNumericalInfo::initByZero();
	memset(name, '\0', max_buff);
}

Iris& operator<<(Iris& object, ifstream& fin)
{
	(IrisNumericalInfo&)object << fin;
	fin.getline(object.name, max_buff);
	return object;
}