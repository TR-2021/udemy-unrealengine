// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Pickups/STUBasePickup.h"
#include "STUHealthPickup.generated.h"

/**
 * 
 */
UCLASS()
class SHOOTTHEMUP_API ASTUHealthPickup : public ASTUBasePickup
{
	GENERATED_BODY()
  protected:
	UPROPERTY(EditAnywhere, Category = "Health", meta = (ClampMin = "0.0", ClampMax = "100.0"))
	int32 HealthAmount = 50;
  private:
	virtual bool GivePickupTo(APawn *Player) override;
};
