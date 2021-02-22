// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Weapon/STUBaseWeapon.h"
#include "STURifleWeapon.generated.h"

/**
 * 
 */
class USTUWeaponFXComponent;
class UNiagaraComponent;
class UNiagaraSystem;
UCLASS()
class SHOOTTHEMUP_API ASTURifleWeapon : public ASTUBaseWeapon
{

	GENERATED_BODY()
  public:
	ASTURifleWeapon();
	virtual void MakeShot()  override;
	virtual void StartFire()  override;
	virtual void StopFire()  override;

  protected:
	UPROPERTY(EditAnywhere, Category = "VFX")
	USTUWeaponFXComponent *WeaponFXComponent;
	
	UPROPERTY()
	UNiagaraComponent *MuzzzleFXComponent;
	void InitMuzzleFX();
	void SetMuzzleVisibility(bool state);
};
