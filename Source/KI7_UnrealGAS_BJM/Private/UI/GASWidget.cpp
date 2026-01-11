// Fill out your copyright notice in the Description page of Project Settings.


#include "UI/GASWidget.h"
#include "Components/ProgressBar.h"
#include "Components/TextBlock.h"

void UGASWidget::NativeConstruct()
{
	Super::NativeConstruct();
}

void UGASWidget::UpdateCurrentHealth_Implementation(float InValue)
{
	CurrentHealth = InValue;
	UpdateHealthUI();
}

void UGASWidget::UpdateMaxHealth_Implementation(float InValue)
{
	MaxHealth = InValue;
	UpdateHealthUI();
}

void UGASWidget::UpdateCurrentMana_Implementation(float InValue)
{
	CurrentMana = InValue;
	UpdateManaUI();
}

void UGASWidget::UpdateMaxMana_Implementation(float InValue)
{
	MaxMana = InValue;
	UpdateManaUI();
}

void UGASWidget::UpdateHealthUI()
{
	if (PB_Health)
	{
		float Percent = (MaxHealth > 0.0f) ? (CurrentHealth / MaxHealth) : 0.0f;
		PB_Health->SetPercent(Percent);
	}

	if (Txt_HealthInfo)
	{
		FString InfoString = FString::Printf(TEXT("%d / %d"), FMath::RoundToInt(CurrentHealth), FMath::RoundToInt(MaxHealth));
		Txt_HealthInfo->SetText(FText::FromString(InfoString));
	}
}

void UGASWidget::UpdateManaUI()
{
	if (PB_Mana)
	{
		float Percent = (MaxMana > 0.0f) ? (CurrentMana / MaxMana) : 0.0f;
		PB_Mana->SetPercent(Percent);
	}

	if (Txt_ManaInfo)
	{
		FString InfoString = FString::Printf(TEXT("%d / %d"), FMath::RoundToInt(CurrentMana), FMath::RoundToInt(MaxMana));
		Txt_ManaInfo->SetText(FText::FromString(InfoString));
	}
}
