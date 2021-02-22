// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "Components/ActorComponent.h"
#include "CoreMinimal.h"
#include "STUWeaponFXComponent.generated.h"

class UNiagaraSystem;
class UPhysicalMaterial;

USTRUCT(BlueprintType)
struct FDecalData
{
	GENERATED_USTRUCT_BODY()

	UPROPERTY(EditAnyWhere, BlueprintReadWrite, Category = "VFX")
	UMaterialInterface *Material;

	UPROPERTY(EditAnyWhere, BlueprintReadWrite, Category = "VFX")
	FVector Size = FVector(10);

	UPROPERTY(EditAnyWhere, BlueprintReadWrite, Category = "VFX")
	float  Lifetime= 3.0f;

	UPROPERTY(EditAnyWhere, BlueprintReadWrite, Category = "VFX")
	float FadeOut = 0.7f;
};

USTRUCT(BlueprintType)
struct FImpactData
{
	GENERATED_USTRUCT_BODY()

	UPROPERTY(EditAnyWhere, BlueprintReadWrite, Category = "VFX")
	UNiagaraSystem *NiagaraEffect;

	UPROPERTY(EditAnyWhere, BlueprintReadWrite, Category = "VFX")
	FDecalData DecalData;
};

UCLASS(ClassGroup = (Custom), meta = (BlueprintSpawnableComponent))
class SHOOTTHEMUP_API USTUWeaponFXComponent : public UActorComponent
{
	GENERATED_BODY()

  public:
	// Sets default values for this component's properties
	USTUWeaponFXComponent();
	void PlayImpactFX(const FHitResult &Hit);

  protected:
	// Called when the game starts
	virtual void BeginPlay() override;
	UPROPERTY(EditDefaultsOnly, Category = "VFX")
	FImpactData DefaultImpactData;

	UPROPERTY(EditDefaultsOnly, Category = "VFX")
	TMap<UPhysicalMaterial *, FImpactData> ImpactDataMap;
  public:
};
