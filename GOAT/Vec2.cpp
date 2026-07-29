#include "Vec2.h"

Vec2::Vec2():
	x(0.0),
	y(0.0)
	
{
}

Vec2::~Vec2()
{
}

void Vec2::Init()
{
}

void Vec2::End()
{
}

void Vec2::Update()
{
	
}

float Vec2::sqrLength()
{
	float ans;
	float len2;

	len2 = (x * x) + (y*y);

	return len2;
}
