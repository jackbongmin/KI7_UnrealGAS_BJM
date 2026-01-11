// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameplayCueNotify_Actor.h"
#include "GCNA_Burn.generated.h"

class UNiagaraSystem;
class UNiagaraComponent;
/**
 * 
 */
UCLASS()
class KI7_UNREALGAS_BJM_API AGCNA_Burn : public AGameplayCueNotify_Actor
{
	GENERATED_BODY()

public:
	AGCNA_Burn();

protected:
	virtual bool OnActive_Implementation(AActor* MyTarget, const FGameplayCueParameters& Parameters) override;

	virtual bool OnRemove_Implementation(AActor* MyTarget, const FGameplayCueParameters& Parameters) override;

public:
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "VFX")
	TObjectPtr<UNiagaraSystem> BurnVFX;

	UPROPERTY()
	TObjectPtr<UNiagaraComponent> SpawnedLoopingEffect;

};
