#pragma once

#include "ICanvas.h"

class CCanvas : public ICanvas
{
	void SetColor(Color color) override;
	void DrawLine(Point from, Point to) override;
	void DrawEllipse(Point center, int width, int height) override;

private:
	Color m_canvasColor;
};