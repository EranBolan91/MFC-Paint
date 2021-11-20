#pragma once
#include "Figure.h"

class Line : public Figure {
public:
	DECLARE_SERIAL(Line);
	Line();
	Line(CPoint P1, CPoint P2, COLORREF colorLine, int thickness);
	~Line();
	void innerDraw(CDC* dc);
	void Serialize(CArchive& ar);
};
