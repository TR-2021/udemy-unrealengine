// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "Components/ActorComponent.h"
#include "CoreMinimal.h"
#include "STUHealthComponent.generated.h"
DECLARE_MULTICAST_DELEGATE(FOnDeath);
DECLARE_MULTICAST_DELEGATE_OneParam(FOnHealthChanged,float);


UCLASS(ClassGroup = (Custom), meta = (BlueprintSpawnableComponent))
class SHOOTTHEMUP_API USTUHealthComponent : public UActorComponent
{
	GENERATED_BODY()

  public:
	USTUHealthComponent();
	float GetHealth(){return Health;}
	
	UFUNCTION(BlueprintCallable)
	bool IsDead(){return Health <=0;}

	FOnDeath OnDeath;
	FOnHealthChanged OnHealthChanged;

	UPROPERTY(EditAnywhere,Category="AutoHeal")
	float HealDelay;		// Delay between damage and heal
	UPROPERTY(EditAnywhere, Category = "AutoHeal")
	float HealRate;			// Rate of executing function Heal
	UPROPERTY(EditAnywhere, Category = "AutoHeal")
	float HealAmount;
	UPROPERTY(EditAnywhere, Category = "AutoHeal")
	bool IsAutoHeal = true;
	

	UPROPERTY()
	FTimerHandle HealTimerHanlde;

	UFUNCTION(BlueprintCallable)
	void Heal();
	void SetHealth(float);
  protected:
	virtual void BeginPlay() override;
	
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, meta=(ClampMin="0",ClampMax="1000"))
	float MaxHealth = 100.0f;


 private:
	float Health = 0.0f;
	
	UFUNCTION()
	void OnAnyDamage(AActor *DamagedActor, float Damage, const class UDamageType *DamageType,
					 class AController *InstigatedBy, AActor *DamageCauser);
};
