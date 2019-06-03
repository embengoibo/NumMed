#include <stdio.h>
#include "stdafx.h"
#include "Capacitor.h"
#include "AlphabetMasks.h"
#include <string>
#include <sstream>
#include <iomanip>

Capacitor::Capacitor() {
	nN = 0;
}
//--------------------------------------------------------------
Capacitor::~Capacitor() {
}
//--------------------------------------------------------------
void Capacitor::SetDistance(const double distance) {
	this->distance = distance; 
	if (vPlate.size() != 0) {
		for (int i = 0; i < upperPlate.nN; i++) {
			vPlate[i]->calculationCenter.SetZ(distance);
		}
	}
}
//--------------------------------------------------------------
void Capacitor::CreateCapacitor(const int groundPlatePot, const int upperPlatePot) {
	groundPlate.masks = new int[groundPlate.nN];
	for (int i = 0; i < groundPlate.nN; i++) {
		groundPlate.masks[i] = FULL_MASK[i];
	}

	upperPlate.masks = new int[upperPlate.nN];
	for (int i = 0; i < upperPlate.nN; i++) {
		upperPlate.masks[i] = O_MASK[i];
	}

	groundPlate.CreatePlate(groundPlatePot);
	upperPlate.CreatePlate(upperPlatePot);

	for (int i = 0; i < upperPlate.nN; i++) {
		if (upperPlate.vPlate[i].maskCoeff == 1) {
			vPlate.push_back(&upperPlate.vPlate[i]);
		}
	}

	for (int i = 0; i < groundPlate.nN; i++) {
		if (groundPlate.vPlate[i].maskCoeff == 1) {
			vPlate.push_back(&groundPlate.vPlate[i]);
		}
	}

	nN = vPlate.size();
}
//--------------------------------------------------------------
void Capacitor::SetGroundPlateDisplayCenter(const double centerX, const double centerY) {
	groundPlate.SetDrawCenter(centerX, centerY, 0);
}
//--------------------------------------------------------------
void Capacitor::SetGroundPlateCalculationCenter(const double centerX, const double centerY) {
	groundPlate.SetCalCenter(centerX, centerY, 0);
}
//--------------------------------------------------------------
void Capacitor::SetUpperPlateDisplayCenter(const double centerX, const double centerY) {
	upperPlate.SetDrawCenter(centerX, centerY, 0);
}
//--------------------------------------------------------------
void Capacitor::SetUpperPlateCalculationCenter(const double centerX, const double centerY) {
	upperPlate.SetCalCenter(centerX, centerY, distance);
}
//--------------------------------------------------------------
void Capacitor::SetOwner(CDocument *pDoc) {
	groundPlate.SetOwner(pDoc);
	upperPlate.SetOwner(pDoc);
}
//--------------------------------------------------------------
void Capacitor::Draw(CDC * pDc) {
	upperPlate.Draw(pDc);
	groundPlate.Draw(pDc);
}
//--------------------------------------------------------------
void Capacitor::CreateMatrix() {
	aMa.SetDimension(nN, nN);
	for (int i = 0; i < nN; i++) {
		for (int j = 0; j < nN; j++) {
			double aVal = vPlate[i]->CouplingCoefficient(*vPlate[j]);
			aMa[i][j] = aVal;
		}
	}
}
//--------------------------------------------------------------
void Capacitor::CreateGmVector() {
	gmVec.SetDim(nN);
	for (int i = 0; i < nN; i++) {
		gmVec[i] = vPlate[i]->ownerPlate->potPlate;
	}
}
//--------------------------------------------------------------
bool Capacitor::FindChargeDistribution() {
	chargeVec.SetDim(nN);
	chargeVec = RealGaussElimination(aMa, gmVec);
	CalculateTotalCharge();
	
	chargeVec.Normalise();
	for (int i = 0; i < nN; i++) {
		vPlate[i]->SetDensity(chargeVec[i]);
	}
	return true;
}
//--------------------------------------------------------------
void Capacitor::CalculateTotalCharge() {
	double aSide = vPlate[0]->GetSide();
	double area = aSide * aSide;
	
	for (int i = 0; i < nN; i++) {
		totalCharge += chargeVec[i];
	}
}
