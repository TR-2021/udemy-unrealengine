// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Weapon/STUBaseWeapon.h"
#include "STURifleWeapon.generated.h"

/**
 * 
 */
UCLASS()
class SHOOTTHEMUP_API ASTURifleWeapon : public ASTUBaseWeapon
{

	GENERATED_BODY()
  public:
	ASTURifleWeapon();
	virtual void MakeShot()  override;
	virtual void StartFire()  override;
	virtual void StopFire()  override;
};
