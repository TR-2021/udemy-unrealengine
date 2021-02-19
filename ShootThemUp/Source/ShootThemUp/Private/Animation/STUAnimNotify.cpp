// Fill out your copyright notice in the Description page of Project Settings.


#include "Animation/STUAnimNotify.h"


void USTUAnimNotify::Notify(USkeletalMeshComponent *MeshComp, UAnimSequenceBase *Animation)
{
	OnNotify.Broadcast(MeshComp);
	Super::Notify(MeshComp, Animation);
}
