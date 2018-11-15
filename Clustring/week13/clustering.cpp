#include "clustering.h"

char whatIsMinimum(double A, double B, double C)
{
	double min = A;
	char whatIs = 'A';
	if (B < min)
	{
		min = B;
		whatIs = 'B';
	}
	if (C < min)
	{
		min = C;
		whatIs = 'C';
	}
	return whatIs;
}