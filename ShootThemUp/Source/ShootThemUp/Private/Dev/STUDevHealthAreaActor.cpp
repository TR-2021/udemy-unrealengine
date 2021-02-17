// Fill out your copyright notice in the Description page of Project Settings.


#include "Dev/STUDevHealthAreaActor.h"
#include "DrawDebugHelpers.h"
#include "Components/SphereComponent.h"
#include "Kismet/GameplayStatics.h"

// Sets default values
ASTUDevHealthAreaActor::ASTUDevHealthAreaActor()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	SphereComponent = CreateDefaultSubobject<USphereComponent>("Root");
	RootComponent = SphereComponent;
	SphereComponent->SetSphereRadius(Radius);
	
}

// Called when the game starts or when spawned
void ASTUDevHealthAreaActor::BeginPlay()
{
	Super::BeginPlay();
	Amount = 10;
}

// Called every frame
void ASTUDevHealthAreaActor::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	DrawDebugSphere(GetWorld(), GetActorLocation(), Radius, 24, Color);
	UGameplayStatics::ApplyRadialDamage(GetWorld(), Amount, GetActorLocation(), Radius, nullptr, {}, this, nullptr,IsFullDamage);
}

