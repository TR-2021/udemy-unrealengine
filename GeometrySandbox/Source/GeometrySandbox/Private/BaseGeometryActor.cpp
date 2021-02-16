// Fill out your copyright notice in the Description page of Project Settings.


#include "BaseGeometryActor.h"
DEFINE_LOG_CATEGORY_STATIC(LogBaseGeomtry,All,All)

// Sets default values
ABaseGeometryActor::ABaseGeometryActor()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	BaseMesh = CreateDefaultSubobject<UStaticMeshComponent>("BaseMesh");
	SetRootComponent(BaseMesh);
}

// Called when the game starts or when spawned
void ABaseGeometryActor::BeginPlay()
{
	Super::BeginPlay();
	InitialLocation = GetActorLocation();
	GetWorldTimerManager().SetTimer(TimerHandler, this, &ABaseGeometryActor::OnTimerFire, GeometryData.TimerRate, true);
}


// Called every frame
void ABaseGeometryActor::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	FVector CurrentLocation = GetActorLocation();
	float time = GetWorld()->GetTimeSeconds();
	switch (GeometryData.MovementTypes)
	{
	case EMovementType::Sin: 
		CurrentLocation.Z = InitialLocation.Z + GeometryData.Amplitude * FMath::Sin(GeometryData.Freequency * time);
		SetActorLocation(CurrentLocation);
		break;
	case EMovementType::Static : 
		break;
	}
	
}

void ABaseGeometryActor::PrintSomeInfo()
{
	UE_LOG(LogBaseGeomtry, Display, TEXT("Name %s"),*GetName());
	UE_LOG(LogBaseGeomtry, Display, L"TEST Display");
	UE_LOG(LogBaseGeomtry, Warning, L"TEST Warning");
	UE_LOG(LogBaseGeomtry, Error,	 L"TEST Error");
	UE_LOG(LogBaseGeomtry, Display, TEXT("%d %d %f"), WeaponsNum, static_cast<int>(DebugVal), SomeRealUNmbver);
}

void ABaseGeometryActor::PrintSomeOnScreen()
{
	FString healthString = "Health " + FString::FromInt(33);
	FString floatString = "float " + FString::SanitizeFloat(12.22f);
	GEngine->AddOnScreenDebugMessage(-1, 4, FColor::Yellow, healthString + floatString);
}

void ABaseGeometryActor::OnTimerFire()
{
	FLinearColor Color = FLinearColor::MakeRandomColor();
	SetColor(Color);

}


void ABaseGeometryActor::PrintTransform()
{
	FTransform transform = GetActorTransform();
	FVector location = transform.GetLocation();
	FRotator rotator = transform.Rotator();
	FVector scale = transform.GetScale3D();

	UE_LOG(LogBaseGeomtry, Warning, TEXT("Transform %s\n"), *transform.ToHumanReadableString());
	UE_LOG(LogBaseGeomtry, Warning, TEXT("Location %s\n"), *location.ToString());
	UE_LOG(LogBaseGeomtry, Warning, TEXT("Rotator %s\n"), *rotator.ToString());
	UE_LOG(LogBaseGeomtry, Warning, TEXT("Scale %s\n"), *scale.ToString());
}

void ABaseGeometryActor::SetColor(const FLinearColor& Color )
{

	UMaterialInstanceDynamic* DynamicMaterialInstance = BaseMesh->CreateAndSetMaterialInstanceDynamic(0);
	if (DynamicMaterialInstance) {
		DynamicMaterialInstance->SetVectorParameterValue("Color", Color);
		OnColorChangedEvent.Broadcast(Color, this);
	}
}