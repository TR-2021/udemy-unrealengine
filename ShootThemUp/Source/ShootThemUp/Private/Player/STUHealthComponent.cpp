// Fill out your copyright notice in the Description page of Project Settings.

#include "Player/STUHealthComponent.h"
#include "Engine/World.h"
#include "TimerManager.h"

// Sets default values for this component's properties
USTUHealthComponent::USTUHealthComponent()
{
	PrimaryComponentTick.bCanEverTick = false;
}


void USTUHealthComponent::BeginPlay()
{
	Super::BeginPlay();
	SetHealth(MaxHealth);
	OnHealthChanged.Broadcast(Health);
	AActor *Owner = GetOwner();
	check(Owner);
	if (Owner)
		Owner->OnTakeAnyDamage.AddDynamic(this, &USTUHealthComponent::OnAnyDamage);
}

void USTUHealthComponent::OnAnyDamage(AActor *DamagedActor, float Damage, const class UDamageType *DamageType,class AController *InstigatedBy, AActor *DamageCauser)
{
	if (IsDead()) return;

 	SetHealth(Health -Damage);

	GetWorld()->GetTimerManager().ClearTimer(HealTimerHanlde);
	if (IsAutoHeal)
	{
		GetWorld()->GetTimerManager().SetTimer(HealTimerHanlde, this,&USTUHealthComponent::Heal, HealRate, true, HealDelay);
	}
	if (IsDead())
	{
		GetWorld()->GetTimerManager().ClearTimer(HealTimerHanlde);
		OnDeath.Broadcast();
	}
}

void USTUHealthComponent::Heal()
{
	SetHealth(Health+ HealAmount);
	if (Health >= MaxHealth)
		GetWorld()->GetTimerManager().ClearTimer(HealTimerHanlde);
}

void USTUHealthComponent::SetHealth(float NewHealth)
{
	Health = FMath::Clamp<float>(NewHealth, 0, MaxHealth);
	OnHealthChanged.Broadcast(NewHealth);
}
