// Fill out your copyright notice in the Description page of Project Settings.

#include "Components/STUWeaponComponent.h"
#include "Animation/STUAnimNotify.h"
#include "Animation/STUEquipFinishedAnimNotify.h"
#include "Animation/STUReloadFinishedAnimNotify.h"
#include "Components/STUWeaponComponent.h"
#include "GameFramework/Character.h"
#include "Weapon/STUBaseWeapon.h"

USTUWeaponComponent::USTUWeaponComponent()
{
	PrimaryComponentTick.bCanEverTick = false;
}

void USTUWeaponComponent::BeginPlay()
{
	Super::BeginPlay();
	checkf(WeaponData.Num() == 2, TEXT("Only 2 weapons in BP"));
	SpawnWeapons();
	EquipWeapon(CurrentWeaponIndex);
	InitAnimations();
}
void USTUWeaponComponent::EndPlay(const EEndPlayReason::Type EndPlayReason)
{
	CurrentWeapon = nullptr;
	for (auto Weapon : Weapons)
	{
		Weapon->DetachFromActor(FDetachmentTransformRules::KeepRelativeTransform);
		Weapon->Destroy();
	}
	Weapons.Empty();
	Super::EndPlay(EndPlayReason);
}

void USTUWeaponComponent::SpawnWeapons()
{
	if (!GetWorld())
		return;

	ACharacter *Character = Cast<ACharacter>(GetOwner());
	if (!Character)
		return;
	for (auto WeaponClass : WeaponData)
	{
		auto Weapon = GetWorld()->SpawnActor<ASTUBaseWeapon>(WeaponClass.WeaponClass);
		if (!Weapon)
			continue;
		Weapon->SetOwner(GetOwner());
		Weapon->OnEmpty.AddUObject(this, &USTUWeaponComponent::OnEmptyClip);
		Weapons.Add(Weapon);
		AttachWeaponToSocket(Weapon, Character->GetMesh(), SecondaryWeaponAttachSocketName);
	}
}
void USTUWeaponComponent::EquipWeapon(int32 WeaponIndex)
{
	if (WeaponIndex < 0 || WeaponIndex >= Weapons.Num())
		return;

	ACharacter *Character = Cast<ACharacter>(GetOwner());
	StopFire();
	if (!Character)
		return;
	if (CurrentWeapon) // If we have already gun in hand
	{
		AttachWeaponToSocket(CurrentWeapon, Character->GetMesh(), SecondaryWeaponAttachSocketName);
	}

	CurrentWeapon = Weapons[WeaponIndex];
	const auto CurrentWeaponData = WeaponData.FindByPredicate([&](const FWeaponData &Data) { //
		return Data.WeaponClass == CurrentWeapon->GetClass();								 //
	});
	CurrentReloadAnimMontage = CurrentWeaponData ? CurrentWeaponData->ReloadAnimMontage : nullptr;

	AttachWeaponToSocket(CurrentWeapon, Character->GetMesh(), PrimaryWeaponAttachSocketName);
	PlayAnim(EquipAnimMontage);
	EquipAnimInProgress = true;
}
void USTUWeaponComponent::PlayAnim(UAnimMontage *AnimMontage)
{
	ACharacter *Character = Cast<ACharacter>(GetOwner());
	if (!Character)
		return;
	Character->PlayAnimMontage(AnimMontage);
}
void USTUWeaponComponent::NextWeapon()
{
	UE_LOG(LogTemp, Display, TEXT("PRESSED"));
	if (!CanEquip())
		return;
	CurrentWeaponIndex = (CurrentWeaponIndex + 1) % Weapons.Num();
	EquipWeapon(CurrentWeaponIndex);
}
void USTUWeaponComponent::AttachWeaponToSocket(ASTUBaseWeapon *Weapon, USceneComponent *Mesh, FName SocketName)
{
	FAttachmentTransformRules AttachmentRules(EAttachmentRule::SnapToTarget, false);
	Weapon->AttachToComponent(Mesh, AttachmentRules, SocketName);
	Weapon->SetOwner(GetOwner());
}
void USTUWeaponComponent::StartFire()
{
	if (CanFire())
		CurrentWeapon->StartFire();
}
void USTUWeaponComponent::StopFire()
{
	if (!CurrentWeapon)
		return;
	CurrentWeapon->StopFire();
}

void USTUWeaponComponent::InitAnimations()
{

	auto EquipFinishedNotify = FindAnimNotifyByClass<USTUEquipFinishedAnimNotify>(EquipAnimMontage);
	if (EquipFinishedNotify)
	{
		EquipFinishedNotify->OnNotify.AddUObject(this, &USTUWeaponComponent::OnEquipedFinished);
	}
	else
	{
		UE_LOG(LogTemp, Error, TEXT("Forgotten setup equip anim"))
	}
	for (auto OneWeaponData : WeaponData)
	{
		auto ReloadFinishedNotify =
			FindAnimNotifyByClass<USTUReloadFinishedAnimNotify>(OneWeaponData.ReloadAnimMontage);
		if (!ReloadFinishedNotify)
		{
			UE_LOG(LogTemp, Error, TEXT("Forgotten setup reload anim"))
		}
		ReloadFinishedNotify->OnNotify.AddUObject(this, &USTUWeaponComponent::OnReloadFinished);
	}
}

void USTUWeaponComponent::OnEquipedFinished(USkeletalMeshComponent *SkeletalMesh)
{
	ACharacter *Character = Cast<ACharacter>(GetOwner());
	if (!Character || SkeletalMesh != Character->GetMesh())
		return;
	EquipAnimInProgress = false;
	UE_LOG(LogTemp, Display, TEXT("Finieshed"));
}

void USTUWeaponComponent::OnReloadFinished(USkeletalMeshComponent *SkeletalMesh)
{

	ACharacter *Character = Cast<ACharacter>(GetOwner());
	if (!Character || SkeletalMesh != Character->GetMesh())
		return;
	ReloadAnimInProgress = false;
	UE_LOG(LogTemp, Display, TEXT("Finieshed"));
}

bool USTUWeaponComponent::CanFire()
{

	return CurrentWeapon != nullptr && !EquipAnimInProgress && !ReloadAnimInProgress;
}

bool USTUWeaponComponent::CanEquip()
{
	return !EquipAnimInProgress && !ReloadAnimInProgress;
}

bool USTUWeaponComponent::CanReload()
{
	return CurrentWeapon != nullptr 
		&& !EquipAnimInProgress
		&& !ReloadAnimInProgress	
		&&  CurrentWeapon->CanReload();
}
void USTUWeaponComponent::Reload()
{
	ChangeClip();
}

void USTUWeaponComponent::OnEmptyClip()
{
	ChangeClip();
}

void USTUWeaponComponent::ChangeClip()
{
	if (!CanReload())
		return;
	CurrentWeapon->StopFire();
	CurrentWeapon->ChangeClip();
	PlayAnim(CurrentReloadAnimMontage);
	ReloadAnimInProgress = true;
}
