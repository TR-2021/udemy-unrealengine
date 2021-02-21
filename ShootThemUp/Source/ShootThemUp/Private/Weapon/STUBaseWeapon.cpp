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


bool ASTUBaseWeapon::IsAmmoEmpty()
{
	return !CurrentAmmoData.IsInfinity && CurrentAmmoData.Clips == 0 && IsClipEmpty();
}

bool ASTUBaseWeapon::IsClipEmpty()
{
	return CurrentAmmoData.Bullets == 0;
}

void ASTUBaseWeapon::DecreaseAmmo()
{
	if (CurrentAmmoData.Bullets == 0)
	{
		StopFire();
		return;
	};
	CurrentAmmoData.Bullets--;
	LogAmmo();
	if (IsClipEmpty() && !IsAmmoEmpty())
	{
		OnEmpty.Broadcast();
	}
}
void  ASTUBaseWeapon::ChangeClip()
{
	CurrentAmmoData.Bullets = DefaultsAmmoData.Bullets;
	if (!CurrentAmmoData.IsInfinity)
	{
		if (CurrentAmmoData.Clips == 0)
		{
			UE_LOG(LogTemp, Display, TEXT("-----No More Clips for reload----"));
			return;
		}
		CurrentAmmoData.Clips--;
	}
	else
	{
		CurrentAmmoData.Clips = DefaultsAmmoData.Clips;
	}
}

bool ASTUBaseWeapon::CanReload()
{
	return CurrentAmmoData.Bullets < DefaultsAmmoData.Bullets && CurrentAmmoData.Clips >0;
}


void ASTUBaseWeapon::LogAmmo()
{
	FString AmmoInfo = "Ammo " + FString::FromInt(CurrentAmmoData.Bullets) + " / ";
	AmmoInfo += CurrentAmmoData.IsInfinity?"Infinity":FString::FromInt(CurrentAmmoData.Clips);
	UE_LOG(LogTemp, Display, TEXT("%s"), *AmmoInfo);
}

bool ASTUBaseWeapon::TryAddAmmo(int32 Amount)
{
	if (IsFullAmmo() || CurrentAmmoData.IsInfinity || Amount <=0) return false;
	if (IsAmmoEmpty())
	{
		CurrentAmmoData.Clips = FMath::Clamp(Amount, 0, DefaultsAmmoData.Clips+1);
		OnEmpty.Broadcast();
	}
	else if (CurrentAmmoData.Clips < DefaultsAmmoData.Clips)
	{
		const auto NextClipsAmount = CurrentAmmoData.Clips + Amount;
		if (DefaultsAmmoData.Clips - NextClipsAmount >= 0)
		{
			CurrentAmmoData.Clips = NextClipsAmount;
		}
		else
		{
			CurrentAmmoData.Clips = DefaultsAmmoData.Clips;
			CurrentAmmoData.Bullets = DefaultsAmmoData.Bullets;
		}
	}
	else
	{
		CurrentAmmoData.Bullets = DefaultsAmmoData.Bullets;
	}
	return true;
}

bool ASTUBaseWeapon::IsFullAmmo()
{
	return CurrentAmmoData.Bullets == DefaultsAmmoData.Bullets && CurrentAmmoData.Clips == DefaultsAmmoData.Clips;
}