#pragma once
#include "Vec2.h"

class Rect
{
public:
	Rect();
	virtual~Rect();


	void Draw(unsigned, int Color, bool isFill);

	void SetLT(float left, float top, float width, float height);

	void SetCenter(float x, float y, float width, float height);

public:
	float GetWidth() const;
	float GetHeight() const;
	float GetCenter() const;
	float GetCenter() const;


};

