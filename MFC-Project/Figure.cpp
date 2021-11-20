#include "pch.h"
#include "Figure.h"

IMPLEMENT_SERIAL(Figure, CObject, 1)

int Figure::figureCount = 0;

Figure::Figure() {
	P1 = CPoint(0, 0);
	P2 = CPoint(0, 0);
	colorLine = 0;
	thickness = 1;
	fillColor = 16777215;
	figureCount++;
}

Figure::Figure(CPoint p1, CPoint p2, COLORREF newFillColor, COLORREF newColorLine, int newThickness) {
	P1 = p1;
	P2 = p2;
	colorLine = newColorLine;
	fillColor = newFillColor;
	thickness = newThickness;
	figureCount++;
}

Figure::~Figure() {
	--figureCount;
}

void Figure::draw(CDC* dc) {
	CPen pen(PS_SOLID, getThickness(), getColorLine());
	CPen* pOldPen = dc->SelectObject(&pen);
	CBrush brush(getFillColor());
	CBrush* oldBrush = dc->SelectObject(&brush);

	innerDraw(dc);
	dc->SelectObject(pOldPen);
	dc->SelectObject(oldBrush);
}

bool Figure::isInside(const CPoint &P) const {
	return (P1.x <= P.x && P.x <= P2.x || P1.x >= P.x && P.x >= P2.x) &&
		(P1.y <= P.y && P.y <= P2.y || P1.y >= P.y && P.y >= P2.y);
}

void Figure::shift(int dx, int dy) {
	P1.x = dx - P1.x;
	P1.y = dy - P1.y;
	P2.x = dx - P2.x;
	P2.y = dy - P2.y;
}

void Figure::Serialize(CArchive& ar) {
	CObject::Serialize(ar);
	if (ar.IsStoring()) {
		ar << P1;
		ar << P2;
		ar << colorLine;
		ar << fillColor;
		ar << thickness;
	}
	else {
		ar >> P1;
		ar >> P2;
		ar >> colorLine;
		ar >> fillColor;
		ar >> thickness;
	}
}

CPoint Figure::getP1() const {
	return P1;
}

CPoint Figure::getP2() const {
	return P2;
}

void Figure::setP1(const CPoint newP){
	P1 = newP;
}

void Figure::setP2(const CPoint newP){
	P2 = newP;
}

COLORREF Figure::getColorLine() const {
	return colorLine;
};

COLORREF Figure::getFillColor() const {
	return fillColor;
};

void Figure::setColorLine(COLORREF newColorLine) {
	colorLine = newColorLine;
};

void Figure::setFillColor(COLORREF newFillColor) {
	fillColor = newFillColor;
};

int Figure::getThickness() const {
	return thickness;
};

void Figure::setThickness(int newThickness){
	thickness = newThickness;
};


