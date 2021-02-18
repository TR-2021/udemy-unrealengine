// Fill out your copyright notice in the Description page of Project Settings.

#include "Weapon/STUProjectile.h"
#include "Components/SphereComponent.h"
#include "DrawDebughelpers.h"
#include "GameFramework/ProjectileMovementComponent.h"
#include "Kismet/GameplayStatics.h"

// Sets default values
ASTUProjectile::ASTUProjectile()
{
	PrimaryActorTick.bCanEverTick = false;
	SphereCollider = CreateDefaultSubobject<USphereComponent>("Root");
	SphereCollider->InitSphereRadius(5.0f);
	SphereCollider->SetCollisionEnabled(ECollisionEnabled::QueryOnly);
	SphereCollider->SetCollisionResponseToAllChannels(ECollisionResponse::ECR_Block );
	SetRootComponent(SphereCollider);

	ProjectileMovement = CreateDefaultSubobject<UProjectileMovementComponent>("Movement");
	ProjectileMovement->InitialSpeed = 2500.0f;
	ProjectileMovement->ProjectileGravityScale = 0;
}

// Called when the game starts or when spawned
void ASTUProjectile::BeginPlay()
{
	Super::BeginPlay();
	ProjectileMovement->Velocity = ShotDirection * ProjectileMovement->InitialSpeed;
	SphereCollider->OnComponentHit.AddDynamic(this, &ASTUProjectile::OnHit);
	SetLifeSpan(LifeSpan);
}

void ASTUProjectile::SetShotDirection(const FVector &Direction)
{
	ShotDirection = Direction;
}

void ASTUProjectile::OnHit(UPrimitiveComponent *HitComponent, AActor *OtherActor, UPrimitiveComponent *OtherComp,FVector NormalImpulse, const FHitResult &Hit)
{
	if (!GetWorld())
		return;

	ProjectileMovement->StopMovementImmediately();
	DrawDebugSphere(GetWorld(),Hit.ImpactPoint,DamageRadius,24, FColor::Red,false,1,0,2);

	UGameplayStatics::ApplyRadialDamage(GetWorld(),					//
										DamageAmount,				//
										GetActorLocation(),			//
										DamageRadius,				//
										UDamageType::StaticClass(), //
										{},							//
										this,						//
										nullptr,					//
										IsFullDamage);

	Destroy();
}
