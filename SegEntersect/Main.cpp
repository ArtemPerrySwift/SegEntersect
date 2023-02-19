#include "Segment.h"

int main()
{
	Segment3D segments[SEG_NUM];

	std::ifstream in;
	in.open("Test.txt");

	for (int i = 0; i < SEG_NUM; i++)
		in >> segments[i];

	in.close();

	Vector3D intersectVect;

	int intersectResCode = intersect(segments, intersectVect);

	std::ofstream out;
	out.open("TestResult.txt");

	switch (intersectResCode)
	{
	case 0:
		out << "Intersection point: " << intersectVect << std::endl;
		break;

	case MULT_INTERSECT:
		out << "Error: there is multiaple intersection points" << std::endl;
		break;

	case NO_INTERSECT:
		out << "Error: there is no intersection point" << std::endl;
		break;

	default:
		out << "Something bad happened" << std::endl;
		return intersectResCode;
	}

	out.close();

	return 0;
}