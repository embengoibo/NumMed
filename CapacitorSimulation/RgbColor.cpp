#include "stdafx.h"
#include "RgbColor.h"
#include<math.h>

///////////////////////////////////////////////////
// Implementation der Klasse RgbColor
///////////////////////////////////////////////////
IMPLEMENT_SERIAL(RgbColor, CObject, 1)
//-------------------------------------------------
RgbColor::RgbColor() {
	red = 252;
	green = 252;
	blue = 252;
}
//----------------------------------------------------------
RgbColor::RgbColor(COLORREF aCol) {
	red = 0x000000FF & aCol;
	green = (0x0000FF00 & aCol)/0x100;
	blue = (0x00FF0000 & aCol)/0x10000;
}
//----------------------------------------------------------
RgbColor::RgbColor(const RgbColor &aColor) {
	red = aColor.red;
	green = aColor.green;
	blue = aColor.blue;
}
//----------------------------------------------------------
RgbColor::RgbColor(int redIndx, int greenIndx, int blueIndx) {
	red = redIndx;
	green = greenIndx;
	blue = blueIndx;
}
//---------------------------------------------------------
RgbColor RgbColor::operator=(const RgbColor& aColor) {
	red = aColor.red;
	green = aColor.green;
	blue = aColor.blue;
	return *this;
}
//---------------------------------------------------------
void RgbColor::SetColor(double aVal) {
	double pi_2 = 1.57079;
	if (aVal > 1) {
		red = 255;
		green = 0;
		blue = 0;
	} else if (aVal >= 0.0 && aVal <= 1)// Farbe aus der rot-grün-Ebene
	{
		double phi = pi_2*aVal;
		red = 255*sin(phi);
		green = 255*cos(phi);
		blue = 255*sin(2*phi);
	} else if (aVal < 0 && aVal >= -1) {
		double phi = -pi_2*aVal;
		red = 150*sin(2*phi);
		green = 255*cos(phi);
		blue = 255*sin(phi);
	} else if (aVal < -1) {
		red = 0;
		green = 0;
		blue = 255;
	} else {
		red = 0;
		green = 0;
		blue = 0;
	}

}
//---------------------------------------------------------
void RgbColor::Serialize(CArchive &ar) {
	if (ar.IsStoring()) {
		ar << red;
		ar << green;
		ar << blue;
	} else {
		ar >> red;
		ar >> green;
		ar >> blue;
	}
}
//---------------------------------------------------------
COLORREF RgbColor::GetColor(float fak = 1.0) {
	return RGB(fak*red, fak*green, fak*blue);
}
//---------------------------------------------------------
COLORREF RgbColor::GetLightColor() {
	return RGB(red, green, blue);
}
//---------------------------------------------------------
COLORREF RgbColor::GetDarkColor() {
	return RGB(0.7*red, 0.7*green, 0.7*blue);
}
//---------------------------------------------------------
std::istream& operator >> (std::istream& is, RgbColor& aCol) {
	char c;
	is >> c >> aCol.red >> c >> aCol.green >> aCol.blue >>c;

	return is;
}
//---------------------------------------------------------
std::ostream& operator << (std::ostream& os, RgbColor& aCol) {
	os << '('<<aCol.red <<','<< aCol.green<<','<< aCol.blue <<')';

	return os;
}
