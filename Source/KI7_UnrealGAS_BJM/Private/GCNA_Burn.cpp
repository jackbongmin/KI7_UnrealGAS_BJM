// Fill out your copyright notice in the Description page of Project Settings.


#include "GCNA_Burn.h"
#include "NiagaraSystem.h"
#include "NiagaraFunctionLibrary.h"
#include "NiagaraComponent.h"
#include "GameplayTagsManager.h"

AGCNA_Burn::AGCNA_Burn()
{
	//GameplayCueTag = FGameplayTag::RequestGameplayTag(FName("GameplayCue.Debuff.Burn"));
	bAutoDestroyOnRemove = true;

}

bool AGCNA_Burn::OnActive_Implementation(AActor* MyTarget, const FGameplayCueParameters& Parameters)
{
	UE_LOG(LogTemp, Warning, TEXT("[GCNA_Burn] OnActive 실행됨! 타겟: %s"), *GetNameSafe(MyTarget));
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
		if (SpawnedLoopingEffect)
		{
			UE_LOG(LogTemp, Warning, TEXT(" [GCNA_Burn] 나이아가라 생성 성공!"));
		}
		else
		{
			UE_LOG(LogTemp, Error, TEXT("[GCNA_Burn] 나이아가라 생성 실패! BurnVFX가 비어있나?"));
		}

		return true;
	}
	UE_LOG(LogTemp, Error, TEXT(" [GCNA_Burn] 타겟이 없거나 BurnVFX가 설정 안 됨!"));
	return false;
}

bool AGCNA_Burn::OnRemove_Implementation(AActor* MyTarget, const FGameplayCueParameters& Parameters)
{
	UE_LOG(LogTemp, Warning, TEXT("[GCNA_Burn] OnRemove 실행됨 (불 꺼짐)"));
	if (SpawnedLoopingEffect)
	{
		SpawnedLoopingEffect->Deactivate();
		SpawnedLoopingEffect = nullptr;
	}
	return true;
}
