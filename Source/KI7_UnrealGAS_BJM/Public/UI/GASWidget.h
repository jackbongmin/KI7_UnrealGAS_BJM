// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "Interface/TwinResource.h"
#include "GASWidget.generated.h"

class UProgressBar;
class UTextBlock;
/**
 * 
 */
UCLASS()
class KI7_UNREALGAS_BJM_API UGASWidget : public UUserWidget, public ITwinResource
{
	GENERATED_BODY()

public:
	virtual void NativeConstruct() override;

	virtual void UpdateCurrentHealth_Implementation(float InValue) override;
	virtual void UpdateMaxHealth_Implementation(float InValue) override;
	virtual void UpdateCurrentMana_Implementation(float InValue) override;
	virtual void UpdateMaxMana_Implementation(float InValue) override;

protected:
	// 내부적으로 UI 업데이트하는 함수
	void UpdateHealthUI();
	void UpdateManaUI();

protected:

	UPROPERTY(meta = (BindWidget))
	TObjectPtr<UProgressBar> PB_Health;

	UPROPERTY(meta = (BindWidgetOptional)) 
		TObjectPtr<UTextBlock> Txt_HealthInfo;


	UPROPERTY(meta = (BindWidgetOptional)) 
		TObjectPtr<UProgressBar> PB_Mana;

	UPROPERTY(meta = (BindWidgetOptional))
	TObjectPtr<UTextBlock> Txt_ManaInfo;

private:

	float CurrentHealth = 0.0f;
	float MaxHealth = 1.0f;
	float CurrentMana = 0.0f;
	float MaxMana = 1.0f;

};
