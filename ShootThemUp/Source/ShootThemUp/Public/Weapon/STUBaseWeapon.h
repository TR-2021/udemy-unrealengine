// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "STUBaseWeapon.generated.h"

class USkeletalMeshComponent;

USTRUCT()
struct FAmmoData
{
	GENERATED_USTRUCT_BODY()

	UPROPERTY(EditAnyWhere, Category = "Ammo")
	int32 Bullets;

	UPROPERTY(EditAnyWhere, Category = "Ammo")
	int32 Clips;

	UPROPERTY(EditAnyWhere, Category = "Ammo")
	bool IsInfinity;
};

UCLASS()
class SHOOTTHEMUP_API ASTUBaseWeapon : public AActor
{
	GENERATED_BODY()

  public:
	// Sets default values for this actor's properties
	ASTUBaseWeapon();

  protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	UPROPERTY(EditAnyWhere,BlueprintReadWrite, Category="Components")
	USkeletalMeshComponent* WeaponMesh;

	UPROPERTY(EditAnyWhere, BlueprintReadWrite, Category = "Components")
	float FireRate = 0.1f;

	UPROPERTY(EditAnyWhere, BlueprintReadWrite, Category = "Components")
	float Inaccuracy = 1.0f;

	UPROPERTY(EditAnyWhere, BlueprintReadWrite, Category = "Components")
	float TraceMaxDistance = 1500;

	UPROPERTY(EditAnyWhere, Category = "Ammunition")
	FAmmoData DefaultsAmmoData{20,5,false};

	FTimerHandle FireTimerHandle;
	FName MuzzleSocketName = "MuzzleSocket";

  private:
	UPROPERTY(EditAnyWhere, Category = "Ammunition")
	FAmmoData CurrentAmmoData;

public:
	virtual void MakeShot();
	virtual void StartFire();
	virtual void StopFire();
	FVector GetMuzzleWorldLocation() const;
	APlayerController *GetPlayerController() const;
	bool GetPlayerViewPoint(FVector &ViewLocation, FRotator &ViewRotation) const;
	bool GetTraceData(FVector &TraceStart, FVector &TraceEnd);
	void MakeHit(FHitResult &HitResult, FVector &TraceStart, FVector &TraceEnd);

	void DecreaseAmmo();
	bool IsAmmoEmpty();
	bool IsClipEmpty();
	void ChangeClip();
	void LogAmmo();

};

