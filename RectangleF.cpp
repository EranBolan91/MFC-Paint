#include "pch.h"
#include "RectangleF.h"

IMPLEMENT_SERIAL(RectangleF, CObject, 1)

RectangleF::RectangleF() : Figure() {
	CPoint p1(0, 0), p2(0, 0);
	setP1(p1);
	setP2(p2);
}

RectangleF::RectangleF(CPoint P1, CPoint P2, COLORREF fillColor, COLORREF colorLine, int thickness) : Figure(P1,P2,fillColor,colorLine, thickness) {}

RectangleF::~RectangleF(){}

void RectangleF::innerDraw(CDC* dc) {
	CPoint P1, P2;
	P1 = getP1();
	P2 = getP2();
	dc->Rectangle(P1.x, P1.y, P2.x, P2.y);
}
