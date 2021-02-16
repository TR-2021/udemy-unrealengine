// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Components/StaticMeshComponent.h"
#include "Engine/Engine.h"
#include "TimerManager.h"
#include "BaseGeometryActor.generated.h"

DECLARE_MULTICAST_DELEGATE_TwoParams(FOnColorChangedDelegate, const FLinearColor&, AActor*)

UENUM(BlueprintType)
enum class EMovementType : uint8
{
	Static,
	Sin
};

USTRUCT(BlueprintType)
struct FGeometryData
{
	GENERATED_USTRUCT_BODY()

	UPROPERTY(EditAnywhere)
	float Amplitude;
	
	UPROPERTY(EditAnywhere)
	float Freequency;
	
	UPROPERTY(EditAnywhere)
	EMovementType MovementTypes = EMovementType::Static;

	UPROPERTY(EditAnywhere)
	FLinearColor Color = FLinearColor::Blue;

	// Timer fire rate in seconds
	UPROPERTY(EditAnywhere)
	float TimerRate= 4.0f;

};


UCLASS()
class GEOMETRYSANDBOX_API ABaseGeometryActor : public AActor
{
	GENERATED_BODY()

public:
	// Sets default values for this actor's properties
	ABaseGeometryActor();
	
protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	void SetColor(const FLinearColor& Color);

	void PrintTransform();

public:
	// Called every frame
	virtual void Tick(float DeltaTime) override;
	void SetGeometryData(const FGeometryData& Data) { GeometryData = Data; }

protected:
	UPROPERTY(EditAnywhere, Category = "Custom vars")
		FGeometryData GeometryData;
	UPROPERTY(EditAnywhere, Category = "Custom vars")
		int32 WeaponsNum = 33;

	UPROPERTY(EditDefaultsOnly, Category = "Custom vars")
		bool DebugVal = false;

	UPROPERTY(EditInstanceOnly, Category = "Custom vars")
		float SomeRealUNmbver = 1.223344;

	UPROPERTY(VisibleAnywhere)
		FString Text = "TEXT";
	
public:
	UPROPERTY(VisibleAnywhere)
		UStaticMeshComponent* BaseMesh;
		FOnColorChangedDelegate OnColorChangedEvent;

private:
	FVector InitialLocation;
	FTimerHandle TimerHandler;
	void PrintSomeInfo();
	void PrintSomeOnScreen();
	void OnTimerFire();
};
