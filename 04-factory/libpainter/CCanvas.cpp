#include "stdafx.h"
#include "CCanvas.h"

void CCanvas::SetColor(Color color)
{
	m_canvasColor = color;
}

void CCanvas::DrawLine(Point from, Point to)
{
	std::cout << "Drawing line from: x = " << from.x 
		<< " y = " << from.y << "\nto: x = " << to.x
		<< " y = " << to.y << std::endl;
}

void CCanvas::DrawEllipse(Point center, int width, int height)
{
	std::cout << "Drawing ellipse with center: x = " << center.x
		<< " y = " << center.y << "\nradius 1 = " << width
		<< " radius 2 = " << height << std::endl;
}
