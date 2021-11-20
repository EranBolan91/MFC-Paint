#pragma once
#include "RectangleF.h"

class Parallelogram : public RectangleF {
	DECLARE_SERIAL(Parallelogram)
private:
	CPoint P3, P4;
public:
	Parallelogram();
	Parallelogram(CPoint P1, CPoint P2, COLORREF colorLine, COLORREF fillColor, int thickness);
	~Parallelogram();
	void innerDraw(CDC* dc);
	void Serialize(CArchive& ar);
	void redefine(CPoint p1, CPoint p2);
	bool isInside(const CPoint& P) const;
	void shift(int dx, int dy);
};
