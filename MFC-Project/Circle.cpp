#include "pch.h"
#include "Circle.h"

IMPLEMENT_SERIAL(Circle, CObject, 1)

Circle::Circle() : Figure() {};

Circle::Circle(CPoint P1, CPoint P2, COLORREF fillColor, COLORREF colorLine, int thickness) : Figure(P1, P2, fillColor,colorLine, thickness) {}

Circle::~Circle() {};

void Circle::innerDraw(CDC* dc) {
	CPoint P1, P2;
	P1 = getP1();
	P2 = getP2();
	dc->Ellipse(P1.x, P1.y, P2.x, P2.y);
}

void Circle::redefine(CPoint P1, CPoint P2) {
	setP1(P1);
	setP2(P2);
}

void Circle::Serialize(CArchive& ar) {
	CObject::Serialize(ar);
	COLORREF fillColor, colorLine;
	CPoint p1, p2;
	int thickness;

	if (ar.IsStoring()) {
		ar << getP1();
		ar << getP2();
		ar << getColorLine();
		ar << getFillColor();
		ar << getThickness();
	}
	else {
		ar >> p1;
		ar >> p2;
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

bool Circle::isInside(const CPoint& P) const {
	CPoint p1, p2;
	p1 = getP1();
	p2 = getP2();
	return (P.x >= p1.x && P.x <= p2.x && P.y >= p1.y && P.y <= p2.y);
};