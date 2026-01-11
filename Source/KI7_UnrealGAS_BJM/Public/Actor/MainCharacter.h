// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "AbilitySystemInterface.h"
#include "GameplayEffect.h"
#include "GameplayEffectTypes.h"
#include "MainCharacter.generated.h"

class UPlayerAttributeSet;
class UAbilitySystemComponent;
class UWidgetComponent;
class UGameplayAbility;
class UInputAction;
class UInputMappingContext;
class UUserWidget;

UCLASS()
class KI7_UNREALGAS_BJM_API AMainCharacter : public ACharacter, public IAbilitySystemInterface
{
	GENERATED_BODY()

public:
	// Sets default values for this character's properties
	AMainCharacter();
	virtual UAbilitySystemComponent* GetAbilitySystemComponent() const override {
		return AbilitySystemComponent;
	};
protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

	void OnFireInput();

private:
	void OnHealthChange(const FOnAttributeChangeData& InData);
	void OnMaxHealthChange(const FOnAttributeChangeData& InData);
	void OnManaChange(const FOnAttributeChangeData& InData);
	void OnMaxManaChange(const FOnAttributeChangeData& InData);

public:
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "GAS")
	TObjectPtr<UAbilitySystemComponent> AbilitySystemComponent;

	UPROPERTY()
	TObjectPtr<UPlayerAttributeSet> PlayerAttributeSet;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "GAS")
	TSubclassOf<UGameplayAbility> FireballAbilityClass;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Input")
	TObjectPtr<UInputMappingContext> DefaultMappingContext;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Input")
	TObjectPtr<UInputAction> IA_Attack;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "UI")
	TSubclassOf<UUserWidget> PlayerHUDClass;

	UPROPERTY()
	TObjectPtr<UUserWidget> PlayerHUDWidget;

};
