#include "pch.h"
#include "Line.h"

IMPLEMENT_SERIAL(Line, CObject, 1)

Line::Line() : Figure() {};
Line::Line(CPoint P1, CPoint P2, COLORREF colorLine, int thickness) : Figure(P1, P2, 0,colorLine, thickness) {};
Line::~Line() {};


void Line::innerDraw(CDC* dc){
	dc->MoveTo(getP1().x, getP1().y);
	dc->LineTo(getP2().x, getP2().y);
}

void Line::Serialize(CArchive& ar){
	CObject::Serialize(ar);
	COLORREF colorLine;
	CPoint p1, p2;
	int thickness;
	if (ar.IsStoring()) {
		ar << getP1();
		ar << getP2();
		ar << getColorLine();
		ar << getThickness();
	}
	else {
		ar >> p1;
		ar >> p2;
		ar >> colorLine;
		ar >> thickness;
		setP1(p1);
		setP2(p2);
		setColorLine(colorLine);
		setThickness(thickness);
	}
}