// Copyright Epic Games, Inc. All Rights Reserved.


#include "ShootThemUpGameModeBase.h"
#include "Player/STUBaseCharacter.h"
#include "Player/STUPlayerController.h"
#include "UI/STUHUD.h"

AShootThemUpGameModeBase::AShootThemUpGameModeBase()
{
	DefaultPawnClass = ASTUBaseCharacter::StaticClass();
	PlayerControllerClass = ASTUPlayerController::StaticClass();
	HUDClass = ASTUHUD::StaticClass();
}