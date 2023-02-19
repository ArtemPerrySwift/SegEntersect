#pragma once
#include "MathCompare.h"
template<size_t NUM_ROWS, size_t NUM_COL>
int multMatVect(double mat[NUM_ROWS][NUM_COL], double vect[NUM_COL], double result[NUM_ROWS])
{
	for (int i = 0; i < NUM_ROWS; i++)
	{
		result[i] = 0;
		for (int k = 0; k < NUM_COL; k++)
			result[i] += mat[i][k] * vect[k];
	}

	return 0;
}

template<size_t NUM_ELEM>
int minus(double mas1[NUM_ELEM], double mas2[NUM_ELEM], double result[NUM_ELEM])
{
	for (int i = 0; i < NUM_ELEM; i++)
		result[i] = mas1[i] - mas2[i];

	return 0;
}

template<size_t NUM_ELEM>
int countNorm(double mas[NUM_ELEM])
{
	double norm = 0;
	for (int i = 0; i < NUM_ELEM; i++)
		norm += mas[i] * mas[i];

	return norm / NUM_ELEM;
}
