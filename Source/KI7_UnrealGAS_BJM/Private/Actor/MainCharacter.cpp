// Fill out your copyright notice in the Description page of Project Settings.


#include "Actor/MainCharacter.h"
#include "AbilitySystemComponent.h"
#include "GAS/AttributeSet/PlayerAttributeSet.h"
#include "Components/WidgetComponent.h"
#include "Interface/TwinResource.h"

// Sets default values
AMainCharacter::AMainCharacter()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	// 컴포넌트 생성
	AbilitySystemComponent = CreateDefaultSubobject<UAbilitySystemComponent>(TEXT("AbilitySystemComponent"));

	PlayerAttributeSet = CreateDefaultSubobject<UPlayerAttributeSet>(TEXT("PlayerAttributeSet"));

	PlayerHUDComponent = CreateDefaultSubobject<UWidgetComponent>(TEXT("PlayerHUD"));
	PlayerHUDComponent->SetupAttachment(RootComponent);

}



// Called when the game starts or when spawned
void AMainCharacter::BeginPlay()
{
	Super::BeginPlay();

	if (AbilitySystemComponent)
	{
		if (AbilitySystemComponent)
		{
			AbilitySystemComponent->InitAbilityActorInfo(this, this);

			// 1. 초기값 UI 반영
			if (PlayerHUDComponent && PlayerHUDComponent->GetWidget() && PlayerHUDComponent->GetWidget()->Implements<UTwinResource>())
			{
				ITwinResource::Execute_UpdateMaxHealth(PlayerHUDComponent->GetWidget(), PlayerAttributeSet->GetMaxHealth());
				ITwinResource::Execute_UpdateCurrentHealth(PlayerHUDComponent->GetWidget(), PlayerAttributeSet->GetHealth());
				ITwinResource::Execute_UpdateMaxMana(PlayerHUDComponent->GetWidget(), PlayerAttributeSet->GetMaxMana());
				ITwinResource::Execute_UpdateCurrentMana(PlayerHUDComponent->GetWidget(), PlayerAttributeSet->GetMana());
			}

			// 2. 값이 변할 때 UI 업데이트 (람다 함수 사용)
			// Health
			AbilitySystemComponent->GetGameplayAttributeValueChangeDelegate(UPlayerAttributeSet::GetHealthAttribute()).AddLambda(
				[this](const FOnAttributeChangeData& Data) {
					if (PlayerHUDComponent && PlayerHUDComponent->GetWidget() && PlayerHUDComponent->GetWidget()->Implements<UTwinResource>()) {
						ITwinResource::Execute_UpdateCurrentHealth(PlayerHUDComponent->GetWidget(), Data.NewValue);
					}
				});
			// Mana
			AbilitySystemComponent->GetGameplayAttributeValueChangeDelegate(UPlayerAttributeSet::GetManaAttribute()).AddLambda(
				[this](const FOnAttributeChangeData& Data) {
					if (PlayerHUDComponent && PlayerHUDComponent->GetWidget() && PlayerHUDComponent->GetWidget()->Implements<UTwinResource>()) {
						ITwinResource::Execute_UpdateCurrentMana(PlayerHUDComponent->GetWidget(), Data.NewValue);
					}
				});
		}
	}

}

// Called every frame
void AMainCharacter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

// Called to bind functionality to input
void AMainCharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

}

