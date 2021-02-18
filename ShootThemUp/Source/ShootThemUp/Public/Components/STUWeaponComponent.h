// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "Components/ActorComponent.h"
#include "CoreMinimal.h"
#include "STUWeaponComponent.generated.h"

class ASTUBaseWeapon;

UCLASS(ClassGroup = (Custom), meta = (BlueprintSpawnableComponent))
class SHOOTTHEMUP_API USTUWeaponComponent : public UActorComponent
{
	GENERATED_BODY()

  public:
	// Sets default values for this component's properties
	USTUWeaponComponent();
	void StartFire();
	void StopFire();
	void NextWeapon();
  protected:
	// Called when the game starts
	virtual void BeginPlay() override;
	virtual void EndPlay(const EEndPlayReason::Type EndPlayReason) override;

	UPROPERTY(EditDefaultsOnly, Category = "Weapon")
	TArray<TSubclassOf<ASTUBaseWeapon>> WeaponClasses;

	UPROPERTY(EditDefaultsOnly, Category = "Weapon")
	FName PrimaryWeaponAttachSocketName = "WeaponSocket";

	UPROPERTY(EditDefaultsOnly, Category = "Weapon")
	FName SecondaryWeaponAttachSocketName = "ArmorySocket";

	UPROPERTY(EditDefaultsOnly, Category = "Weapon")
	int32 CurrentWeaponIndex = 0;
	
	UPROPERTY(EditDefaultsOnly, Category = "Animation")
	UAnimMontage* EquipAnimMontage;

	UPROPERTY()
	TArray<ASTUBaseWeapon*> Weapons;
	
	UPROPERTY()
	ASTUBaseWeapon *CurrentWeapon = nullptr;

	
	bool EquipAnimInProgress = false;

  private:
	void SpawnWeapons();
	void AttachWeaponToSocket(ASTUBaseWeapon* Weapon, USceneComponent *Mesh, FName SocketName);
	void EquipWeapon(int32 WeaponIndex);
	void PlayAnim(UAnimMontage *AnimMontage);
	void InitAnimations();
	void OnEquipedFinished(USkeletalMeshComponent *SkeletalMesh);
	bool CanFire();
	bool CanEquip();
};
