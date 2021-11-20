#pragma once
#include "RectangleF.h"

class Square : public RectangleF {
	DECLARE_SERIAL(Square)
private:
	CPoint P3, P4;
public:
	Square();
	Square(CPoint P1, CPoint P2, COLORREF colorLine, COLORREF fillColor, int thickness);
	~Square();
	void innerDraw(CDC* dc);
	void Serialize(CArchive& ar);
	void redefine(CPoint p1, CPoint p2);
	bool isInside(const CPoint& P) const;
	void shift(int dx, int dy);
};