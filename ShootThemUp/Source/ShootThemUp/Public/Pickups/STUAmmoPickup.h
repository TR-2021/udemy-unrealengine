// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Pickups/STUBasePickup.h"
#include "STUAmmoPickup.generated.h"

class ASTUBaseWeapon;

UCLASS()
class SHOOTTHEMUP_API ASTUAmmoPickup : public ASTUBasePickup
{
	GENERATED_BODY()
  protected:
	UPROPERTY(EditAnywhere, Category = "Pickup", meta = (ClampMin = "1.0", ClampMax = "10.0"))
	int32 ClipAmount=10;

	UPROPERTY(EditAnywhere, Category = "Pickup")
	TSubclassOf<ASTUBaseWeapon> WeaponType;

  private:
	virtual bool GivePickupTo(APawn *Player) override;
};
