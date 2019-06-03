#pragma once

#include "RVektor.h"

class SquarePlate;
class SmallSquare {
// Properties
public:
	double side; //side length in meter
	double aDensity;
	int maskCoeff = 1;
	RVektor drawCenter; //Center of the square in meter, using for drawing
	RVektor calculationCenter; //Center of the square in meter, using for calculate
	CDocument *pOwner;
	SquarePlate *ownerPlate;

// Methods
public:
	SmallSquare();
	~SmallSquare();

	void Draw(CDC *pDc);
	void SetOwner(CDocument* pDoc);
	void SetOwnerPlate(SquarePlate* ownerPlate);
	void SetDrawingCenter(const RVektor& aVec); //Changes center to aVec
	void SetDrawingCenter(const double aX, const double aY, const double aZ);
	void SetCalculationCenter(const RVektor& aVec); //Changes center to aVec
	void SetCalculationCenter(const double aX, const double aY, const double aZ);
	void SetSide(const double aSide); //change the value of side
	void SetDensity(double aDens);
	void SetMask(const int maskCoeff);
	double GetSide() const;
	double CouplingCoefficient(const SmallSquare& aSq);
	double SelfCoupling();
	double DistanceCoupling(const SmallSquare& aSq);
	bool IsSelfCoupling(const SmallSquare& aSq);
	RVektor GetDrawingCenter() const;
	RVektor GetCalculationCenter() const ;
	SquarePlate* GetOwnerPlate();
};