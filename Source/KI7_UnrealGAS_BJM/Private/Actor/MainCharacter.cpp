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

	BarComponent = CreateDefaultSubobject<UWidgetComponent>(TEXT("PlayerHUD"));
	BarComponent->SetupAttachment(RootComponent);

}



// Called when the game starts or when spawned
void AMainCharacter::BeginPlay()
{
	Super::BeginPlay();

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
				UE_LOG(LogTemp, Warning, TEXT("[BeginPlay] 어빌리티 부여 성공! 클래스: %s"), *FireballAbilityClass->GetName());
			}
			else
			{
				UE_LOG(LogTemp, Error, TEXT("[BeginPlay] FireballAbilityClass가 비어있음! BP에서 설정 안 함?"));
			}

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
	//UE_LOG(LogTemp, Log, TEXT("빠이어 볼!"))
	UE_LOG(LogTemp, Log, TEXT(" [Input] 클릭 입력 감지됨!"));

	if (AbilitySystemComponent && FireballAbilityClass)
	{
		// [진단 2] 실행 시도 결과 확인
		bool bSuccess = AbilitySystemComponent->TryActivateAbilityByClass(FireballAbilityClass);

		if (bSuccess)
		{
			UE_LOG(LogTemp, Warning, TEXT("✅ [Input] TryActivate 성공! (이제 GA 로그가 떠야 함)"));
		}
		else
		{
			UE_LOG(LogTemp, Error, TEXT("❌ [Input] TryActivate 실패! (마나 부족? 쿨타임? 태그 문제? 어빌리티 부여 안됨?)"));
		}
	}
	else
	{
		UE_LOG(LogTemp, Error, TEXT("❌ [Input] ASC가 없거나 FireballAbilityClass가 None임!"));
	}

	if (AbilitySystemComponent && FireballAbilityClass)
	{
		AbilitySystemComponent->TryActivateAbilityByClass(FireballAbilityClass);
	}
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

