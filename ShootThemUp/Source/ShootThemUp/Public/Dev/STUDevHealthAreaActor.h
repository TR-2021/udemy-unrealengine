// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "STUDevHealthAreaActor.generated.h"
class USphereComponent;
UCLASS()
class SHOOTTHEMUP_API ASTUDevHealthAreaActor : public AActor
{
	GENERATED_BODY()

  public:
	// Sets default values for this actor's properties
	ASTUDevHealthAreaActor();

  protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;
	UPROPERTY(VisibleAnywhere)
	USphereComponent *SphereComponent;

	UPROPERTY(EditAnywhere,Category="Dev")
	float Radius = 300.0f;

	UPROPERTY(EditAnywhere, Category = "Dev")
	FColor Color;
	
	UPROPERTY(EditAnywhere, Category = "Dev")
	float Amount;
	
	UPROPERTY(EditAnywhere, Category = "Dev")
	bool IsFullDamage;
  public:
	// Called every frame
	virtual void Tick(float DeltaTime) override;


};
