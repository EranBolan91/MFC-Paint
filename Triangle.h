#pragma once
#include "Figure.h"

class Triangle : public Figure{
	DECLARE_SERIAL(Triangle)
private:
	CPoint P3 = 0;
public:
	Triangle();
	Triangle(CPoint P1, CPoint P2, COLORREF colorLine, COLORREF fillColor, int thickness);
	~Triangle();
	void innerDraw(CDC* dc);
	void setP3(const CPoint P);
	void Serialize(CArchive& ar);
	void redefine(CPoint p1, CPoint p2);
	bool isInside(const CPoint& P) const;
};
