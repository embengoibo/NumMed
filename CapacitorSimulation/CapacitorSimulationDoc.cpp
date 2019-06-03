// CapacitorSimulationDoc.cpp : implementation of the CCapacitorSimulationDoc class
#include "stdafx.h"

// SHARED_HANDLERS can be defined in an ATL project implementing preview, thumbnail
// and search filter handlers and allows sharing of document code with that project.
#ifndef SHARED_HANDLERS
#include "CapacitorSimulation.h"
#endif

#include "CapacitorSimulationDoc.h"
#include <propkey.h>

#ifdef _DEBUG
#define new DEBUG_NEW
#endif

// CCapacitorSimulationDoc
IMPLEMENT_DYNCREATE(CCapacitorSimulationDoc, CDocument)
BEGIN_MESSAGE_MAP(CCapacitorSimulationDoc, CDocument)
	ON_COMMAND(ID_FILE_SEND_MAIL, &CCapacitorSimulationDoc::OnFileSendMail)
	ON_UPDATE_COMMAND_UI(ID_FILE_SEND_MAIL, &CCapacitorSimulationDoc::OnUpdateFileSendMail)
END_MESSAGE_MAP()
//--------------------------------------------------------------
// CCapacitorSimulationDoc construction/destruction
CCapacitorSimulationDoc::CCapacitorSimulationDoc() noexcept {
	// TODO: add one-time construction code here

	wxScreen = GetSystemMetrics(SM_CXFULLSCREEN);
	wyScreen = GetSystemMetrics(SM_CYFULLSCREEN);

	xCenter = wxScreen / 2;
	yCenter = wyScreen / 2;

	scaleFac = 4500;

	capacitor.SetDistance(0.005); // by default it is 0.005m
	this->SetCapacitorCenters();
	capacitor.CreateCapacitor(-1 /*volt for ground plate*/, 1 /*volt for upper plate*/);
	capacitor.SetOwner(this);
}
//--------------------------------------------------------------
CCapacitorSimulationDoc::~CCapacitorSimulationDoc() {}
//--------------------------------------------------------------
void CCapacitorSimulationDoc::SetCapacitorCenters() {
	capacitor.SetGroundPlateDisplayCenter(wxScreen / 3, yCenter);
	capacitor.SetGroundPlateCalculationCenter(wxScreen / 3, yCenter);

	capacitor.SetUpperPlateDisplayCenter(wxScreen / 3 * 2, yCenter);
	capacitor.SetUpperPlateCalculationCenter(wxScreen / 3, yCenter);
}
//--------------------------------------------------------------
void CCapacitorSimulationDoc::DrawDocument(CDC * pDc) {
	capacitor.Draw(pDc);
}
//--------------------------------------------------------------
int CCapacitorSimulationDoc::SideToScreen(double aSide) {
	return (int)scaleFac*aSide;
}
//--------------------------------------------------------------
CPoint CCapacitorSimulationDoc::VecToScreen(SmallSquare& aSq) {
	int xSc = scaleFac * aSq.GetDrawingCenter()[0] + aSq.GetOwnerPlate()->drawCenterX;
	int ySc = -scaleFac * aSq.GetDrawingCenter()[1] + aSq.GetOwnerPlate()->drawCenterY;

	return CPoint(xSc, ySc);
}
//--------------------------------------------------------------
CRect CCapacitorSimulationDoc::SquareToScreen(SmallSquare & aSq) {
	CPoint center = VecToScreen(aSq);
	int side = SideToScreen(aSq.GetSide());

	int left = center.x - side / 2;
	int right = center.x + side / 2;
	int top = center.y + side / 2;
	int bot = center.y - side / 2;

	return CRect(left, top, right, bot);
}
//--------------------------------------------------------------
bool CCapacitorSimulationDoc::DoCalculation() {
	capacitor.CreateMatrix();
	capacitor.CreateGmVector();
	return capacitor.FindChargeDistribution();
}
//--------------------------------------------------------------
BOOL CCapacitorSimulationDoc::OnNewDocument() {
	if (!CDocument::OnNewDocument()) { return FALSE; }

	// TODO: add reinitialization code here
	// (SDI documents will reuse this document)
	return TRUE;
}
//--------------------------------------------------------------
// CCapacitorSimulationDoc serialization
void CCapacitorSimulationDoc::Serialize(CArchive& ar) {
	if (ar.IsStoring()) {
		// TODO: add storing code here
	} else {
		// TODO: add loading code here
	}
}
//--------------------------------------------------------------
#ifdef SHARED_HANDLERS
// Support for thumbnails
void CCapacitorSimulationDoc::OnDrawThumbnail(CDC& dc, LPRECT lprcBounds) {
	// Modify this code to draw the document's data
	dc.FillSolidRect(lprcBounds, RGB(255, 255, 255));

	CString strText = _T("TODO: implement thumbnail drawing here");
	LOGFONT lf;

	CFont* pDefaultGUIFont = CFont::FromHandle((HFONT)GetStockObject(DEFAULT_GUI_FONT));
	pDefaultGUIFont->GetLogFont(&lf);
	lf.lfHeight = 36;

	CFont fontDraw;
	fontDraw.CreateFontIndirect(&lf);

	CFont* pOldFont = dc.SelectObject(&fontDraw);
	dc.DrawText(strText, lprcBounds, DT_CENTER | DT_WORDBREAK);
	dc.SelectObject(pOldFont);
}
//--------------------------------------------------------------
// Support for Search Handlers
void CCapacitorSimulationDoc::InitializeSearchContent() {
	CString strSearchContent;
	// Set search contents from document's data.
	// The content parts should be separated by ";"

	// For example:  strSearchContent = _T("point;rectangle;circle;ole object;");
	SetSearchContent(strSearchContent);
}
//--------------------------------------------------------------
void CCapacitorSimulationDoc::SetSearchContent(const CString& value) {
	if (value.IsEmpty()) {
		RemoveChunk(PKEY_Search_Contents.fmtid, PKEY_Search_Contents.pid);
	} else {
		CMFCFilterChunkValueImpl *pChunk = nullptr;
		ATLTRY(pChunk = new CMFCFilterChunkValueImpl);
		if (pChunk != nullptr) {
			pChunk->SetTextValue(PKEY_Search_Contents, value, CHUNK_TEXT);
			SetChunkValue(pChunk);
		}
	}
}

#endif // SHARED_HANDLERS
//--------------------------------------------------------------
// CCapacitorSimulationDoc diagnostics
#ifdef _DEBUG
void CCapacitorSimulationDoc::AssertValid() const {
	CDocument::AssertValid();
}

void CCapacitorSimulationDoc::Dump(CDumpContext& dc) const {
	CDocument::Dump(dc);
}
#endif //_DEBUG
//--------------------------------------------------------------
// CCapacitorSimulationDoc commands