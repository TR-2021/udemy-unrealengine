// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "Blueprint/UserWidget.h"
#include "CoreMinimal.h"
#include <Weapon/STUBaseWeapon.h>
#include "STUUserWidget.generated.h"

/**
 *
 */
class USTUHealthComponent;
UCLASS()
class SHOOTTHEMUP_API USTUUserWidget : public UUserWidget
{
	GENERATED_BODY()

  public:
	UFUNCTION(BlueprintCallable)
	float GetHealthPercents();

	UFUNCTION(BlueprintCallable)
	bool GetWeaponUIData(FWeaponUIData &WeaponUIData);
	UFUNCTION(BlueprintCallable)
	bool GetWeaponData(FAmmoData &WeaponData);

	UFUNCTION(BlueprintCallable)
	FString GetFormatedWeaponData(FAmmoData WeaponData);
	UFUNCTION(BlueprintCallable)
	bool IsPlayerAlive();
	UFUNCTION(BlueprintCallable)
	bool IsPlayerSpectating();


	private:
	USTUHealthComponent *GetHealthComponent();
};
