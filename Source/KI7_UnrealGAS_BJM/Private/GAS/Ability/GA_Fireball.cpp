// Fill out your copyright notice in the Description page of Project Settings.


#include "GAS/Ability/GA_Fireball.h"
#include "Actor/FireballProjectile.h"
#include "GameFramework/Character.h"


UGA_Fireball::UGA_Fireball()
{
	InstancingPolicy = EGameplayAbilityInstancingPolicy::InstancedPerActor;
}

void UGA_Fireball::ActivateAbility(const FGameplayAbilitySpecHandle Handle, const FGameplayAbilityActorInfo* ActorInfo, const FGameplayAbilityActivationInfo ActivationInfo, const FGameplayEventData* TriggerEventData)
{

	//UE_LOG(LogTemp, Warning, TEXT("어빌리티 활성화 시도"));

	if (!CommitAbility(Handle, ActorInfo, ActivationInfo))
	{
		//UE_LOG(LogTemp, Error, TEXT("코스트/쿨타임 때문에 실패"));
		EndAbility(Handle, ActorInfo, ActivationInfo, true, true);
		return;
	}

	ACharacter* Character = Cast<ACharacter>(ActorInfo->AvatarActor.Get());
	if (Character && ProjectileClass)
	{
		//UE_LOG(LogTemp, Warning, TEXT("발사체 생성 시도"));
		FVector SpawnLocation = Character->GetActorLocation() + (Character->GetActorForwardVector() * 50.0f);
		FRotator SpawnRotation = Character->GetControlRotation();

		FActorSpawnParameters SpawnParams;
		SpawnParams.Owner = Character;
		SpawnParams.Instigator = Character;

		GetWorld()->SpawnActor<AFireballProjectile>(ProjectileClass, SpawnLocation, SpawnRotation, SpawnParams);
	}
	else
	{
	
	}

	EndAbility(Handle, ActorInfo, ActivationInfo, true, false);
}
