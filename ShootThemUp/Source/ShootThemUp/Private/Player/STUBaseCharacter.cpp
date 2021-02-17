// Fill out your copyright notice in the Description page of Project Settings.

#include "Player/STUBaseCharacter.h"
#include "Player/STUHealthComponent.h"
#include "Camera/CameraComponent.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "Components/TextRenderComponent.h"
#include "GameFramework/SpringArmComponent.h"

// Sets default values
ASTUBaseCharacter::ASTUBaseCharacter()
{
	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need
	// it.
	PrimaryActorTick.bCanEverTick = true;


	SpringArmComponent = CreateDefaultSubobject<USpringArmComponent>("SpringArm");
	SpringArmComponent->SetupAttachment(GetRootComponent());
	SpringArmComponent->bUsePawnControlRotation = true;

	CameraComponent = CreateDefaultSubobject<UCameraComponent>("Camera");
	CameraComponent->SetupAttachment(SpringArmComponent);
	
	HealthComponent = CreateDefaultSubobject<USTUHealthComponent>("Commponent");
	HealthComponent->OnHealthChanged.AddUObject(this, &ASTUBaseCharacter::OnHealthChanged);
	HealthComponent->OnDeath.AddUObject(this, &ASTUBaseCharacter::OnDeath);

	TextComponent = CreateDefaultSubobject<UTextRenderComponent>("Text");
	TextComponent->SetupAttachment(GetRootComponent());

	MaxRunSpeed = 3000;
	ImpulseMultiplier = 4;
}

// Called when the game starts or when spawned
void ASTUBaseCharacter::BeginPlay()
{
	Super::BeginPlay();
	DefaultSpeed = GetMovementComponent()->GetMaxSpeed();
	
}

// Called every frame
void ASTUBaseCharacter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	
}

// Called to bind functionality to input
void ASTUBaseCharacter::SetupPlayerInputComponent(UInputComponent *PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);
	PlayerInputComponent->BindAxis("MoveForward", this, &ASTUBaseCharacter::MoveForward);
	PlayerInputComponent->BindAxis("MoveRight", this, &ASTUBaseCharacter::MoveRight);
	PlayerInputComponent->BindAxis("LookUp", this, &Super::AddControllerPitchInput);
	PlayerInputComponent->BindAxis("LookAround", this, &Super::AddControllerYawInput);
	PlayerInputComponent->BindAction("Jump", EInputEvent::IE_Pressed, this, &Super::Jump);
	PlayerInputComponent->BindAction("Run", EInputEvent::IE_Pressed, this, &ASTUBaseCharacter::StartRun);
	PlayerInputComponent->BindAction("Run", EInputEvent::IE_Released, this, &ASTUBaseCharacter::StopRun);
}

void ASTUBaseCharacter::MoveForward(float Input)
{
	AddMovementInput(GetActorForwardVector(), Input);
	IsMovingForward = Input > 0;
}

void ASTUBaseCharacter::MoveRight(float Input)
{
	AddMovementInput(GetActorRightVector(), Input);
}

void ASTUBaseCharacter::StartRun()
{
	IsWantToRun = true;
	if (IsRunning())
	{
		UCharacterMovementComponent *MovementComponent = GetCharacterMovement();
		MovementComponent->MaxWalkSpeed = MaxRunSpeed;
		MovementComponent->AddImpulse(GetActorForwardVector() * ImpulseMultiplier, false);
	}
}
void ASTUBaseCharacter::StopRun()
{
	GetCharacterMovement()->MaxWalkSpeed = DefaultSpeed;
	IsWantToRun = false;
}



void ASTUBaseCharacter::OnHealthChanged(float Health)
{
	TextComponent->SetText(FText::FromString(FString::Printf(TEXT("%.0f"), Health)));
}



bool ASTUBaseCharacter::IsRunning()
{
	return IsWantToRun && IsMovingForward && GetVelocity().Size() > 0;
}

float ASTUBaseCharacter::GetMovementDirection() const
{
	FVector ForwardVector = GetActorForwardVector();
	FVector VelocityVector = GetVelocity();
	FVector CrossProduct = FVector::CrossProduct(ForwardVector, VelocityVector);
	ForwardVector.Normalize();
	VelocityVector.Normalize();
	float angle = FMath::Acos(FVector::DotProduct(ForwardVector, VelocityVector));
	return FMath::RadiansToDegrees(angle) * FMath::Sign(CrossProduct.Z);
}

void ASTUBaseCharacter::OnDeath()
{
	PlayAnimMontage(DeathAnimationMontage);
	GetCharacterMovement()->DisableMovement();
	GetController()->ChangeState(NAME_Spectating);
	SetLifeSpan(3);
}