#include "pch.h"
#include "framework.h"
#include "MFCApplication.h"
#include "MFCApplicationDlg.h"
#include "afxdialogex.h"
#include "Square.h"
#include "Triangle.h"
#include "Line.h"
#include "Circle.h"
#include "Square.h"
#include "Parallelogram.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


CMFCApplicationDlg::CMFCApplicationDlg(CWnd* pParent /*=nullptr*/)
	: CDialogEx(IDD_MFCAPPLICATION_DIALOG, pParent)
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CMFCApplicationDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_RADIO_TRIANGLE1, radioBtnTriangle);
	DDX_Control(pDX, IDC_RADIO_RECTANGLE, radioBtnRectangle);
	DDX_Control(pDX, IDC_RADIO_LINE, radioBtnLine);
	DDX_Control(pDX, IDC_STATIC_X, xVar);
	DDX_Control(pDX, IDC_STATIC_Y, yVar);
	DDX_Control(pDX, IDC_COMBO_THICKNESS, comboBoxThickness);
}

BEGIN_MESSAGE_MAP(CMFCApplicationDlg, CDialogEx)
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_WM_LBUTTONDOWN()
	ON_WM_LBUTTONUP()
	ON_WM_MOUSEMOVE()
	ON_BN_CLICKED(IDC_RADIO_RECTANGLE, &CMFCApplicationDlg::OnBnClickedRadioRectangle)
	ON_BN_CLICKED(IDC_RADIO_TRIANGLE1, &CMFCApplicationDlg::OnBnClickedRadioTriangle1)
	ON_BN_CLICKED(IDC_RADIO_LINE, &CMFCApplicationDlg::OnBnClickedRadioLine)
	ON_BN_CLICKED(IDABORT, &CMFCApplicationDlg::OnBnClickedAbort)
	ON_BN_CLICKED(IDC_BUTTON1_DELETE_BTN, &CMFCApplicationDlg::OnBnClickedButton1DeleteBtn)
	ON_BN_CLICKED(IDC_BUTTON_CLEAR, &CMFCApplicationDlg::OnBnClickedButtonClear)
	ON_BN_CLICKED(IDC_RADIO_CIRCLE, &CMFCApplicationDlg::OnBnClickedRadioCircle)
ON_BN_CLICKED(IDC_BUTTON_FILL_FIGURE, &CMFCApplicationDlg::OnBnClickedButtonFillFigure)
ON_BN_CLICKED(IDC_RADIO_SQUARE, &CMFCApplicationDlg::OnBnClickedRadioSquare)
ON_CBN_SELCHANGE(IDC_COMBO_THICKNESS, &CMFCApplicationDlg::OnCbnSelchangeComboThickness)
ON_COMMAND(ID_FILE_SAVEFILE, &CMFCApplicationDlg::OnFileSavefile)
ON_COMMAND(ID_FILE_LOADFILE, &CMFCApplicationDlg::OnFileLoadfile)
ON_BN_CLICKED(IDC_RADIO_PARALLELOGRAM, &CMFCApplicationDlg::OnBnClickedRadioParallelogram)
//ON_WM_SETCURSOR()
ON_WM_SETCURSOR()
END_MESSAGE_MAP()


// CMFCApplicationDlg message handlers

BOOL CMFCApplicationDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();
	SetIcon(m_hIcon, TRUE);		
	SetIcon(m_hIcon, FALSE);
	CString str, title;
	title = "MFC-Paint";
	SetWindowText(title);
	CheckRadioButton(IDC_RADIO_RECTANGLE, IDC_RADIO_CIRCLE, IDC_RADIO_RECTANGLE);

	//Menu setup
	pMenu = new CMenu();
	pMenu->LoadMenu(IDR_MENU1);
	SetMenu(pMenu);

	// Init the Combo Box (Thickness of the line)
	for (int i = 1; i <= 7; i++) {
		str.Format(_T(" %d "), i);
		comboBoxThickness.AddString(str);
	}
	comboBoxThickness.SetCurSel(0);

	return TRUE;
}


void CMFCApplicationDlg::OnPaint()
{
	int figIndex = 0;
	if (IsIconic())
	{
		CPaintDC dc(this); // device context for painting

		SendMessage(WM_ICONERASEBKGND, reinterpret_cast<WPARAM>(dc.GetSafeHdc()), 0);

		// Center icon in client rectangle
		int cxIcon = GetSystemMetrics(SM_CXICON);
		int cyIcon = GetSystemMetrics(SM_CYICON);
		CRect rect;
		GetClientRect(&rect);
		int x = (rect.Width() - cxIcon + 1) / 2;
		int y = (rect.Height() - cyIcon + 1) / 2;

		// Draw the icon
		dc.DrawIcon(x, y, m_hIcon);
	}
	else
	{
		CPaintDC dc(this);
		for (int i = 0; i < figs.GetSize(); i++)
			figs[i]->draw(&dc);
	}
}

HCURSOR CMFCApplicationDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}



