#pragma once
#include <fstream>
#include <string>
#include "staticSLAE.h"

const int DIM_NUM = 3; //  оличество измерений в которых рассматриваютс€ отрезки
const int SEG_NUM = 2; //  оличество сегментов дл€ нахождени€ точки пересечени€
const int SEG_VECT_NUM = 2; //  оличество точек отрезка

enum INTERSECT_MSG { NO_INTERSECT = 1, MULT_INTERSECT}; //  оды сообщений дл€ функции посика точки пересечени€
enum SEGMENT_MSG { DEGENERATE_ERR = 1, VECT_IS_OUT_LINE }; //  оды сообщений дл€ методов Segment3D

struct Vector3D
{
public:
	double X;
	double Y;
	double Z;

	Vector3D();

	Vector3D(double X, double Y, double Z);
};

bool isEqual(Vector3D num1, Vector3D num2);

std::istream& operator >> (std::istream& in, Vector3D& vector3D);

std::ostream& operator << (std::ostream& out, Vector3D& vector3D);

class Segment3D
{
public:

	static const double MIN_SEG_PARAM;
	static const double MAX_SEG_PARAM;

	Vector3D getStartVect();

	Vector3D getEndVect();

	int setStart(Vector3D newStart);

	int setEnd(Vector3D newEnd);

	int setStartEnd(Vector3D newStart, Vector3D newEnd);

	Segment3D();

	std::istream& read(std::istream& in);

	/// <summary>
	/// ѕредставл€€ пр€мую образованную двум€ точками отрезка в параметрическом виде, возвращает значение параметра,
	/// подставл€€ который в параметрическое уравнение пр€мой, можно получить входную точку vect
	/// </summary>
	int getParamByVect(Vector3D vect, double& param);

	bool isVectInSegment(Vector3D vect);

	Vector3D getVectByParam(double param);

private:
	Vector3D start;
	Vector3D end;
};

std::istream& operator >> (std::istream& in, Segment3D& segment3D);

int fillSLAEForIntersect(Segment3D segments[SEG_NUM], StaticRectSLAE<DIM_NUM, SEG_NUM>& slae);

int intersect(Segment3D segments[SEG_NUM], Vector3D& intersectVect);