
// CapacitorSimulationView.h : interface of the CCapacitorSimulationView class
//

#pragma once


class CCapacitorSimulationView: public CView {
protected: // create from serialization only
	CCapacitorSimulationView() noexcept;
	DECLARE_DYNCREATE(CCapacitorSimulationView)

	// Attributes
public:
	CCapacitorSimulationDoc* GetDocument() const;

	// Operations
public:

	// Overrides
public:
	virtual void OnDraw(CDC* pDC);  // overridden to draw this view
	virtual BOOL PreCreateWindow(CREATESTRUCT& cs);
protected:
	virtual BOOL OnPreparePrinting(CPrintInfo* pInfo);
	virtual void OnBeginPrinting(CDC* pDC, CPrintInfo* pInfo);
	virtual void OnEndPrinting(CDC* pDC, CPrintInfo* pInfo);

	// Implementation
public:
	virtual ~CCapacitorSimulationView();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:

	// Generated message map functions
protected:
	afx_msg void OnFilePrintPreview();
	afx_msg void OnRButtonUp(UINT nFlags, CPoint point);
	afx_msg void OnContextMenu(CWnd* pWnd, CPoint point);
	afx_msg void Calculate();
	DECLARE_MESSAGE_MAP()
};

#ifndef _DEBUG  // debug version in CapacitorSimulationView.cpp
inline CCapacitorSimulationDoc* CCapacitorSimulationView::GetDocument() const {
	return reinterpret_cast<CCapacitorSimulationDoc*>(m_pDocument);
}
#endif

