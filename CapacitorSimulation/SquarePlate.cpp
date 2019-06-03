#include "stdafx.h"
#include "RVektor.h"
#include "SmallSquare.h"
#include "Vector.h"
#include "SquarePlate.h"

//void(*RMatrix::ErrHdlr)(char*) = RMatrix::DefaultErrHdlr;
//char RMatrix::ErrFlag = 0;
//--------------------------------------------------------------
SquarePlate::SquarePlate() {
	nX = 20;
	nY = 32;
	nN = nX*nY;
	plateSizeX = 0.1;// platesize x dimension in meter
	plateSizeY = 0.16;// platesize x dimension in meter
	potPlate = 0;//Potential of the plate is 1 Volt
	drawCenterX = 0;
	drawCenterY = 0;
	drawCenterZ = 0;
	calCenterX = 0;
	calCenterY = 0;
	calCenterZ = 0;
}
//--------------------------------------------------------------
SquarePlate::~SquarePlate() {}
//--------------------------------------------------------------
void SquarePlate::CreatePlate(const int potPlate) {
	this->potPlate = potPlate; // set potential of the plate
	vPlate.SetDim(nN);// set number of small plate
	double delX = plateSizeX / nX; // x-distance distance between small plates in meter
	double delY = plateSizeY / nY; // y-distance distance between small plates in meter

	int iN = 0;
	for (int iX = -nX / 2; iX < nX / 2; iX++) {
		double x = delX * iX;
		for (int iY = nY / 2; iY >= -(nY - 1) / 2; iY--) {
			double y = delY * iY;
			vPlate[iN].SetDrawingCenter(x, y, drawCenterZ);
			vPlate[iN].SetCalculationCenter(x, y, calCenterZ);
			vPlate[iN].SetSide(delX);
			vPlate[iN].SetOwnerPlate(this);
			vPlate[iN].SetMask(masks[iN]);
			iN++;
		}
	}
}
//--------------------------------------------------------------
void SquarePlate::SetDrawCenter(const double drawCenterX, const double drawCenterY, const double drawCenterZ) {
	this->drawCenterX = drawCenterX;
	this->drawCenterY = drawCenterY;
	this->drawCenterZ = drawCenterZ;
}
//--------------------------------------------------------------
void SquarePlate::SetCalCenter(const double calCenterX, const double calCenterY, const double calCenterZ) {
	this->calCenterX = calCenterX;
	this->calCenterY = calCenterY;
	this->calCenterZ = calCenterZ;
}
//--------------------------------------------------------------
void SquarePlate::Draw(CDC *pDc) {
	for (int i = 0; i < nN; i++) {
		vPlate[i].Draw(pDc);
	}
}
//--------------------------------------------------------------
void SquarePlate::SetOwner(CDocument *pDoc) {
	pOwner = pDoc;
	for (int i = 0; i < nN; i++) {
		vPlate[i].SetOwner(pDoc);
	}
}
//--------------------------------------------------------------