void CMFCApplicationDlg::OnLButtonDown(UINT nFlags, CPoint point)
{
	start = point;
	for (int i = 0; i < figs.GetSize(); i++)
		if (figs[i]->isInside(start)) {
			isInside = true;
			selectedFigure = figs[i];
			toDeleteIndex = i;
		}
	if(!isInside)
		switch (chooseFig)
		{
		case RECTANGLE:
			figs.Add(new RectangleF(start, start, fillColor,colorLine, thicknessLevel));
			break;
		case TRIANGLE:
			figs.Add(new Triangle(start, start, fillColor, colorLine, thicknessLevel));
			break;
		case LINE:
			figs.Add(new Line(start, start, colorLine, thicknessLevel));
			break;
		case CIRCLE:
			figs.Add(new Circle(start, start, fillColor, colorLine, thicknessLevel));
			break;
		case SQUARE:
			figs.Add(new Square(start,start, fillColor, colorLine, thicknessLevel));
			break;
		case PARALLELOGRAM:
			figs.Add(new Parallelogram(start, start, fillColor, colorLine, thicknessLevel));
			break;
		default:
			break;
		}

	if (toDelete && isInside) {
		figs.RemoveAt(toDeleteIndex);
		Invalidate();
	}

	isPressed = true;

	CDialogEx::OnLButtonDown(nFlags, point);
}


void CMFCApplicationDlg::OnLButtonUp(UINT nFlags, CPoint point)
{
	if (isPressed) {
		if (isInside) {
			isInside = false;
			isPressed = false;
		}
		else {
			isPressed = false;
			figs[figs.GetSize() - 1]->redefine(start, point);
			Invalidate();
		}
	}

	CDialogEx::OnLButtonUp(nFlags, point);
}


void CMFCApplicationDlg::OnMouseMove(UINT nFlags, CPoint point)
{	
	if(!toDelete){
		if (isPressed) {
			if (isInside) {
				selectedFigure->shift(point.x,point.y);
				Invalidate();
			}
			else {
				end = point;
				figs[figs.GetSize() - 1]->redefine(start, end);
				Invalidate();
			}
		}
	}
	
	pointCor.Format(_T("X: %d"), point.x);
	xVar.SetWindowText(pointCor);

	pointCor.Format(_T("Y: %d"), point.y);
	yVar.SetWindowText(pointCor);

	CDialogEx::OnMouseMove(nFlags, point);
}


void CMFCApplicationDlg::OnBnClickedRadioRectangle()
{
	chooseFig = RECTANGLE;
	toDelete = false;
}


void CMFCApplicationDlg::OnBnClickedRadioTriangle1()
{
	chooseFig = TRIANGLE;
	toDelete = false;
}


void CMFCApplicationDlg::OnBnClickedRadioLine()
{
	chooseFig = LINE;
	toDelete = false;
}

void CMFCApplicationDlg::OnBnClickedRadioCircle()
{
	chooseFig = CIRCLE;
	toDelete = false;
}

void CMFCApplicationDlg::OnBnClickedRadioSquare()
{
	chooseFig = SQUARE;
	toDelete = false;
}

void CMFCApplicationDlg::OnBnClickedRadioParallelogram()
{
	chooseFig = PARALLELOGRAM;
	toDelete = false;
}

void CMFCApplicationDlg::OnBnClickedAbort()
{
	CColorDialog dlg;
	if (dlg.DoModal() == IDOK)
	{
		colorLine = dlg.GetColor();
	}
}


void CMFCApplicationDlg::OnBnClickedButtonFillFigure()
{
	CColorDialog dlg;
	if (dlg.DoModal() == IDOK)
	{
		fillColor = dlg.GetColor();
	}
}


void CMFCApplicationDlg::OnBnClickedButton1DeleteBtn()
{
	//SetCursor(::LoadCursor(NULL, IDC_ARROW));
	//HCURSOR hOldCursor = NULL;
	//hOldCursor = SetCursor(LoadCursor(NULL, IDC_HAND));
	//SetCursor(AfxGetApp()->LoadStandardCursor(IDC_HAND));
	//SetCursor(hOldCursor);
	if (!toDelete)
		toDelete = true;
	else
		toDelete = false;

}


void CMFCApplicationDlg::OnBnClickedButtonClear()
{
	figs.RemoveAll();
	Invalidate();
}


void CMFCApplicationDlg::OnCbnSelchangeComboThickness()
{
	thicknessLevel = comboBoxThickness.GetCurSel() + 1;
}


void CMFCApplicationDlg::OnFileSavefile()
{
	CFileDialog dlg(FALSE, _T(".figs"), NULL, 0, _T("Figures (*.figs)|*.figs|All Files (*.*)|*.*||"));
	CString filename;
	if (dlg.DoModal() == IDOK)
	{
		filename = dlg.GetPathName();
		CFile file(filename, CFile::modeCreate | CFile::modeWrite);
		CArchive ar(&file, CArchive::store);
		figs.Serialize(ar);
		ar.Close();
		file.Close();
	}
}


void CMFCApplicationDlg::OnFileLoadfile()
{
	CFileDialog dlg(TRUE, _T(".figs"), NULL, 0, _T("Figures (*.figs)|*.figs|All Files (*.*)|*.*||"));
	CString filename;
	if (dlg.DoModal() == IDOK)
	{
		filename = dlg.GetPathName();
		CFile file(filename, CFile::modeRead);
		CArchive ar(&file, CArchive::load);
		figs.Serialize(ar);
		ar.Close();
		file.Close();
		Invalidate();
	}
}


BOOL CMFCApplicationDlg::OnSetCursor(CWnd* pWnd, UINT nHitTest, UINT message)
{
	SetCursor(AfxGetApp()->LoadStandardCursor(IDC_HAND));

	return CDialogEx::OnSetCursor(pWnd, nHitTest, message);
}
