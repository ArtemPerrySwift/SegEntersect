#include "Segment.h"


Vector3D::Vector3D()
{
	X = Y = Z = 0;
}

Vector3D::Vector3D(double X, double Y, double Z)
{
	this->X = X;
	this->Y = Y;
	this->Z = Z;
}

bool isEqual(Vector3D num1, Vector3D num2)
{
	if (isEqual(num1.X, num2.X) && isEqual(num1.Y, num2.Y) && isEqual(num1.Z, num2.Z))
		return true;

	return false;
}

std::istream& operator >> (std::istream& in, Vector3D& vector3D)
{
	in >> vector3D.X >> vector3D.Y >> vector3D.Z;
	return in;
}

std::ostream& operator << (std::ostream& out, Vector3D& vector3D)
{
	out << vector3D.X << " " << vector3D.Y << " " << vector3D.Z;
	return out;
}

Vector3D Segment3D::getStartVect()
{
	return start;
}

Vector3D Segment3D::getEndVect()
{
	return end;
}

int Segment3D::setStart(Vector3D newStart)
{
	if (isEqual(start, newStart))
		return DEGENERATE_ERR;

	start = newStart;
	return 0;
}

int Segment3D::setEnd(Vector3D newEnd)
{
	if (isEqual(start, newEnd))
		return DEGENERATE_ERR;

	end = newEnd;
	return 0;
}

int Segment3D::setStartEnd(Vector3D newStart, Vector3D newEnd)
{
	if (setStart(newStart) != 0)
		return DEGENERATE_ERR;

	if (setEnd(newEnd) != 0)
		return DEGENERATE_ERR;

	return 0;
}

Segment3D::Segment3D()
{
	end.X = 1;
	end.Y = 1;
	end.Z = 1;
}

std::istream& Segment3D::read(std::istream& in)
{
	Vector3D bufStart;
	Vector3D bufEnd;

	in >> bufStart >> bufEnd;
	if (isEqual(bufStart, bufEnd))
		throw "Length of segment cannot be almost 0";

	start = bufStart;
	end = bufEnd;

	return in;
}

/// <summary>
/// Представляя прямую образованную двумя точками отрезка в параметрическом виде, возвращает значение параметра,
/// подставляя который в параметрическое уравнение прямой, можно получить входную точку vect
/// </summary>
int Segment3D::getParamByVect(Vector3D vect, double& param)
{
	double t = 0;
	double tx, ty, tz;
	bool fx = true, fy = true, fz = true;

	fx = !isEqual(end.X, start.X);
	if (fx)
	{
		tx = (vect.X - start.X) / (end.X - start.X);
		t = tx;
	}
	else
		if (!isEqual(vect.X, start.X))
			return VECT_IS_OUT_LINE;


	fy = !isEqual(end.Y, start.Y);
	if (fy)
	{
		ty = (vect.Y - start.Y) / (end.Y - start.Y);
		t = ty;
	}
	else
		if (!isEqual(vect.Y, start.Y))
			return VECT_IS_OUT_LINE;

	fz = !isEqual(end.Z, start.Z);
	if (fz)
	{
		tz = (vect.Z - start.Z) / (end.Z - start.Z);
		t = tz;
	}
	else
		if (!isEqual(vect.Z, start.Z))
			return VECT_IS_OUT_LINE;


	if (fx && fy && !isEqual(tx, ty))
		return VECT_IS_OUT_LINE;

	if (fx && fz && !isEqual(tx, tz))
		return VECT_IS_OUT_LINE;

	if (fy && fz && !isEqual(ty, tz))
		return VECT_IS_OUT_LINE;


	param = t;
	return 0;
}

bool Segment3D::isVectInSegment(Vector3D vect)
{
	double param;
	int resultCode = getParamByVect(vect, param);

	if (resultCode != 0)
		return false;

	return MIN_SEG_PARAM <= param && param <= MAX_SEG_PARAM;
}

Vector3D Segment3D::getVectByParam(double param)
{
	Vector3D ans;
	ans.X = start.X + param * (end.X - start.X);
	ans.Y = start.Y + param * (end.Y - start.Y);
	ans.Z = start.Z + param * (end.Z - start.Z);

	return ans;
}

/// <summary>
/// Минимальное значение которое может принимать параметр, чтобы точка находящаяся на линии отрезка
/// и являющаяся результатом подстановки параметра в уравнение прямой находилась в пределах отрезка
/// </summary>
const double Segment3D::MIN_SEG_PARAM = 0;

