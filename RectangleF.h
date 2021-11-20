#pragma once
#include "Figure.h"

class RectangleF : public Figure {
	DECLARE_SERIAL(RectangleF)
public:
	RectangleF();
	RectangleF(CPoint P1, CPoint P2, COLORREF fillColor, COLORREF colorLine, int thickness);
	~RectangleF();
	void innerDraw(CDC* dc);
};
