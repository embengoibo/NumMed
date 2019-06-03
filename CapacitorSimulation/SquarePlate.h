#pragma once


#include "SmallSquare.h"
#include "Vector.h"


class SquarePlate {
// Properties
public:
	int nX; // number of small square in width
	int nY; // number of small square in height
	int nN; // total number of small square
	double drawCenterX; // x-coordinate of center for drawing pixel
	double drawCenterY; // x-coordinate of center for drawing pixel
	double drawCenterZ; // x-coordinate of center for drawing pixel
	double calCenterX; // x-coordinate of center for drawing pixel
	double calCenterY; // x-coordinate of center for drawing pixel
	double calCenterZ; // x-coordinate of center for drawing pixel
	double plateSizeX; // size X dimension in meter
	double plateSizeY; // size Y dimension in meter
	double potPlate; // potential of the plate in volt
	int *masks;
	CDocument *pOwner; //Owner of the plate
	Vektor<SmallSquare> vPlate;

// Methods
public:
	SquarePlate();
	~SquarePlate();

	void Draw(CDC *pDc); //Draw  whole plate
	void CreatePlate(const int potPlate);
	void SetOwner(CDocument* pDoc);
	void SetDrawCenter(const double drawCenterX, const double drawCenterY, const double drawCenterZ);
	void SetCalCenter(const double calCenterX, const double calCenterY, const double calCenterZ);
};
