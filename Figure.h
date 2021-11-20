#pragma once
#include "pch.h"

class Figure : public CObject {
	DECLARE_SERIAL(Figure);
private:
	CPoint P1;
	CPoint P2;
	COLORREF fillColor, colorLine;
	//CPen *pen;
	//CPen* pOldPen;
	//CBrush *brush;
	//CBrush* oldBrush;
	int thickness = 1;
	int static figureCount;
public:
	Figure();
	Figure(CPoint p1, CPoint p2, COLORREF fillColor = 16777215, COLORREF colorLine = 0, int thickness = 1);
	virtual ~Figure();
	CPoint getP1() const;
	CPoint getP2() const;
	COLORREF getColorLine() const;
	COLORREF getFillColor() const;
	void setColorLine(COLORREF colorLine);
	void setFillColor(COLORREF fillColor);
	int getThickness() const;
	void setThickness(int thickness);
	void setP1(const CPoint p);
	void setP2(const CPoint p);
	virtual void Serialize(CArchive& ar);
	virtual void draw(CDC* dc);
	virtual void innerDraw(CDC* dc) {};
	virtual void redefine(CPoint p1, CPoint p2) { P1 = p1; P2 = p2; };
	virtual bool isInside(const CPoint& P) const;
	virtual void shift(int dx, int dy);
};

