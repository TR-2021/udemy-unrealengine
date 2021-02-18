// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/HUD.h"
#include "STUHUD.generated.h"

/**
 *
 */
UCLASS()
class SHOOTTHEMUP_API ASTUHUD : public AHUD
{
	GENERATED_BODY()
  protected:
	virtual void DrawHUD() override;

  private:
	void DrawCrosshair();
};
