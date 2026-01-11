// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "AbilitySystemInterface.h"
#include "GameplayEffectTypes.h"
#include "Enemy.generated.h"


class UAbilitySystemComponent;
class UEnemyAttributeSet;
class UWidgetComponent;


UCLASS()
class KI7_UNREALGAS_BJM_API AEnemy : public ACharacter
{
	GENERATED_BODY()


public:
	// Sets default values for this character's properties
	AEnemy();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

private:
	void OnHealthChange(const FOnAttributeChangeData& InData);
	void OnMaxHealthChange(const FOnAttributeChangeData& InData);

public:
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "GAS")
	TObjectPtr<UAbilitySystemComponent> AbilitySystemComponent;

	UPROPERTY()
	TObjectPtr<UEnemyAttributeSet> EnemyAttributeSet;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "UI")
	TObjectPtr<UWidgetComponent> HealthWidgetComponent;

};
