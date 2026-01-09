// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "AttributeSet.h"
#include "AbilitySystemComponent.h"
#include "GAS/GameAbilitySystemMacros.h"
#include "EnemyAttributeSet.generated.h"

/**
 * 
 */
UCLASS()
class KI7_UNREALGAS_BJM_API UEnemyAttributeSet : public UAttributeSet
{
	GENERATED_BODY()
	
public:
	UEnemyAttributeSet();
	virtual void PreAttributeChange(const FGameplayAttribute& Attribute, float& NewValue) override;
	virtual void PostGameplayEffectExecute(const FGameplayEffectModCallbackData& Data) override;

	UPROPERTY(BlueprintReadOnly, Category = "Health")
	FGameplayAttributeData Health;
	ATTRIBUTE_ACCESSORS(UEnemyAttributeSet, Health);

	UPROPERTY(BlueprintReadOnly, Category = "Health")
	FGameplayAttributeData MaxHealth;
	ATTRIBUTE_ACCESSORS(UEnemyAttributeSet, MaxHealth);

};
