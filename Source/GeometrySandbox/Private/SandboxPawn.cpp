// Fill out your copyright notice in the Description page of Project Settings.


#include "SandboxPawn.h"
#include "Components/InputComponent.h"
#include "Components/StaticMeshComponent.h"
#include "Camera/CameraComponent.h"

DEFINE_LOG_CATEGORY_STATIC(LogSandboxPawn, All, All)

// Sets default values
ASandboxPawn::ASandboxPawn()
{
 	// Set this pawn to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	SceneComponent = CreateDefaultSubobject<USceneComponent>("Root");
	RootComponent = SceneComponent;

	MeshComponent = CreateDefaultSubobject<UStaticMeshComponent>("Mesh");
	MeshComponent->SetupAttachment(GetRootComponent());

	CameraComponent = CreateDefaultSubobject<UCameraComponent>("Camera");
	CameraComponent->SetupAttachment(GetRootComponent());


}

void ASandboxPawn::PossessedBy(AController* NewController)
{
	Super::PossessedBy(NewController);
	UE_LOG(LogSandboxPawn, Warning, TEXT("%s Possessed by %s"), *GetName(), *NewController->GetName());
}

void ASandboxPawn::UnPossessed()
{
	Super::UnPossessed();
	UE_LOG(LogSandboxPawn, Warning, TEXT("%s Un Possessed"), *GetName());

}

// Called when the game starts or when spawned
void ASandboxPawn::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void ASandboxPawn::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	if (!VelocityVector.IsZero()) {
		const FVector NewLocation = GetActorLocation() + VelocityVector * DeltaTime * Velocity;
		SetActorLocation(NewLocation);
	}

}

// Called to bind functionality to input
void ASandboxPawn::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);
	PlayerInputComponent->BindAxis("MoveForward", this, &ASandboxPawn::MoveForward);
	PlayerInputComponent->BindAxis("MoveRight", this, &ASandboxPawn::MoveRight);

}

void ASandboxPawn::MoveForward(float Input)
{
	UE_LOG(LogSandboxPawn, Warning, TEXT("%f"), Input);
	VelocityVector.X = Input;
}

void ASandboxPawn::MoveRight(float Input)
{
	UE_LOG(LogSandboxPawn, Warning, TEXT("%f"), Input);
	VelocityVector.Y = Input;
}

