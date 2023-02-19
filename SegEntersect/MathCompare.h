#pragma once
#include <cmath>
const double EPS = 1e-12;

/// <summary>
/// Сравнение на равенство двух чисел с плавающей точкой с учётом погрешности вычислений
/// </summary>
bool isEqual(double num1, double num2);
