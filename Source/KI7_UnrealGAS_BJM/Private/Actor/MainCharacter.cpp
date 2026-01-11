// Fill out your copyright notice in the Description page of Project Settings.


#include "Actor/MainCharacter.h"
#include "AbilitySystemComponent.h"
#include "GAS/AttributeSet/PlayerAttributeSet.h"
#include "Components/WidgetComponent.h"
#include "Interface/TwinResource.h"
#include "EnhancedInputComponent.h"
#include "EnhancedInputSubsystems.h"
#include "InputMappingContext.h"

// Sets default values
AMainCharacter::AMainCharacter()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = false;

	// 컴포넌트 생성
	AbilitySystemComponent = CreateDefaultSubobject<UAbilitySystemComponent>(TEXT("AbilitySystemComponent"));

	PlayerAttributeSet = CreateDefaultSubobject<UPlayerAttributeSet>(TEXT("PlayerAttributeSet"));


}



// Called when the game starts or when spawned
void AMainCharacter::BeginPlay()
{
	Super::BeginPlay();

	if (IsLocallyControlled() && PlayerHUDClass)
	{
		PlayerHUDWidget = CreateWidget<UUserWidget>(GetWorld(), PlayerHUDClass);
		if (PlayerHUDWidget)
		{
			PlayerHUDWidget->AddToViewport();
		}
	}

	if (APlayerController* PlayerController = Cast<APlayerController>(Controller))
	{
		if (UEnhancedInputLocalPlayerSubsystem* Subsystem = ULocalPlayer::GetSubsystem<UEnhancedInputLocalPlayerSubsystem>(PlayerController->GetLocalPlayer()))
		{
			if (DefaultMappingContext)
			{
				Subsystem->AddMappingContext(DefaultMappingContext, 0);
			}
		}
	}


	if (AbilitySystemComponent)
	{
		if (AbilitySystemComponent)
		{
			AbilitySystemComponent->InitAbilityActorInfo(this, this);

			if (FireballAbilityClass)
			{
				AbilitySystemComponent->GiveAbility(FGameplayAbilitySpec(FireballAbilityClass, 1, 0, this));
				UE_LOG(LogTemp, Warning, TEXT("어빌리티 부여 성공 클래스: %s"), *FireballAbilityClass->GetName());
			}
			else
			{
				UE_LOG(LogTemp, Error, TEXT("FireballAbilityClass가 비어있음"));
			}

			AbilitySystemComponent->GetGameplayAttributeValueChangeDelegate(UPlayerAttributeSet::GetHealthAttribute()).AddUObject(this, &AMainCharacter::OnHealthChange);
			AbilitySystemComponent->GetGameplayAttributeValueChangeDelegate(UPlayerAttributeSet::GetMaxHealthAttribute()).AddUObject(this, &AMainCharacter::OnMaxHealthChange);
			AbilitySystemComponent->GetGameplayAttributeValueChangeDelegate(UPlayerAttributeSet::GetManaAttribute()).AddUObject(this, &AMainCharacter::OnManaChange);
			AbilitySystemComponent->GetGameplayAttributeValueChangeDelegate(UPlayerAttributeSet::GetMaxManaAttribute()).AddUObject(this, &AMainCharacter::OnMaxManaChange);

			if (PlayerHUDWidget && PlayerHUDWidget->Implements<UTwinResource>())
			{
				ITwinResource::Execute_UpdateMaxHealth(PlayerHUDWidget, PlayerAttributeSet->GetMaxHealth());
				ITwinResource::Execute_UpdateCurrentHealth(PlayerHUDWidget, PlayerAttributeSet->GetHealth());
				ITwinResource::Execute_UpdateMaxMana(PlayerHUDWidget, PlayerAttributeSet->GetMaxMana());
				ITwinResource::Execute_UpdateCurrentMana(PlayerHUDWidget, PlayerAttributeSet->GetMana());
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

	if (UEnhancedInputComponent* EnhancedInputComponent = Cast<UEnhancedInputComponent>(PlayerInputComponent))
	{
		if (IA_Attack)
		{
			EnhancedInputComponent->BindAction(IA_Attack, ETriggerEvent::Started, this, &AMainCharacter::OnFireInput);
		}
	}

}

void AMainCharacter::OnFireInput()
{
	UE_LOG(LogTemp, Log, TEXT("빠이어 볼!"))


	if (AbilitySystemComponent && FireballAbilityClass)
	{
		bool bSuccess = AbilitySystemComponent->TryActivateAbilityByClass(FireballAbilityClass);

		if (bSuccess)
		{
			UE_LOG(LogTemp, Warning, TEXT("TryActivate 성공"));
		}
		else
		{
			UE_LOG(LogTemp, Error, TEXT("TryActivate 실패"));
		}
	}
	else
	{
		UE_LOG(LogTemp, Error, TEXT("None임"));
	}

	if (AbilitySystemComponent && FireballAbilityClass)
	{
		AbilitySystemComponent->TryActivateAbilityByClass(FireballAbilityClass);
	}
}

void AMainCharacter::OnHealthChange(const FOnAttributeChangeData& InData)
{
	if (PlayerHUDWidget && PlayerHUDWidget->Implements<UTwinResource>())
	{
		ITwinResource::Execute_UpdateCurrentHealth(PlayerHUDWidget, InData.NewValue);
	}
}

void AMainCharacter::OnMaxHealthChange(const FOnAttributeChangeData& InData)
{
	if (PlayerHUDWidget && PlayerHUDWidget->Implements<UTwinResource>())
	{
		ITwinResource::Execute_UpdateMaxHealth(PlayerHUDWidget, InData.NewValue);
	}
}

void AMainCharacter::OnManaChange(const FOnAttributeChangeData& InData)
{
	if (PlayerHUDWidget && PlayerHUDWidget->Implements<UTwinResource>())
	{
		ITwinResource::Execute_UpdateCurrentMana(PlayerHUDWidget, InData.NewValue);
	}
}

void AMainCharacter::OnMaxManaChange(const FOnAttributeChangeData& InData)
{
	if (PlayerHUDWidget && PlayerHUDWidget->Implements<UTwinResource>())
	{
		ITwinResource::Execute_UpdateMaxMana(PlayerHUDWidget, InData.NewValue);
	}
}

