// Fill out your copyright notice in the Description page of Project Settings.


#include "Weapon/STURifleWeapon.h"
#include "Engine/World.h"
#include "GameFramework/Character.h"
#include "GameFramework/Controller.h"
#include "DrawDebugHelpers.h"

ASTURifleWeapon::ASTURifleWeapon() : ASTUBaseWeapon()
{
	Inaccuracy = 0.1f;
	FireRate = 0.01f;
}
void ASTURifleWeapon::StartFire()
{
	GetWorld()->GetTimerManager().SetTimer(FireTimerHandle, this, &ASTURifleWeapon::MakeShot, FireRate, true);
}
void ASTURifleWeapon::StopFire()
{
	GetWorld()->GetTimerManager().ClearTimer(FireTimerHandle);
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

	FCollisionQueryParams CollisionParams;
	CollisionParams.AddIgnoredActor(Player);
	FHitResult HitResult;
	GetWorld()->LineTraceSingleByChannel(HitResult, TraceStart, TraceEnd, ECollisionChannel::ECC_Visibility,
										 CollisionParams);

	if (HitResult.bBlockingHit)
	{
		AActor *HitActor = HitResult.Actor.Get();
		if (!HitActor)
			return;

		HitActor->TakeDamage(10, {}, PlayerController, Player);
		DrawDebugLine(GetWorld(), SocketTransform.GetLocation(), HitResult.ImpactPoint, FColor::Green, false, 3, 0,
					  1.0f);
		DrawDebugSphere(GetWorld(), HitResult.ImpactPoint, 10, 24, FColor::Red, false, 5);

	}
	else
	{
		DrawDebugLine(GetWorld(), SocketTransform.GetLocation(), TraceEnd, FColor::Blue, false, 3, 0, 1.0f);
	}
	DecreaseAmmo();
}
