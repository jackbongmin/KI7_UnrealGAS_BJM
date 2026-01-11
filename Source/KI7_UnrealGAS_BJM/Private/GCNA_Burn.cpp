// Fill out your copyright notice in the Description page of Project Settings.


#include "GCNA_Burn.h"
#include "NiagaraSystem.h"
#include "NiagaraFunctionLibrary.h"
#include "NiagaraComponent.h"
#include "GameplayTagsManager.h"

AGCNA_Burn::AGCNA_Burn()
{
	GameplayCueTag = FGameplayTag::RequestGameplayTag(FName("GameplayCue.Debuff.Burn"));
	bAutoDestroyOnRemove = true; 
}

bool AGCNA_Burn::OnActive_Implementation(AActor* MyTarget, const FGameplayCueParameters& Parameters)
{
	if (MyTarget && BurnVFX)
	{
		SpawnedLoopingEffect = UNiagaraFunctionLibrary::SpawnSystemAttached(
			BurnVFX,
			MyTarget->GetRootComponent(),
			FName("None"),
			FVector::ZeroVector,
			FRotator::ZeroRotator,
			EAttachLocation::SnapToTarget,
			true
		);

		return true;
	}
	return false;
}

bool AGCNA_Burn::OnRemove_Implementation(AActor* MyTarget, const FGameplayCueParameters& Parameters)
{
	if (SpawnedLoopingEffect)
	{
		SpawnedLoopingEffect->Deactivate();
		SpawnedLoopingEffect = nullptr;
	}
	return true;
}
