#include "MathCompare.h"

bool isEqual(double num1, double num2)
{
	if (num1 == num2)
		return true;

	double buf = num1 != 0 ? num1 : num2;

	if (abs((num2 - num1) / buf) < EPS)
		return true;

	return false;
}