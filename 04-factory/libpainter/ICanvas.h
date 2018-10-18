#pragma once

#include <iostream>

enum Color
{
	GREEN,
	RED,
	BLUE,
	YELLOW,
	PINK,
	BLACK
};

struct Point
{
	int x;
	int y;
};

class ICanvas
{

public:
	virtual ~ICanvas() = default;

	virtual void SetColor(Color color) = 0;
	virtual void DrawLine(Point from, Point to) = 0;
	virtual void DrawEllipse(Point center, int w, int h) = 0;
};