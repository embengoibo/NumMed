#include "stdafx.h"
#include "Physicon.h"
#include "RVektor.h"
#include "RgbColor.h"
#include "SmallSquare.h"
#include "CapacitorSimulationDoc.h"
//-------------------------------------------------------------
void(*Vektor<SmallSquare>::ErrHdlr)(char*) = Vektor<SmallSquare>::DefaultErrHdlr;
char Vektor<SmallSquare>::ErrFlag = 0;
//-------------------------------------------------------------
SmallSquare::SmallSquare() {
	side = 0.0;
	drawCenter = RVektor(0.0, 0.0, 0.0);
	calculationCenter = RVektor(0.0, 0.0, 0.0);
	aDensity = 0.0;
}
//-------------------------------------------------------------
SmallSquare::~SmallSquare() {}
//-------------------------------------------------------------
void SmallSquare::SetDrawingCenter(const RVektor& aVec) {
	drawCenter = aVec; 
}
//-------------------------------------------------------------
void SmallSquare::SetCalculationCenter(const RVektor& aVec) {
	drawCenter = aVec; 
}
//-------------------------------------------------------------
void SmallSquare::SetDensity(double aDens) { 
	aDensity = aDens; 
}
//-------------------------------------------------------------
void SmallSquare::SetMask(const int maskCoeff) {
	this->maskCoeff = maskCoeff;
}
//-------------------------------------------------------------
void SmallSquare::SetOwner(CDocument* pDoc) {
	pOwner = pDoc; 
}
//-------------------------------------------------------------
void SmallSquare::SetSide(const double aSide) {
	side = aSide;
}
//-------------------------------------------------------------
void SmallSquare::SetDrawingCenter(const double aX, const double aY, const double aZ) {
	drawCenter.SetX(aX);
	drawCenter.SetY(aY);
	drawCenter.SetZ(aZ);
}
//-------------------------------------------------------------
void SmallSquare::SetCalculationCenter(const double aX, const double aY, const double aZ) {
	calculationCenter.SetX(aX);
	calculationCenter.SetY(aY);
	calculationCenter.SetZ(aZ);
}
//-------------------------------------------------------------
SquarePlate * SmallSquare::GetOwnerPlate() {
	return this->ownerPlate;
}
//-------------------------------------------------------------
RVektor SmallSquare::GetDrawingCenter() const { 
	return drawCenter;
}
//-------------------------------------------------------------
RVektor SmallSquare::GetCalculationCenter() const { 
	return calculationCenter; 
}
//-------------------------------------------------------------
double SmallSquare::GetSide() const {
	return side; 
}
//-------------------------------------------------------------
bool SmallSquare::IsSelfCoupling(const SmallSquare& aSq) {
	return (calculationCenter == aSq.calculationCenter);
}
//-------------------------------------------------------------
double SmallSquare::CouplingCoefficient(const SmallSquare& aSq) {
	if (IsSelfCoupling(aSq)) { 
		return SelfCoupling(); 
	} else {
		return DistanceCoupling(aSq);
	}
}
//-------------------------------------------------------------
double SmallSquare::SelfCoupling() {
	double retVal = side / (PI*EPS_0);
	retVal *= log(sqrt(2.0) + 1.0);
	return retVal;
}
//-------------------------------------------------------------
double SmallSquare::DistanceCoupling(const SmallSquare& aSq) {
	double dis = (calculationCenter - aSq.calculationCenter).Norm();
	double retVal = side*side;
	retVal /= (4.0*PI*EPS_0*dis);
	return retVal;
}
//-------------------------------------------------------------
void SmallSquare::Draw(CDC *pDc) {
	CRect aRec = ((CCapacitorSimulationDoc*)pOwner)->SquareToScreen(*this);
	int left = aRec.left;
	int top = aRec.top;
	int right = aRec.right;
	int bot = aRec.bottom;
	pDc->MoveTo(left, bot);
	pDc->LineTo(left, top);
	pDc->LineTo(right, top);
	pDc->LineTo(right, bot);
	pDc->LineTo(left, bot);
	RgbColor aCol;
	if (aDensity == 0.) { 
		aCol.SetWhite(); 
	} else { 
		aCol.SetColor(aDensity); 
	}
	CBrush myBrush;
	myBrush.CreateSolidBrush(aCol.GetColor(1.));
	CBrush* pTempBrush = NULL;
	pTempBrush = (CBrush*)pDc->SelectObject(&myBrush);
	pDc->Rectangle(aRec);
	pDc->SelectObject(pTempBrush);
}
//-------------------------------------------------------------
void SmallSquare::SetOwnerPlate(SquarePlate* ownerPlate) {
	this->ownerPlate = ownerPlate;
}
//-------------------------------------------------------------