

#include "Pickups/STUHealthPickup.h"
#include <Player/STUHealthComponent.h>
#include <Player/STUBaseCharacter.h>

bool ASTUHealthPickup::GivePickupTo(APawn *PlayerPawn)
{
	const auto Player = Cast<ASTUBaseCharacter>(PlayerPawn);
	if (!Player) return false;

	const auto HealthComponent = Cast<USTUHealthComponent>(Player->GetComponentByClass(USTUHealthComponent::StaticClass()));
	if (!HealthComponent || HealthComponent->IsDead()) return false;

	return HealthComponent->TryAddHealth(HealthAmount);
}