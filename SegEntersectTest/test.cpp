#include "pch.h"
#include "../SegEntersect/Segment.cpp"
#include "../SegEntersect/MathCompare.cpp"

Vector3D vectForSegm0[SEG_VECT_NUM];
Vector3D vectForSegm1[SEG_VECT_NUM];

Segment3D segments[SEG_NUM];

TEST(Intersection, GeneralIntersection) 
{
	Vector3D vectForSegm0[SEG_VECT_NUM];
	Vector3D vectForSegm1[SEG_VECT_NUM];

	Segment3D segments[SEG_NUM];

	vectForSegm0[0] = { -2, 1, 3 };
	vectForSegm0[1] = { 4, 3, 5 };

	vectForSegm1[0] = { -1, -2, 0 };
	vectForSegm1[1] = { 3, 10, 12 };
	
	segments[0].setStartEnd(vectForSegm0[0], vectForSegm0[1]);
	segments[1].setStartEnd(vectForSegm1[0], vectForSegm1[1]);

	Vector3D intersectPoint;

	int intersectResCode = intersect(segments, intersectPoint);

	EXPECT_EQ(intersectResCode, 0);

	Vector3D trueIntersectPoint(0.25, 1.75, 3.75);

	EXPECT_TRUE(isEqual(intersectPoint, trueIntersectPoint));
	
	//EXPECT_TRUE(true);
}

TEST(Intersection, IntersectionIn2DPlot)
{
	Vector3D vectForSegm0[SEG_VECT_NUM];
	Vector3D vectForSegm1[SEG_VECT_NUM];

	Segment3D segments[SEG_NUM];

	vectForSegm0[0] = { -2, 1, 0 };
	vectForSegm0[1] = { 4, 3, 0 };

	vectForSegm1[0] = { -1, -2, 0 };
	vectForSegm1[1] = { 3, 10, 0 };

	segments[0].setStartEnd(vectForSegm0[0], vectForSegm0[1]);
	segments[1].setStartEnd(vectForSegm1[0], vectForSegm1[1]);

	Vector3D intersectPoint;

	int intersectResCode = intersect(segments, intersectPoint);

	EXPECT_EQ(intersectResCode, 0);

	Vector3D trueIntersectPoint(0.25, 1.75, 0);

	EXPECT_TRUE(isEqual(intersectPoint, trueIntersectPoint));

	//EXPECT_TRUE(true);
}

TEST(Intersection, BoundaryIntersection)
{
	Vector3D vectForSegm0[SEG_VECT_NUM];
	Vector3D vectForSegm1[SEG_VECT_NUM];

	Segment3D segments[SEG_NUM];

	vectForSegm0[0] = { -2, 1, 3 };
	vectForSegm0[1] = { 4, 3, 5 };

	vectForSegm1[0] = { 4, 3, 5 };
	vectForSegm1[1] = { 7, 4, 6 };

	segments[0].setStartEnd(vectForSegm0[0], vectForSegm0[1]);
	segments[1].setStartEnd(vectForSegm1[0], vectForSegm1[1]);

	Vector3D intersectPoint;

	int intersectResCode = intersect(segments, intersectPoint);

	EXPECT_EQ(intersectResCode, 0);

	Vector3D trueIntersectPoint(4, 3, 5);

	EXPECT_TRUE(isEqual(intersectPoint, trueIntersectPoint));

	//EXPECT_TRUE(true);
}

TEST(NoIntersaction, IntersectionOutOfSegments)
{
	Vector3D vectForSegm0[SEG_VECT_NUM];
	Vector3D vectForSegm1[SEG_VECT_NUM];

	Segment3D segments[SEG_NUM];

	vectForSegm0[0] = { 1, 2, 4 };
	vectForSegm0[1] = { 4, 3, 5 };

	vectForSegm1[0] = { -1, -2, 0 };
	vectForSegm1[1] = { 3, 10, 12 };

	segments[0].setStartEnd(vectForSegm0[0], vectForSegm0[1]);
	segments[1].setStartEnd(vectForSegm1[0], vectForSegm1[1]);

	Vector3D intersectPoint;

	int intersectResCode = intersect(segments, intersectPoint);

	EXPECT_EQ(intersectResCode, NO_INTERSECT);

}

TEST(NoIntersaction, ParallelSegments)
{
	Vector3D vectForSegm0[SEG_VECT_NUM];
	Vector3D vectForSegm1[SEG_VECT_NUM];

	Segment3D segments[SEG_NUM];

	vectForSegm0[0] = { 1, 2, 4 };
	vectForSegm0[1] = { 4, 3, 5 };

	vectForSegm1[0] = { 2, 2, 4 };
	vectForSegm1[1] = { 5, 3, 5 };

	segments[0].setStartEnd(vectForSegm0[0], vectForSegm0[1]);
	segments[1].setStartEnd(vectForSegm1[0], vectForSegm1[1]);

	Vector3D intersectPoint;

	int intersectResCode = intersect(segments, intersectPoint);

	EXPECT_EQ(intersectResCode, NO_INTERSECT);

}

TEST(NoIntersaction, SegmentsOnOneLine)
{
	Vector3D vectForSegm0[SEG_VECT_NUM];
	Vector3D vectForSegm1[SEG_VECT_NUM];

	Segment3D segments[SEG_NUM];

	vectForSegm0[0] = { 1, 2, 4 };
	vectForSegm0[1] = { 4, 3, 5 };

	vectForSegm1[0] = { 7, 4, 6 };
	vectForSegm1[1] = { 10, 5, 7 };

	segments[0].setStartEnd(vectForSegm0[0], vectForSegm0[1]);
	segments[1].setStartEnd(vectForSegm1[0], vectForSegm1[1]);

	Vector3D intersectPoint;

	int intersectResCode = intersect(segments, intersectPoint);

	EXPECT_EQ(intersectResCode, NO_INTERSECT);
}

TEST(MultipleIntersactions, SegmentInAnotheSegment)
{
	Vector3D vectForSegm0[SEG_VECT_NUM];
	Vector3D vectForSegm1[SEG_VECT_NUM];

	Segment3D segments[SEG_NUM];

	vectForSegm0[0] = { 1, 2, 4 };
	vectForSegm0[1] = { 10, 5, 7 };

	vectForSegm1[0] = { 7, 4, 6 };
	vectForSegm1[1] = { 10, 5, 7 };

	segments[0].setStartEnd(vectForSegm0[0], vectForSegm0[1]);
	segments[1].setStartEnd(vectForSegm1[0], vectForSegm1[1]);

	Vector3D intersectPoint;

	int intersectResCode = intersect(segments, intersectPoint);

	EXPECT_EQ(intersectResCode, MULT_INTERSECT);
}

TEST(MultipleIntersactions, SegmentPartInAnotheSegment)
{
	Vector3D vectForSegm0[SEG_VECT_NUM];
	Vector3D vectForSegm1[SEG_VECT_NUM];

	Segment3D segments[SEG_NUM];

	vectForSegm0[0] = { 1, 2, 4 };
	vectForSegm0[1] = { 7, 4, 6 };

	vectForSegm1[0] = { 4, 3, 5 };
	vectForSegm1[1] = { 10, 5, 7 };

	segments[0].setStartEnd(vectForSegm0[0], vectForSegm0[1]);
	segments[1].setStartEnd(vectForSegm1[0], vectForSegm1[1]);

	Vector3D intersectPoint;

	int intersectResCode = intersect(segments, intersectPoint);

	EXPECT_EQ(intersectResCode, MULT_INTERSECT);
}