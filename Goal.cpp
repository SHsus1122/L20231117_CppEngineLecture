#include "Goal.h"

AGoal::AGoal()
{
	Shape = 'G';
	X = 10;
	Y = 10;
	SortOrder = 200;
}

AGoal::AGoal(int NewX, int NewY, char NewShape, int NewSortOrder)
{
	Shape = NewShape;
	SetX(NewX);
	SetY(NewY);
	SortOrder = NewSortOrder;
}

AGoal::~AGoal()
{
}
