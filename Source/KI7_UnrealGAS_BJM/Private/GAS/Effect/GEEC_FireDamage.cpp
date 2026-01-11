// Fill out your copyright notice in the Description page of Project Settings.


#include "GAS/Effect/GEEC_FireDamage.h"
#include "GAS/AttributeSet/EnemyAttributeSet.h"
#include "AbilitySystemComponent.h"
#include "GameplayTagsManager.h"

struct FFireDamageStatics
{

	DECLARE_ATTRIBUTE_CAPTUREDEF(Health);

	FFireDamageStatics()
	{
		DEFINE_ATTRIBUTE_CAPTUREDEF(UEnemyAttributeSet, Health, Target, false);
	}
};


static const FFireDamageStatics& FireDamageStatics()
{
	static FFireDamageStatics Statics;
	return Statics;
}


UGEEC_FireDamage::UGEEC_FireDamage()
{
	RelevantAttributesToCapture.Add(FireDamageStatics().HealthDef);
}

void UGEEC_FireDamage::Execute_Implementation(const FGameplayEffectCustomExecutionParameters& ExecutionParams, FGameplayEffectCustomExecutionOutput& OutExecutionOutput) const
{
	UAbilitySystemComponent* TargetASC = ExecutionParams.GetTargetAbilitySystemComponent();
	UAbilitySystemComponent* SourceASC = ExecutionParams.GetSourceAbilitySystemComponent();

	if (TargetASC && SourceASC)
	{

		const FGameplayEffectSpec& Spec = ExecutionParams.GetOwningSpec();
		const FGameplayTagContainer* TargetTags = Spec.CapturedTargetTags.GetAggregatedTags();

		float Damage = 10.0f;

		float PassedDamage = Spec.GetSetByCallerMagnitude(FGameplayTag::RequestGameplayTag(FName("Effect.Damage")), false, -1.0f);
		if (PassedDamage >= 0.0f)
		{
			Damage = PassedDamage;
		}

		FGameplayTag BurnTag = FGameplayTag::RequestGameplayTag(FName("State.Debuff.Burn"));

		if (TargetTags && TargetTags->HasTag(BurnTag))
		{
			Damage *= 2.0f;
			UE_LOG(LogTemp, Log, TEXT("Target is Burning! Double Damage: %.1f"), Damage);
		}

		if (Damage > 0.0f)
		{
			OutExecutionOutput.AddOutputModifier(
				FGameplayModifierEvaluatedData(
					FireDamageStatics().HealthProperty,
					EGameplayModOp::Additive,          
					-Damage                            
				)
			);
		}
	}
}
