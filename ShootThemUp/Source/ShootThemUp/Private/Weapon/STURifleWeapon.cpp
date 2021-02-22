// Fill out your copyright notice in the Description page of Project Settings.


#include "Weapon/STURifleWeapon.h"
#include "Engine/World.h"
#include "GameFramework/Character.h"
#include "GameFramework/Controller.h"
#include "STUWeaponFXComponent.h"
#include "DrawDebugHelpers.h"
#include "..\..\Public\Weapon\STURifleWeapon.h"
#include "NiagaraComponent.h"


ASTURifleWeapon::ASTURifleWeapon() : ASTUBaseWeapon()
{
	Inaccuracy = 0.1f;
	FireRate = 0.01f;
	WeaponFXComponent = CreateDefaultSubobject<USTUWeaponFXComponent>("WeaponFX");
}


void ASTURifleWeapon::StartFire()
{
	InitMuzzleFX();
	GetWorld()->GetTimerManager().SetTimer(FireTimerHandle, this, &ASTURifleWeapon::MakeShot, FireRate, true);
}
void ASTURifleWeapon::StopFire()
{
	SetMuzzleVisibility(false);
	GetWorld()->GetTimerManager().ClearTimer(FireTimerHandle);
}
void ASTURifleWeapon::InitMuzzleFX()
{
	if (!MuzzzleFXComponent)
	{
		MuzzzleFXComponent = SpawnMuzzleFX();
	}
	SetMuzzleVisibility(true);
}
void ASTURifleWeapon::SetMuzzleVisibility(bool Visible)
{
	if (MuzzzleFXComponent)
	{
		MuzzzleFXComponent->SetPaused(!Visible);
		MuzzzleFXComponent->SetPaused(Visible);
	}
}
void ASTURifleWeapon::MakeShot()
{
	if (!GetWorld() || IsAmmoEmpty())
		return;

	const auto Player = Cast<ACharacter>(GetOwner());
	if (!Player)
		return;

	const auto PlayerController = Player->GetController<APlayerController>();
	if (!PlayerController)
		return;

	FVector ViewLocation;
	FRotator ViewRotation;
	PlayerController->GetPlayerViewPoint(ViewLocation, ViewRotation);

	FTransform SocketTransform = WeaponMesh->GetSocketTransform(MuzzleSocketName);
	FVector TraceStart = ViewLocation;

	FVector ShootDirection = FMath::VRandCone(ViewRotation.Vector(), FMath::DegreesToRadians(Inaccuracy / 2));
	FVector TraceEnd = TraceStart + ShootDirection * TraceMaxDistance;

	FHitResult HitResult;
	MakeHit(HitResult, TraceStart, TraceEnd);
	DecreaseAmmo();

	if (HitResult.bBlockingHit)
	{
		WeaponFXComponent->PlayImpactFX(HitResult);
		AActor *HitActor = HitResult.Actor.Get();
		if (!HitActor)
			return;
		
		HitActor->TakeDamage(10, {}, PlayerController, Player);
	}
	else
	{
		DrawDebugLine(GetWorld(), SocketTransform.GetLocation(), TraceEnd, FColor::Blue, false, 3, 0, 1.0f);
	}
}
