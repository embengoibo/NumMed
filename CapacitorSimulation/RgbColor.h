#pragma once

#include <afxwin.h>
#include <iostream>

//-------------------------------------------------------------
class RgbColor: public CObject {
	DECLARE_SERIAL(RgbColor)
protected:
	int red;
	int green;
	int blue;

public:
	RgbColor();
	RgbColor(COLORREF aCol);
	RgbColor(int redIndx, int greenIndx, int blueIndx);
	RgbColor(const RgbColor &aColor);
	RgbColor operator=(const RgbColor& aColor);
	void Serialize(CArchive &ar);
	void SetGreen() { red = 0; green = 255;  blue = 0; };
	void SetRed() { red = 255; green = 0;  blue = 0; };
	void SetBlue() { red = 0; green = 0;  blue = 255; };
	void SetCyan() { red = 0; green = 255;  blue = 255; };
	void SetMagenta() { red = 255; green = 0;   blue = 255; };
	void SetYellow() { red = 255; green = 255;  blue = 0; };
	void SetWhite() { red = 255; green = 255;  blue = 255; };
	void SetBlack() { red = 0; green = 0;    blue = 0; };
	void SetColor(double aValue);//Farbe als Intensität
	BOOL IsRed() { return (red == 255)&&(green==0)&&(blue == 0); };
	BOOL IsGreen() { return (red == 0)&&(green==255)&&(blue == 0); };
	BOOL IsBlue() { return (red == 0)&&(green==0)&&(blue == 255); };
	BOOL IsBlack() { return (red == 0)&&(green==0)&&(blue == 0); };
	BOOL IsWhite() { return (red == 255)&&(green==255)&&(blue == 255); };
	COLORREF GetColor(float fak);
	COLORREF GetLightColor();
	COLORREF GetDarkColor();

	friend std::istream& operator >> (std::istream& is, RgbColor& aCol);
	friend std::ostream& operator << (std::ostream& os, RgbColor& aCol);
};