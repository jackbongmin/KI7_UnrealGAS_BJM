// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Abilities/GameplayAbility.h"
#include "GA_Fireball.generated.h"

class AFireballProjectile;

/**
 * 
 */
UCLASS()
class KI7_UNREALGAS_BJM_API UGA_Fireball : public UGameplayAbility
{
	GENERATED_BODY()
	
public:
	UGA_Fireball();

	virtual void ActivateAbility(const FGameplayAbilitySpecHandle Handle, const FGameplayAbilityActorInfo* ActorInfo, const FGameplayAbilityActivationInfo ActivationInfo, const FGameplayEventData* TriggerEventData) override;

public:
	// 소환할 발사체 클래스 (BP에서 설정)
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Ability")
	TSubclassOf<AFireballProjectile> ProjectileClass;

};
