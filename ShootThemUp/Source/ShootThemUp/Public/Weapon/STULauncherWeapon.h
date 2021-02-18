// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Weapon/STUBaseWeapon.h"
#include "STULauncherWeapon.generated.h"

class ASTUProjectile;

UCLASS()
class SHOOTTHEMUP_API ASTULauncherWeapon : public ASTUBaseWeapon
{
	GENERATED_BODY()
  public:
	ASTULauncherWeapon();
	virtual void MakeShot() override;
	virtual void StartFire() override;
	
  protected:
	UPROPERTY(EditAnywhere,Category="Components")
	TSubclassOf<ASTUProjectile> ProjectileClass;
};