// Fill out your copyright notice in the Description page of Project Settings.


#include "Animation/STUEquipFinishedAnimNotify.h"

void USTUEquipFinishedAnimNotify::Notify(USkeletalMeshComponent *MeshComp, UAnimSequenceBase *Animation)
{
	OnNotify.Broadcast(MeshComp);
	Super::Notify(MeshComp, Animation);
}
