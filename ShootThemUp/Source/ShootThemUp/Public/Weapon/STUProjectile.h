// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "STUProjectile.generated.h"

class USphereComponent;
class UProjectileMovementComponent;
class USTUWeaponFXComponent;

UCLASS()
class SHOOTTHEMUP_API ASTUProjectile : public AActor
{
	GENERATED_BODY()

  public:
	// Sets default values for this actor's properties
	ASTUProjectile();
	void SetShotDirection(const FVector &Direction);

  protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;
	UPROPERTY(VisibleDefaultsOnly)
	USphereComponent *SphereCollider;

	UPROPERTY(VisibleDefaultsOnly)
	UProjectileMovementComponent *ProjectileMovement;

	UPROPERTY(EditDefaultsOnly)
	float DamageRadius = 200.0f;

	UPROPERTY(EditDefaultsOnly)
	float DamageAmount = 50.0f; // Damage in center of sphere

	UPROPERTY(EditDefaultsOnly)
	float LifeSpan = 5.0f; 

	UPROPERTY(EditDefaultsOnly)
	bool IsFullDamage= false; 
	UPROPERTY(VisibleAnywhere, Category = "VFX")
	USTUWeaponFXComponent *WeaponFXComponent;

  private:
	FVector ShotDirection;
	UFUNCTION()
	void OnHit(UPrimitiveComponent *HitComponent, AActor *OtherActor, UPrimitiveComponent *OtherComp,
			   FVector NormalImpulse, const FHitResult &Hit);
};
