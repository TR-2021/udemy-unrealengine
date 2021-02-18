// Fill out your copyright notice in the Description page of Project Settings.

#include "Components/STUWeaponComponent.h"
#include "..\..\Public\Components\STUWeaponComponent.h"
#include "Animation/AnimNotifies/AnimNotify.h"
#include "Animation/STUEquipFinishedAnimNotify.h"
#include "GameFramework/Character.h"
#include "Weapon/STUBaseWeapon.h"

USTUWeaponComponent::USTUWeaponComponent()
{
	PrimaryComponentTick.bCanEverTick = false;
}

void USTUWeaponComponent::BeginPlay()
{
	Super::BeginPlay();
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
	for (auto WeaponClass : WeaponClasses)
	{
		auto Weapon = GetWorld()->SpawnActor<ASTUBaseWeapon>(WeaponClass);
		if (!Weapon)
			continue;
		Weapon->SetOwner(GetOwner());
		Weapons.Add(Weapon);
		AttachWeaponToSocket(Weapon, Character->GetMesh(), SecondaryWeaponAttachSocketName);
	}
}
void USTUWeaponComponent::EquipWeapon(int32 WeaponIndex)
{

	ACharacter *Character = Cast<ACharacter>(GetOwner());
	StopFire();
	if (!Character)
		return;
	if (CurrentWeapon) // If we have already gun in hand
	{
		AttachWeaponToSocket(CurrentWeapon, Character->GetMesh(), SecondaryWeaponAttachSocketName);
	}

	CurrentWeapon = Weapons[WeaponIndex];
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
	if (!CanEquip()) return; 
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
	if (!EquipAnimMontage)
		return;

	auto const NotifyEvents = EquipAnimMontage->Notifies;
	for (auto NotifyEvent : NotifyEvents)
	{
		auto EquipFinished = Cast<USTUEquipFinishedAnimNotify>(NotifyEvent.Notify);
		if (EquipFinished)
		{
			EquipFinished->OnNotify.AddUObject(this, &USTUWeaponComponent::OnEquipedFinished);
			break;
		}
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

bool USTUWeaponComponent::CanFire()
{

	return CurrentWeapon != nullptr && !EquipAnimInProgress;
}

bool USTUWeaponComponent::CanEquip()
{
	return !EquipAnimInProgress;
}
