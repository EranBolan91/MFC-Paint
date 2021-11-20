#pragma once
#include "Figure.h"

class Circle : public Figure {
	DECLARE_SERIAL(Circle)
public:
	Circle();
	Circle(CPoint P1, CPoint P2, COLORREF fillColor, COLORREF colorLine, int thickness);
	~Circle();
	void innerDraw(CDC* dc);
	void Serialize(CArchive& ar);
	void redefine(CPoint p1, CPoint p2);
	bool isInside(const CPoint& P) const;
};
