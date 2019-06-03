// CapacitorSimulationDoc.h : interface of the CCapacitorSimulationDoc class
#pragma once


#include "Capacitor.h"


class CCapacitorSimulationDoc: public CDocument {
protected: // create from serialization only
	CCapacitorSimulationDoc() noexcept;
	DECLARE_DYNCREATE(CCapacitorSimulationDoc)

// Attributes
public:
	double wxScreen; //xWidth of the screen
	double wyScreen; //yWidth of the screen
	double xCenter;  // xcenter of screen
	double yCenter;  //yCenter of Screen
	double scaleFac; //scale factor in points/m
	Capacitor capacitor;

// Operations
public:
	void SetCapacitorCenters();
	void DrawDocument(CDC *pDc);
	CPoint VecToScreen(SmallSquare & aSq);
	int SideToScreen(double aSide); //Transformation to Screen
	CRect SquareToScreen(SmallSquare& aSq); //Square to CRect
	bool DoCalculation(); //solves the numerical problem

// Overrides
public:
	virtual BOOL OnNewDocument();
	virtual void Serialize(CArchive& ar);
#ifdef SHARED_HANDLERS
	virtual void InitializeSearchContent();
	virtual void OnDrawThumbnail(CDC& dc, LPRECT lprcBounds);
#endif // SHARED_HANDLERS

// Implementation
public:
	virtual ~CCapacitorSimulationDoc();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

// Generated message map functions
protected:
	DECLARE_MESSAGE_MAP()

#ifdef SHARED_HANDLERS
	// Helper function that sets search content for a Search Handler
	void SetSearchContent(const CString& value);
#endif // SHARED_HANDLERS
};
