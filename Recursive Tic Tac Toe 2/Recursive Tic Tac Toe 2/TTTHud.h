#pragma once

class HUD
{
public:
	HUD();
	~HUD();
	void DrawHUD();
private:
	int HUDStartX;
	int HUDWidth;
	int edgeOffset;
	
	void DrawDividerLine();
	void DrawTurnText();
	void DrawInstructions();
	void DrawWinnerText();
};