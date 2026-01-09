// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "AttributeSet.h"
#include "AbilitySystemComponent.h"
#include "GAS/GameAbilitySystemMacros.h"
#include "PlayerAttributeSet.generated.h"

/**
 * 
 */
UCLASS()
class KI7_UNREALGAS_BJM_API UPlayerAttributeSet : public UAttributeSet
{
	GENERATED_BODY()
	
public:
	UPlayerAttributeSet();


	virtual void PreAttributeChange(const FGameplayAttribute& Attribute, float& NewValue) override;
	virtual void PostGameplayEffectExecute(const FGameplayEffectModCallbackData& Data) override;

	UPROPERTY(BlueprintReadOnly, Category = "Status")
	FGameplayAttributeData Health;
	ATTRIBUTE_ACCESSORS(UPlayerAttributeSet, Health);

	UPROPERTY(BlueprintReadOnly, Category = "Status")
	FGameplayAttributeData MaxHealth;
	ATTRIBUTE_ACCESSORS(UPlayerAttributeSet, MaxHealth);

	UPROPERTY(BlueprintReadOnly, Category = "Status")
	FGameplayAttributeData Mana;
	ATTRIBUTE_ACCESSORS(UPlayerAttributeSet, Mana);

	UPROPERTY(BlueprintReadOnly, Category = "Status")
	FGameplayAttributeData MaxMana;
	ATTRIBUTE_ACCESSORS(UPlayerAttributeSet, MaxMana);

};
