// Fill out your copyright notice in the Description page of Project Settings.


#include "SandboxPlayerController.h"
#include "Components/InputComponent.h"
#include "Kismet/GameplayStatics.h"
#include "SandboxPawn.h"

DEFINE_LOG_CATEGORY_STATIC(LogSandboxPlayerController, All, All)

void ASandboxPlayerController::BeginPlay() {
	UGameplayStatics::GetAllActorsOfClass(GetWorld(), ASandboxPawn::StaticClass(), Pawns);
}

void ASandboxPlayerController::SetupInputComponent() {
	Super::SetupInputComponent();
	InputComponent->BindAction("ChangePawn", IE_Pressed, this, &ASandboxPlayerController::ChangePawn);
}

void ASandboxPlayerController::ChangePawn() {
	UE_LOG(LogSandboxPlayerController, Warning, TEXT("SpaceBar Pressed"));
	if (Pawns.Num() <= 1) return;
	
	PawnIndex = (PawnIndex + 1) % Pawns.Num();
	ASandboxPawn* CurrentPawn = Cast<ASandboxPawn>(Pawns[PawnIndex]);
	Possess(CurrentPawn);
}