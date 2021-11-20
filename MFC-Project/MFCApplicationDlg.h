
// MFCApplicationDlg.h : header file
//

#pragma once
#include "Figure.h"

const int RECTANGLE{ 1 };
const int TRIANGLE{ 2 };
const int LINE{ 3 };
const int CIRCLE{ 4 };
const int SQUARE{ 5 };
const int PARALLELOGRAM{ 6 };

// CMFCApplicationDlg dialog
class CMFCApplicationDlg : public CDialogEx
{
// Construction
public:
	CMFCApplicationDlg(CWnd* pParent = nullptr);	// standard constructor
	CPoint start, end;
	bool isPressed = false;
	bool isInside = false;
	bool toDelete = false;
	int toDeleteIndex = -1;
	int thicknessLevel = -1;
	Figure *selectedFigure;
	CTypedPtrArray<CObArray, Figure*> figs;
	int chooseFig = 1;
	COLORREF colorLine, fillColor = 16777215;
	CString pointCor;
	CToolBar toolBar;
	CMenu* pMenu;
	
// Dialog Data
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_MFCAPPLICATION_DIALOG };
	
#endif

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV support


// Implementation
protected:
	HICON m_hIcon;

	// Generated message map functions
	virtual BOOL OnInitDialog();
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnLButtonDown(UINT nFlags, CPoint point);
	afx_msg void OnLButtonUp(UINT nFlags, CPoint point);
	afx_msg void OnMouseMove(UINT nFlags, CPoint point);
	afx_msg void OnBnClickedRadioRectangle();
	afx_msg void OnBnClickedRadioTriangle1();
	CButton radioBtnTriangle;
	CButton radioBtnRectangle;
	CButton radioBtnLine;
	afx_msg void OnBnClickedRadioLine();
	afx_msg void OnBnClickedAbort();
	afx_msg void OnBnClickedButton1DeleteBtn();
	afx_msg void OnBnClickedButtonClear();
	afx_msg void OnBnClickedButtonSave();
	afx_msg void OnBnClickedButtonLoad();
	afx_msg void OnBnClickedRadioCircle();
	afx_msg void OnBnClickedButtonFillFigure();
	CStatic xVar;
	CStatic yVar;
	afx_msg void OnBnClickedRadioSquare();
	afx_msg void OnCbnSelchangeComboThickness();
	CComboBox comboBoxThickness;
	afx_msg void OnFileSavefile();
	afx_msg void OnFileLoadfile();
	afx_msg void OnBnClickedRadioParallelogram();
//	afx_msg BOOL OnSetCursor(CWnd* pWnd, UINT nHitTest, UINT message);
	afx_msg BOOL OnSetCursor(CWnd* pWnd, UINT nHitTest, UINT message);
};
