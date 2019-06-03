#pragma once


#include "SquarePlate.h"
#include "RMatrix.h"
#include "SmallSquare.h"
#include "Vector.h"
#include <vector>


class Capacitor {
// Properties
public:
	int nN; // total small square of 2 plates 
	double distance; // distance between two plate in metter
	double totalCharge;
	SquarePlate groundPlate;
	SquarePlate upperPlate;
	RVektor gmVec;
	RMatrix aMa;
	RVektor chargeVec;
	std::vector<SmallSquare*> vPlate;

// Methods
public:
	Capacitor();
	~Capacitor();
	
	void Draw(CDC *pDc);
	void CreateCapacitor(const int groundPlatePot, const int upperPlatePot);
	void SetDistance(const double distance);
	void SetGroundPlateDisplayCenter(const double centerX, const double centerY);
	void SetGroundPlateCalculationCenter(const double centerX, const double centerY);
	void SetUpperPlateDisplayCenter(const double centerX, const double centerY);
	void SetUpperPlateCalculationCenter(const double centerX, const double centerY);
	void SetOwner(CDocument *pDoc);
	void CreateMatrix();
	void CreateGmVector();
	bool FindChargeDistribution();
	void CalculateTotalCharge();
};

