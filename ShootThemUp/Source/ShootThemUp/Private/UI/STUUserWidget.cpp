// Fill out your copyright notice in the Description page of Project Settings.

#include "UI/STUUserWidget.h"
#include <Player/STUHealthComponent.h>
#include <Components/STUWeaponComponent.h>

bool USTUUserWidget::GetWeaponUIData(FWeaponUIData &WeaponUIData)
{
	const auto Player = GetOwningPlayerPawn();
	if (!Player)
		return false;

	const auto Component = Player->GetComponentByClass(USTUWeaponComponent::StaticClass());
	const auto WeaponComponent = Cast<USTUWeaponComponent>(Component);
	if (!WeaponComponent)
		return false;
	return WeaponComponent->GetWeaponUIData(WeaponUIData);
}

FString USTUUserWidget::GetFormatedWeaponData(FAmmoData WeaponData)
{
	int CurrentAmmo = WeaponData.Bullets;
	int CurrentClips = WeaponData.Clips;
	FString StringAmmo = FString::FromInt(CurrentAmmo) + "/" + (WeaponData.IsInfinity ? "Inf" : FString::FromInt(CurrentClips));
	return StringAmmo;
}
bool USTUUserWidget::GetWeaponData(FAmmoData &WeaponData)
{
	const auto Player = GetOwningPlayerPawn();
	if (!Player)
		return false;

	const auto Component = Player->GetComponentByClass(USTUWeaponComponent::StaticClass());
	const auto WeaponComponent = Cast<USTUWeaponComponent>(Component);
	if (!WeaponComponent)
		return false;
	return WeaponComponent->GetWeaponData(WeaponData);
}

float USTUUserWidget::GetHealthPercents()
{
	const auto HealthComponent = GetHealthComponent();
	if (!HealthComponent)
		return 0.0f;

	return HealthComponent->GetHealthPercent();
}


bool USTUUserWidget::IsPlayerAlive()
{
	const auto HealthComponent = GetHealthComponent();
	if (!HealthComponent) return false;
	return !HealthComponent->IsDead();
}
bool USTUUserWidget::IsPlayerSpectating()
{
	const auto Controller = GetOwningPlayer();
	return Controller && Controller->GetStateName() == NAME_Spectating;
}
USTUHealthComponent *USTUUserWidget::GetHealthComponent()
{

	const auto Player = GetOwningPlayerPawn();
	if (!Player)
		return nullptr;

	const auto Component = Player->GetComponentByClass(USTUHealthComponent::StaticClass());
	const auto HealthComponent = Cast<USTUHealthComponent>(Component);
	if (HealthComponent)
		return HealthComponent;
	else
		return nullptr;
}