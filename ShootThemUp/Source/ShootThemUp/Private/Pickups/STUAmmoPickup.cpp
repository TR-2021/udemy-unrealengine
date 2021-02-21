// Fill out your copyright notice in the Description page of Project Settings.

#include "Pickups/STUAmmoPickup.h"
#include <Weapon/STUBaseWeapon.h>
#include <Components/STUWeaponComponent.h>
#include <Player/STUHealthComponent.h>
#include <Player/STUBaseCharacter.h>

bool ASTUAmmoPickup::GivePickupTo(APawn *PlayerPawn)
{
	const auto Player = Cast<ASTUBaseCharacter>(PlayerPawn);
	if (!Player) return false;

	const auto HealthComponent = Cast<USTUHealthComponent>(Player->GetComponentByClass(USTUHealthComponent::StaticClass()));
	if (!HealthComponent || HealthComponent->IsDead()) return false;
	
	const auto WeaponComponent = Cast<USTUWeaponComponent>(Player->GetComponentByClass(USTUWeaponComponent::StaticClass()));
	if (!WeaponComponent)return false;
	
	return WeaponComponent->TryAddAmmo(WeaponType,ClipAmount);
}