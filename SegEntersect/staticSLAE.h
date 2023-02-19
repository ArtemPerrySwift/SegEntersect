#pragma once
#include "MatrixVectMath.h"

enum SLAE_MSG { SLAE_FAIL = 1, WRONG_SOLUT = 2 };
template<size_t SLAE_DIM>
int solveSLAEByGausse(double A[SLAE_DIM][SLAE_DIM], double b[SLAE_DIM], double x[SLAE_DIM])
{
	double BufM[SLAE_DIM][SLAE_DIM];
	double bufb[SLAE_DIM];
	int i, j, k;
	double buf;
	bool f;

	for (i = 0; i < SLAE_DIM; i++)
	{
		bufb[i] = b[i];
		for (j = 0; j < SLAE_DIM; j++)
			BufM[i][j] = A[i][j];
	}

	double a;
	double aModule;
	int jMax;
	for (i = 0; i < SLAE_DIM; i++)
	{
		a = BufM[i][i];
		aModule = abs(a);
		jMax = i;
		for (j = i + 1; j < SLAE_DIM; j++)
		{
			if (abs(BufM[j][i]) > aModule) jMax = j;
		}

		if (!BufM[jMax][i]) return SLAE_FAIL;

		if (jMax != i)
		{
			for (k = i; k < SLAE_DIM; k++)
			{
				buf = BufM[i][k];
				BufM[i][k] = BufM[jMax][k];
				BufM[jMax][k] = buf;
			}
			buf = bufb[i];
			bufb[i] = bufb[jMax];
			bufb[jMax] = buf;
		}

		a = BufM[i][i];
		for (j = i; j < SLAE_DIM; j++)
			BufM[i][j] /= a;

		bufb[i] /= a;

		for (j = i + 1; j < SLAE_DIM; j++)
		{
			a = BufM[j][i];
			for (k = i; k < SLAE_DIM; k++)
			{
				BufM[j][k] -= a * BufM[i][k];
			}
			bufb[j] -= a * bufb[i];
		}
	}

	for (i = SLAE_DIM - 1; i > -1; i--)
	{
		for (j = i + 1; j < SLAE_DIM; j++)
			bufb[i] -= BufM[i][j] * x[j];
		x[i] = bufb[i];
	}

	return 0;
}

template<size_t NUM_ROWS, size_t NUM_COL>
struct StaticRectSLAE
{
public:
	double matSLAE[NUM_ROWS][NUM_COL];
	double fSLAE[NUM_ROWS];

	StaticRectSLAE()
	{
		for (int i = 0; i < NUM_ROWS; i++)
		{
			for (int j = 0; j < NUM_COL; j++)
				matSLAE[i][j] = 0;

			fSLAE[i] = 0;
		}
	}

	int virtual solveRectSLAE(double result[NUM_COL])
	{
		double quadSLAE[NUM_COL][NUM_COL];
		double fQuadSLAE[NUM_COL];

		rectSLAEtoQuadSLAE(quadSLAE, fQuadSLAE);

		int resultCode = solveSLAEByGausse<NUM_COL>(quadSLAE, fQuadSLAE, result);

		if (resultCode != 0)
			return resultCode;

		double normFRectSLAE = countNorm<NUM_ROWS>(fSLAE);

		if (normFRectSLAE == 0)
			return 0;

		double fRectSLAECheck[NUM_ROWS];

		multMatVect<NUM_ROWS, NUM_COL>(matSLAE, result, fRectSLAECheck);
		minus<NUM_ROWS>(fSLAE, fRectSLAECheck, fRectSLAECheck);
		
		double normError = countNorm<NUM_ROWS>(fRectSLAECheck);

	
		if (normError / normFRectSLAE > EPS)
			return WRONG_SOLUT;

		return 0;
	}

	/// <summary>
	/// Приведение прямоугольной СЛАУ к квадратной
	/// </summary>
	int rectSLAEtoQuadSLAE(double quadSLAE[NUM_COL][NUM_COL], double fQuadSLAE[NUM_COL])
	{
		for (int i = 0; i < NUM_COL; i++)
		{
			for (int j = 0; j < NUM_COL; j++)
			{
				quadSLAE[i][j] = 0;
				for (int k = 0; k < NUM_ROWS; k++)
					quadSLAE[i][j] += matSLAE[k][i] * matSLAE[k][j];

			}

			fQuadSLAE[i] = 0;
			for (int k = 0; k < NUM_ROWS; k++)
				fQuadSLAE[i] += matSLAE[k][i] * fSLAE[k];
		}

		return 0;
	}
};


template<size_t SLAE_DIM>
struct StaticQuadSLAE : public StaticRectSLAE<SLAE_DIM, SLAE_DIM>
{
	int solveRectSLAE(double result[SLAE_DIM]) override
	{
		return solveSLAEByGausse<SLAE_DIM>(this->matSLAE, this->fSLAE, result);
	}
};