/// <summary>
/// Максимальное значение которое может принимать параметр, чтобы точка находящаяся на линии отрезка
/// и являющаяся результатом подстановки параметра в уравнение прямой находилась в пределах отрезка
/// </summary>
const double Segment3D::MAX_SEG_PARAM = 1;

std::istream& operator >> (std::istream& in, Segment3D& segment3D)
{
	return segment3D.read(in);
}

int fillSLAEForIntersect(Segment3D segments[SEG_NUM], StaticRectSLAE<DIM_NUM, SEG_NUM>& slae)
{
	Vector3D startSegVect[SEG_NUM];
	Vector3D endSegVect[SEG_NUM];

	for (int i = 0; i < SEG_NUM; i++)
	{
		startSegVect[i] = segments[i].getStartVect();
		endSegVect[i] = segments[i].getEndVect();
	}

	slae.matSLAE[0][0] = endSegVect[0].X - startSegVect[0].X;
	slae.matSLAE[1][0] = endSegVect[0].Y - startSegVect[0].Y;
	slae.matSLAE[2][0] = endSegVect[0].Z - startSegVect[0].Z;

	slae.matSLAE[0][1] = -(endSegVect[1].X - startSegVect[1].X);
	slae.matSLAE[1][1] = -(endSegVect[1].Y - startSegVect[1].Y);
	slae.matSLAE[2][1] = -(endSegVect[1].Z - startSegVect[1].Z);

	slae.fSLAE[0] = startSegVect[1].X - startSegVect[0].X;
	slae.fSLAE[1] = startSegVect[1].Y - startSegVect[0].Y;
	slae.fSLAE[2] = startSegVect[1].Z - startSegVect[0].Z;


	return 0;
}

int intersect(Segment3D segments[SEG_NUM], Vector3D& intersectVect)
{
	double buf;

	double rectSLAE[DIM_NUM][SEG_NUM];
	double fRectSLAE[DIM_NUM];

	StaticRectSLAE<DIM_NUM, SEG_NUM> slae;

	double vectParams[SEG_NUM];

	fillSLAEForIntersect(segments, slae);

	if (slae.solveRectSLAE(vectParams) == 0) // если линии на которых расположены отрезки пересекаются
	{
		if (Segment3D::MIN_SEG_PARAM >= vectParams[0] || vectParams[0] >= Segment3D::MAX_SEG_PARAM ||
			Segment3D::MIN_SEG_PARAM >= vectParams[1] || vectParams[1] >= Segment3D::MAX_SEG_PARAM) // Если линии пересекаются за пределами отрезков
			return NO_INTERSECT;

		intersectVect = segments[0].getVectByParam(vectParams[0]);
		return 0;
	}

	bool isStartVectSeg0InSeg1, isEndVectSeg0InSeg1;
	bool isStartVectSeg1InSeg0, isEndVectSeg1InSeg0;

	isStartVectSeg0InSeg1 = segments[1].isVectInSegment(segments[0].getStartVect());
	isEndVectSeg0InSeg1 = segments[1].isVectInSegment(segments[0].getEndVect());
	isStartVectSeg1InSeg0 = segments[0].isVectInSegment(segments[1].getStartVect());
	isEndVectSeg1InSeg0 = segments[0].isVectInSegment(segments[1].getEndVect());

	if (!(isStartVectSeg0InSeg1 || isEndVectSeg0InSeg1 || isStartVectSeg1InSeg0 || isEndVectSeg1InSeg0)) // Если отрезки расположены на параллельных прямых или на одной, но не пересекаются
		return NO_INTERSECT;

	if (isStartVectSeg0InSeg1 && isEndVectSeg0InSeg1 || isStartVectSeg1InSeg0 && isEndVectSeg1InSeg0) // Если один отрезок вложен в другой
		return MULT_INTERSECT;

	/*Блок проверки пересечения отрезков в их крайних точках*/
	if (isEqual(segments[0].getStartVect(), segments[1].getStartVect()))
	{
		intersectVect = segments[0].getStartVect();
		return 0;
	}

	if (isEqual(segments[0].getStartVect(), segments[1].getEndVect()))
	{
		intersectVect = segments[0].getStartVect();
		return 0;
	}

	if (isEqual(segments[0].getEndVect(), segments[1].getStartVect()))
	{
		intersectVect = segments[0].getEndVect();
		return 0;
	}

	if (isEqual(segments[0].getEndVect(), segments[1].getEndVect()))
	{
		intersectVect = segments[0].getEndVect();
		return 0;
	}

	return MULT_INTERSECT;

}
