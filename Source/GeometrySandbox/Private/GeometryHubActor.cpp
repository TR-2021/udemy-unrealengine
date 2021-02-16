// Fill out your copyright notice in the Description page of Project Settings.


#include "GeometryHubActor.h"
#include "Engine/World.h"

// Sets default values
AGeometryHubActor::AGeometryHubActor()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

// Called when the game starts or when spawned
void AGeometryHubActor::BeginPlay()
{
	Super::BeginPlay();
	UWorld* World = GetWorld();
	int length = 3;
	if (World) {
		for (size_t i = 0; i < length; i++)
		{
			ABaseGeometryActor* Geometry= World->SpawnActor<ABaseGeometryActor>(GeometryClass);
			if (Geometry) {
				FTransform Transform = FTransform(FRotator(), FVector(50, 100 * i, 100));
				FGeometryData Data = FGeometryData();
				Data.MovementTypes = (i % 2) == 0 ? EMovementType::Sin : EMovementType::Static;
				Data.Freequency = i * 2;
				Data.Amplitude = i * 10;
				Geometry->SetGeometryData(Data);
				Geometry->SetActorTransform(Transform);
			}
		}  
		// Defered Spawning
		for (size_t i = 0; i < length; i++)
		{
			FTransform Transform = FTransform(FRotator(), FVector(50, 100 * i, 400));
			ABaseGeometryActor* Geometry = World->SpawnActorDeferred<ABaseGeometryActor>(GeometryClass, Transform);
			if (Geometry) {
				FGeometryData Data = FGeometryData();
				Data.Color = FLinearColor::Red;
				Data.MovementTypes = (i % 2) == 0 ? EMovementType::Sin : EMovementType::Static;
				Data.Freequency = i * 2;
				Data.Amplitude = i * 10;
				Geometry->SetGeometryData(Data);
				Geometry->FinishSpawning(Transform);
			}
		}

		for (const FGeometryPayload Payload : GeometryPayload) 
		{
			ABaseGeometryActor* Geometry = World->SpawnActorDeferred<ABaseGeometryActor>(Payload.GeometryClass, Payload.InitialTransform);
			if (Geometry) {
				FGeometryData Data = FGeometryData();
				Data.Color = FLinearColor::Red;
				Geometry->OnColorChangedEvent.AddUObject(this, &AGeometryHubActor::OnGeometryColorChanged);
				Geometry->SetGeometryData(Data);
				Geometry->FinishSpawning(Payload.InitialTransform);
			}
		}


	}
}

// Called every frame
void AGeometryHubActor::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void  AGeometryHubActor::OnGeometryColorChanged(const FLinearColor& Color, AActor* Actor)
{
	GEngine->AddOnScreenDebugMessage(-1, 4, FColor::Yellow, Actor->GetName()+" Has changed color To "+*Color.ToString());
}

