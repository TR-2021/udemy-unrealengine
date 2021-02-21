// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "STUBasePickup.generated.h"
class USphereComponent;

UCLASS()
class SHOOTTHEMUP_API ASTUBasePickup : public AActor
{
	GENERATED_BODY()

  public:
	// Sets default values for this actor's properties
	ASTUBasePickup();

  protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;
	virtual void NotifyActorBeginOverlap(AActor *OtherActor) override;

	UPROPERTY(EditAnywhere, Category = "Pickups")
	USphereComponent *SphereCollider;
	UPROPERTY(EditAnywhere, Category = "Pickups")
	float RespawnTime = 3;

  public:
	// Called every frame
	virtual void Tick(float DeltaTime) override;
	virtual bool GivePickupTo(APawn *Player);

  private:
	float RotationYaw;
	
	void PickupWasTaken();
	void Respawn();
	void GenerateRotationYaw();

};
