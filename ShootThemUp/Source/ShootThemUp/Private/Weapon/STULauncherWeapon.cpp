// Fill out your copyright notice in the Description page of Project Settings.


#include "Weapon/STULauncherWeapon.h"
#include "Engine/World.h"
#include "GameFramework/Character.h"
#include "GameFramework/Controller.h"
#include "DrawDebugHelpers.h"
#include "Weapon/STUProjectile.h"
#include "Kismet/GameplayStatics.h"

ASTULauncherWeapon::ASTULauncherWeapon() 
{
	Inaccuracy = 0;
	FireRate = 1;
}
void ASTULauncherWeapon::StartFire()
{
	MakeShot();
}

void ASTULauncherWeapon::MakeShot()
{
	FTransform SpawnTransform(FRotator::ZeroRotator, GetMuzzleWorldLocation());
	if (!GetWorld() || IsAmmoEmpty())
	{
		StopFire();
		return;
	}
	FVector TraceStart, TraceEnd;
	if (!GetTraceData(TraceStart,TraceEnd)) return;

	FHitResult HitResult;
	MakeHit(HitResult, TraceStart, TraceEnd);

	const FVector EndPoint = HitResult.bBlockingHit ? HitResult.ImpactPoint : TraceEnd;
	const FVector Direction = (EndPoint - GetMuzzleWorldLocation()).GetSafeNormal();

	auto Projectile = GetWorld()->SpawnActorDeferred<ASTUProjectile>(ProjectileClass, SpawnTransform);
	if (Projectile)
	{
		Projectile->SetShotDirection(Direction);
		Projectile->SetOwner(GetOwner());
		Projectile->FinishSpawning(SpawnTransform);
		DecreaseAmmo();
		SpawnMuzzleFX();
	}
}
