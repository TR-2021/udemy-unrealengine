// Fill out your copyright notice in the Description page of Project Settings.

#include "UI/STUHUD.h"
#include "Engine/Canvas.h"

void ASTUHUD::DrawHUD()
{
	DrawCrosshair();
}

void ASTUHUD::DrawCrosshair()
{
	int32 SizeX = Canvas->SizeX;
	int32 SizeY = Canvas->SizeY;
	const TInterval<float> Center(SizeX / 2, SizeY / 2);
	const float HalfLineSize = 10.0f;
	const float Thickness = 1.0f;
	const FColor Color = FColor::Blue;

	DrawLine(Center.Min - HalfLineSize, Center.Max, Center.Min + HalfLineSize, Center.Max, Color, Thickness);
	DrawLine(Center.Min, Center.Max - HalfLineSize, Center.Min, Center.Max + HalfLineSize, Color, Thickness);
}
