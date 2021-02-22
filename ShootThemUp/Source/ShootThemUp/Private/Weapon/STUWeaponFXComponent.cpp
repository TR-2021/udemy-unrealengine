#include "Weapon/STUWeaponFXComponent.h"
#include "NiagaraFunctionLibrary.h"
#include  "PhysicalMaterials/PhysicalMaterial.h"
#include  "Kismet/GameplayStatics.h"
#include  "Components/DecalComponent.h"

// Sets default values for this component's properties
USTUWeaponFXComponent::USTUWeaponFXComponent()
{
	PrimaryComponentTick.bCanEverTick = false;

}


void USTUWeaponFXComponent::PlayImpactFX(const FHitResult &Hit)
{
	auto ImpactData = DefaultImpactData;
	if (Hit.PhysMaterial.IsValid())
	{
		UE_LOG(LogTemp, Display, L"VALID");
		const auto PhysMat = Hit.PhysMaterial.Get();
		if (ImpactDataMap.Contains(PhysMat))
		{
			ImpactData = ImpactDataMap[PhysMat];	
			UE_LOG(LogTemp, Display, L"SET");
		}
	}
	//spawn Niagara
	UNiagaraFunctionLibrary::SpawnSystemAtLocation(GetWorld(), ImpactData.NiagaraEffect, Hit.ImpactPoint,Hit.ImpactNormal.Rotation());
	auto Decal= UGameplayStatics::SpawnDecalAtLocation(GetWorld(), ImpactData.DecalData.Material, ImpactData.DecalData.Size,Hit.ImpactPoint, Hit.ImpactNormal.Rotation());
	if (Decal)
		Decal->SetFadeOut(ImpactData.DecalData.Lifetime, ImpactData.DecalData.FadeOut);
}

// Called when the game starts
void USTUWeaponFXComponent::BeginPlay()
{
	Super::BeginPlay();
	
}

