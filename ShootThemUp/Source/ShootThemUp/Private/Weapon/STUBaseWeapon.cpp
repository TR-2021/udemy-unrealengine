// Fill out your copyright notice in the Description page of Project Settings.

#include "Weapon/STUBaseWeapon.h"
#include "..\..\Public\Weapon\STUBaseWeapon.h"
#include "Components/SkeletalMeshComponent.h"
#include "GameFramework/Character.h"
#include "GameFramework/Controller.h"

// Sets default values
ASTUBaseWeapon::ASTUBaseWeapon()
{
	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = false;
	WeaponMesh = CreateDefaultSubobject<USkeletalMeshComponent>("Root");
	RootComponent = WeaponMesh;
}

// Called when the game starts or when spawned
void ASTUBaseWeapon::BeginPlay()
{
	Super::BeginPlay();
	CurrentAmmoData = DefaultsAmmoData;
	check(WeaponMesh);
}

void ASTUBaseWeapon::StartFire()
{
}
void ASTUBaseWeapon::StopFire()
{
}

void ASTUBaseWeapon::MakeShot()
{
}

APlayerController *ASTUBaseWeapon::GetPlayerController() const
{
	const auto Player = Cast<ACharacter>(GetOwner());
	if (!Player)
		return nullptr;
	return Player->GetController<APlayerController>();
}

bool ASTUBaseWeapon::GetPlayerViewPoint(FVector &ViewLocation, FRotator &ViewRotation) const
{
	const auto PlayerController = GetPlayerController();
	if (!PlayerController)
		return false;

	PlayerController->GetPlayerViewPoint(ViewLocation, ViewRotation);
	return true;
}
FVector ASTUBaseWeapon::GetMuzzleWorldLocation() const
{
	return WeaponMesh->GetSocketLocation(MuzzleSocketName);
}

bool ASTUBaseWeapon::GetTraceData(FVector &TraceStart, FVector &TraceEnd)
{
	FVector ViewLocation;
	FRotator ViewRotation;
	if (!GetPlayerViewPoint(ViewLocation, ViewRotation))
		return false;

	TraceStart = ViewLocation;
	FVector ShootDirection = ViewRotation.Vector();
	TraceEnd = TraceStart + ShootDirection * TraceMaxDistance;
	return true;
}

void ASTUBaseWeapon::MakeHit(FHitResult &HitResult, FVector &TraceStart, FVector &TraceEnd)
{
	FCollisionQueryParams CollisionParams;
	CollisionParams.AddIgnoredActor(GetOwner());
	GetWorld()->LineTraceSingleByChannel(HitResult, TraceStart, TraceEnd, ECollisionChannel::ECC_Visibility,
										 CollisionParams);
}

void ASTUBaseWeapon::DecreaseAmmo()
{
	CurrentAmmoData.Bullets--;
	LogAmmo();
	if (IsClipEmpty() && !IsAmmoEmpty())
	{
		ChangeClip();
	}
}

bool ASTUBaseWeapon::IsAmmoEmpty()
{
	return !CurrentAmmoData.IsInfinity && CurrentAmmoData.Clips == 0 && IsClipEmpty();
}

bool ASTUBaseWeapon::IsClipEmpty()
{
	return CurrentAmmoData.Bullets == 0;
}

void  ASTUBaseWeapon::ChangeClip()
{
	CurrentAmmoData.Bullets = DefaultsAmmoData.Bullets;
	CurrentAmmoData.Clips = CurrentAmmoData.IsInfinity ? DefaultsAmmoData.Clips : CurrentAmmoData.Clips - 1;
	UE_LOG(LogTemp, Display, TEXT("-----Clip Changed----"));
}

void ASTUBaseWeapon::LogAmmo()
{
	FString AmmoInfo = "Ammo " + FString::FromInt(CurrentAmmoData.Bullets) + " / ";
	AmmoInfo += CurrentAmmoData.IsInfinity?"Infinity":FString::FromInt(CurrentAmmoData.Clips);
	UE_LOG(LogTemp, Display, TEXT("%s"), *AmmoInfo);
}