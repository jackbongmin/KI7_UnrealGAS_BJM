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
	PrimaryActorTick.bCanEverTick = false;

	// 컴포넌트 생성
	AbilitySystemComponent = CreateDefaultSubobject<UAbilitySystemComponent>(TEXT("AbilitySystemComponent"));

	PlayerAttributeSet = CreateDefaultSubobject<UPlayerAttributeSet>(TEXT("PlayerAttributeSet"));

	BarComponent = CreateDefaultSubobject<UWidgetComponent>(TEXT("PlayerHUD"));
	BarComponent->SetupAttachment(RootComponent);

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

			AbilitySystemComponent->GetGameplayAttributeValueChangeDelegate(UPlayerAttributeSet::GetHealthAttribute()).AddUObject(this, &AMainCharacter::OnHealthChange);
			AbilitySystemComponent->GetGameplayAttributeValueChangeDelegate(UPlayerAttributeSet::GetMaxHealthAttribute()).AddUObject(this, &AMainCharacter::OnMaxHealthChange);
			AbilitySystemComponent->GetGameplayAttributeValueChangeDelegate(UPlayerAttributeSet::GetManaAttribute()).AddUObject(this, &AMainCharacter::OnManaChange);
			AbilitySystemComponent->GetGameplayAttributeValueChangeDelegate(UPlayerAttributeSet::GetMaxManaAttribute()).AddUObject(this, &AMainCharacter::OnMaxManaChange);

			if (BarComponent && BarComponent->GetWidget() && BarComponent->GetWidget()->Implements<UTwinResource>())
			{
				ITwinResource::Execute_UpdateMaxHealth(BarComponent->GetWidget(), PlayerAttributeSet->GetMaxHealth());
				ITwinResource::Execute_UpdateCurrentHealth(BarComponent->GetWidget(), PlayerAttributeSet->GetHealth());
				ITwinResource::Execute_UpdateMaxMana(BarComponent->GetWidget(), PlayerAttributeSet->GetMaxMana());
				ITwinResource::Execute_UpdateCurrentMana(BarComponent->GetWidget(), PlayerAttributeSet->GetMana());
			}
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

void AMainCharacter::OnHealthChange(const FOnAttributeChangeData& InData)
{
	if (BarComponent && BarComponent->GetWidget() && BarComponent->GetWidget()->Implements<UTwinResource>())
	{
		ITwinResource::Execute_UpdateCurrentHealth(BarComponent->GetWidget(), InData.NewValue);
	}
}

void AMainCharacter::OnMaxHealthChange(const FOnAttributeChangeData& InData)
{
	if (BarComponent && BarComponent->GetWidget() && BarComponent->GetWidget()->Implements<UTwinResource>())
	{
		ITwinResource::Execute_UpdateMaxHealth(BarComponent->GetWidget(), InData.NewValue);
	}
}

void AMainCharacter::OnManaChange(const FOnAttributeChangeData& InData)
{
	if (BarComponent && BarComponent->GetWidget() && BarComponent->GetWidget()->Implements<UTwinResource>())
	{
		ITwinResource::Execute_UpdateCurrentMana(BarComponent->GetWidget(), InData.NewValue);
	}
}

void AMainCharacter::OnMaxManaChange(const FOnAttributeChangeData& InData)
{
	if (BarComponent && BarComponent->GetWidget() && BarComponent->GetWidget()->Implements<UTwinResource>())
	{
		ITwinResource::Execute_UpdateMaxMana(BarComponent->GetWidget(), InData.NewValue);
	}
}

