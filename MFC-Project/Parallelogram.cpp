#include "pch.h"
#include "Parallelogram.h"

IMPLEMENT_SERIAL(Parallelogram, CObject, 1)

Parallelogram::Parallelogram() : RectangleF() {}

Parallelogram::Parallelogram(CPoint P1, CPoint P2, COLORREF fillColor, COLORREF colorLine, int thickness) : RectangleF(P1, P2, fillColor, colorLine, thickness) {}

Parallelogram::~Parallelogram() {}

void Parallelogram::innerDraw(CDC* dc) {
	CPoint arr[4], P1, P2;
	P1 = getP1();
	P2 = getP2();
	arr[0].x = P1.x;
	arr[0].y = P1.y;
	arr[1].x = P2.x;
	arr[1].y = P2.y;
	arr[2].x = P3.x;
	arr[2].y = P3.y;
	arr[3].x = P4.x;
	arr[3].y = P4.y;

	dc->Polygon(arr, 4);
}

void Parallelogram::Serialize(CArchive& ar) {
	CObject::Serialize(ar);
	COLORREF fillColor, colorLine;
	CPoint p1, p2;
	int thickness;
	if (ar.IsStoring()) {
		ar << getP1();
		ar << getP2();
		ar << P3;
		ar << P4;
		ar << getColorLine();
		ar << getFillColor();
		ar << getThickness();
	}
	else {
		ar >> p1;
		ar >> p2;
		ar >> P3;
		ar >> P4;
		ar >> colorLine;
		ar >> fillColor;
		ar >> thickness;
		setP1(p1);
		setP2(p2);
		setColorLine(colorLine);
		setFillColor(fillColor);
		setThickness(thickness);
	}
}

void Parallelogram::redefine(CPoint p1, CPoint p2) {
	int dx;
	dx = p2.x - p1.x;
	CPoint newP2(p2.x-80,p1.y);
	setP1(p1);
	setP2(newP2);
	P3.x = p2.x;
	P3.y = p2.y;
	P4.x = p1.x + 80;
	P4.y = p2.y;
}

bool Parallelogram::isInside(const CPoint& P) const {
	CPoint p1, p2;
	p1 = getP1();
	p2 = getP2();
	return (P.x >= p1.x && P.x <= P3.x && P.y >= p1.y && P.y <= P3.y) ||
		(P.x <= p1.x && P.x >= P3.x && P.y <= p1.y && P.y >= P3.y);
};

void Parallelogram::shift(int dx, int dy) {
	CPoint p1, p2;
	p1 = getP1();
	p2 = getP2();
	p1.x = dx - p1.x;
	p1.y = dy - p1.y;
	p2.x = dx - p2.x;
	p2.y = dy - p2.y;
	setP1(p1);
	setP2(p2);
	P3.x = dx - P3.x;
	P3.y = dy - P3.y;
	P4.x = dx - P4.x;
	P4.y = dy - P4.y;
};