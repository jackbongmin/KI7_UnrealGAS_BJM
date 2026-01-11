// Fill out your copyright notice in the Description page of Project Settings.


#include "Actor/Enemy.h"
#include "AbilitySystemComponent.h"
#include "Components/WidgetComponent.h"
#include "GAS/AttributeSet/EnemyAttributeSet.h"
#include "Interface/TwinResource.h"

// Sets default values
AEnemy::AEnemy()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	AbilitySystemComponent = CreateDefaultSubobject<UAbilitySystemComponent>(TEXT("AbilitySystemComponent"));
	EnemyAttributeSet = CreateDefaultSubobject<UEnemyAttributeSet>(TEXT("EnemyAttributeSet"));

	HealthWidgetComponent = CreateDefaultSubobject<UWidgetComponent>(TEXT("HealthWidget"));
	HealthWidgetComponent->SetupAttachment(RootComponent);
}

// Called when the game starts or when spawned
void AEnemy::BeginPlay()
{
	Super::BeginPlay();

	if (AbilitySystemComponent)
	{
		AbilitySystemComponent->InitAbilityActorInfo(this, this);

		AbilitySystemComponent->GetGameplayAttributeValueChangeDelegate(UEnemyAttributeSet::GetHealthAttribute()).AddUObject(this, &AEnemy::OnHealthChange);
		AbilitySystemComponent->GetGameplayAttributeValueChangeDelegate(UEnemyAttributeSet::GetMaxHealthAttribute()).AddUObject(this, &AEnemy::OnMaxHealthChange);

		if (HealthWidgetComponent && HealthWidgetComponent->GetWidget() && HealthWidgetComponent->GetWidget()->Implements<UTwinResource>())
		{
			ITwinResource::Execute_UpdateMaxHealth(HealthWidgetComponent->GetWidget(), EnemyAttributeSet->GetMaxHealth());
			ITwinResource::Execute_UpdateCurrentHealth(HealthWidgetComponent->GetWidget(), EnemyAttributeSet->GetHealth());
		}
	}

}

// Called every frame
void AEnemy::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

// Called to bind functionality to input
void AEnemy::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

}

void AEnemy::OnHealthChange(const FOnAttributeChangeData& InData)
{
	if (HealthWidgetComponent && HealthWidgetComponent->GetWidget() && HealthWidgetComponent->GetWidget()->Implements<UTwinResource>())
	{
		ITwinResource::Execute_UpdateCurrentHealth(HealthWidgetComponent->GetWidget(), InData.NewValue);
	}
}

void AEnemy::OnMaxHealthChange(const FOnAttributeChangeData& InData)
{
	if (HealthWidgetComponent && HealthWidgetComponent->GetWidget() && HealthWidgetComponent->GetWidget()->Implements<UTwinResource>())
	{
		ITwinResource::Execute_UpdateMaxHealth(HealthWidgetComponent->GetWidget(), InData.NewValue);
	}
}

