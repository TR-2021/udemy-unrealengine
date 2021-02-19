// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "Components/ActorComponent.h"
#include "CoreMinimal.h"
#include "STUWeaponComponent.generated.h"

class ASTUBaseWeapon;

USTRUCT(BlueprintType)
struct FWeaponData
{
	GENERATED_USTRUCT_BODY();

	UPROPERTY(EditDefaultsOnly,BlueprintReadWrite,Category = "Weapon")
	TSubclassOf<ASTUBaseWeapon> WeaponClass;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite,Category = "Weapon")
	UAnimMontage* ReloadAnimMontage;
};


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
	void Reload();
  protected:
	// Called when the game starts
	virtual void BeginPlay() override;
	virtual void EndPlay(const EEndPlayReason::Type EndPlayReason) override;

	UPROPERTY(EditDefaultsOnly, Category = "Weapon")
	TArray<FWeaponData> WeaponData;

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
	UPROPERTY()
	UAnimMontage *CurrentReloadAnimMontage = nullptr;
	
	bool EquipAnimInProgress = false;
	bool ReloadAnimInProgress = false;

  private:
	void SpawnWeapons();
	void AttachWeaponToSocket(ASTUBaseWeapon* Weapon, USceneComponent *Mesh, FName SocketName);
	void EquipWeapon(int32 WeaponIndex);
	void PlayAnim(UAnimMontage *AnimMontage);
	void InitAnimations();
	void OnEquipedFinished(USkeletalMeshComponent *SkeletalMesh);
	void OnReloadFinished(USkeletalMeshComponent *SkeletalMesh);
	bool CanFire();
	bool CanEquip();
	bool CanReload();
	void OnEmptyClip();
	void ChangeClip();

	template <class T> T *FindAnimNotifyByClass(UAnimSequenceBase* Animation);
};

template <class T> inline T *USTUWeaponComponent::FindAnimNotifyByClass(UAnimSequenceBase* Animation)
{
	if (!Animation)
		return nullptr;
	
	auto const NotifyEvents = Animation->Notifies;
	for (auto NotifyEvent : NotifyEvents)
	{
		auto AnimMontage = Cast<T>(NotifyEvent.Notify);
		if (AnimMontage){return AnimMontage;}
	}
	return nullptr;
}
