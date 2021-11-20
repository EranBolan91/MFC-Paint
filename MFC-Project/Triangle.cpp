#include "pch.h"
#include "Triangle.h"

IMPLEMENT_SERIAL(Triangle, CObject, 1)

Triangle::Triangle() : Figure() {};

Triangle::Triangle(CPoint P1, CPoint P2, COLORREF fillColor, COLORREF colorLine, int thickness) : Figure(P1, P2, fillColor,colorLine, thickness) {
	CPoint p;
}

Triangle::~Triangle() {};

void Triangle::innerDraw(CDC* dc) {
	CPoint arr[3], P1, P2;
	P1 = getP1();
	P2 = getP2();

	arr[0].x = P1.x;
	arr[0].y = P1.y;
	arr[1].x = P2.x;
	arr[1].y = P2.y;
	arr[2].x = P3.x;
	arr[2].y = P2.y;
	dc->Polygon(arr, 3);
}

void Triangle::setP3(const CPoint P){
	P3 = P;
}

void Triangle::redefine(CPoint P1, CPoint P2) {
	P3.x = (P1.x + P2.x) / 2;
	P3.y = (P1.y + P2.y) / 2;
	setP3(P3);
	setP1(P1);
	setP2(P2);
}

void Triangle::Serialize(CArchive& ar) {
	CObject::Serialize(ar);
	COLORREF fillColor, colorLine;
	CPoint p1, p2;
	int thickness;
	if (ar.IsStoring()) {
		ar << getP1();
		ar << getP2();
		ar << P3;
		ar << getColorLine();
		ar << getFillColor();
		ar << getThickness();
	}
	else {
		ar >> p1;
		ar >> p2;
		ar >> P3;
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

bool Triangle::isInside(const CPoint& P) const {
	return (getP1().x <= P.x && P.y <= getP2().y && P.x <= P3.x) ||
		   (getP1().x >= P.x && P.y >= getP2().y && P.x >= P3.x);
}