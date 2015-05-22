#include <cstdlib>
#include "TTTHud.h"
#include "GlobalVariables.h"

HUD::HUD()
{
	HUDStartX = std::min(w, h);
	HUDWidth = std::max(w, h) - std::min(w, h);
}

HUD::~HUD()
{

}

void HUD::DrawHUD()
{
	DrawDividerLine();
	DrawTurnText();
	DrawInstructions();
}

void HUD::DrawDividerLine()
{

}

void HUD::DrawTurnText()
{

}

void HUD::DrawInstructions()
{

}

void HUD::DrawWinnerText()
{

}
