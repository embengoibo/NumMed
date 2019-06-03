
// CapacitorSimulationView.cpp : implementation of the CCapacitorSimulationView class
//

#include "stdafx.h"
// SHARED_HANDLERS can be defined in an ATL project implementing preview, thumbnail
// and search filter handlers and allows sharing of document code with that project.
#ifndef SHARED_HANDLERS
#include "CapacitorSimulation.h"
#endif

#include "CapacitorSimulationDoc.h"
#include "CapacitorSimulationView.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// CCapacitorSimulationView

IMPLEMENT_DYNCREATE(CCapacitorSimulationView, CView)

BEGIN_MESSAGE_MAP(CCapacitorSimulationView, CView)
	// Standard printing commands
	ON_COMMAND(ID_FILE_PRINT, &CView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_DIRECT, &CView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_PREVIEW, &CCapacitorSimulationView::OnFilePrintPreview)
	ON_COMMAND(ID_EDIT_DOCALCULATE, &CCapacitorSimulationView::Calculate)
	ON_WM_CONTEXTMENU()
	ON_WM_RBUTTONUP()
END_MESSAGE_MAP()

// CCapacitorSimulationView construction/destruction

CCapacitorSimulationView::CCapacitorSimulationView() noexcept {
	// TODO: add construction code here

}

CCapacitorSimulationView::~CCapacitorSimulationView() {}

BOOL CCapacitorSimulationView::PreCreateWindow(CREATESTRUCT& cs) {
	// TODO: Modify the Window class or styles here by modifying
	//  the CREATESTRUCT cs

	return CView::PreCreateWindow(cs);
}

// CCapacitorSimulationView drawing

void CCapacitorSimulationView::OnDraw(CDC* pDC) {
	

	CCapacitorSimulationDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);
	if (!pDoc)
		return;

	// TODO: add draw code for native data here
	pDoc->DrawDocument(pDC);
}


// CCapacitorSimulationView printing


void CCapacitorSimulationView::OnFilePrintPreview() {
#ifndef SHARED_HANDLERS
	AFXPrintPreview(this);
#endif
}

BOOL CCapacitorSimulationView::OnPreparePrinting(CPrintInfo* pInfo) {
	// default preparation
	return DoPreparePrinting(pInfo);
}

void CCapacitorSimulationView::OnBeginPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/) {
	// TODO: add extra initialization before printing
}

void CCapacitorSimulationView::OnEndPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/) {
	// TODO: add cleanup after printing
}

void CCapacitorSimulationView::OnRButtonUp(UINT /* nFlags */, CPoint point) {
	ClientToScreen(&point);
	OnContextMenu(this, point);
}

void CCapacitorSimulationView::OnContextMenu(CWnd* /* pWnd */, CPoint point) {
#ifndef SHARED_HANDLERS
	theApp.GetContextMenuManager()->ShowPopupMenu(IDR_POPUP_EDIT, point.x, point.y, this, TRUE);
#endif
}


// CCapacitorSimulationView diagnostics

#ifdef _DEBUG
void CCapacitorSimulationView::AssertValid() const {
	CView::AssertValid();
}

void CCapacitorSimulationView::Dump(CDumpContext& dc) const {
	CView::Dump(dc);
}

CCapacitorSimulationDoc* CCapacitorSimulationView::GetDocument() const // non-debug version is inline
{
	ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(CCapacitorSimulationDoc)));
	return (CCapacitorSimulationDoc*)m_pDocument;
}
#endif //_DEBUG


// CCapacitorSimulationView message handlers
void CCapacitorSimulationView::Calculate() {
	MessageBox(L"I will try to do the solution", L"DoSolution");
	CCapacitorSimulationDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);
	if (!pDoc->DoCalculation())
		MessageBox(L"Error occur", L"Error");
	else {
		MessageBox(L"Fine it worked", L"Hello");
		Invalidate(true);
	}
}
