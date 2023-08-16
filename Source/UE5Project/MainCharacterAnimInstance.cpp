// Fill out your copyright notice in the Description page of Project Settings.


#include "MainCharacterAnimInstance.h"
#include "MainCharacter.h"

void UMainCharacterAnimInstance::NativeBeginPlay()
{
	Super::NativeBeginPlay();

	OnMontageBlendingOut.AddDynamic(this, &UMainCharacterAnimInstance::MontageEnd);

	AMainCharacter* character = Cast<AMainCharacter>(GetOwningActor());

	allAnimations = character->allAnimations;
}

void UMainCharacterAnimInstance::NativeUpdateAnimation(float deltaTime)
{
	Super::NativeUpdateAnimation(deltaTime);

	if (0 == allAnimations.Num())
	{
		return;
	}

	AMainCharacter* character = Cast<AMainCharacter>(GetOwningActor());

	aniState = character->aniState;

	class UAnimMontage* montage = allAnimations[aniState];

	if (nullptr == montage)
	{
		return;
	}

	if (false == Montage_IsPlaying(montage))
	{
		if (montage == currMontage && montage->bLoop == true)
		{
			return;
		}

		UE_LOG(LogTemp, Log, TEXT("Player State : %s"), *UEnum::GetValueAsString(aniState));

		currMontage = montage;
		Montage_Play(montage, 1.0f);
	}
}

void UMainCharacterAnimInstance::MontageEnd(UAnimMontage* _anim, bool _inter)
{
	//TSubclassOf<UMainCharacterAnimInstance> instance = UMainCharacterAnimInstance::StaticClass();

	AMainCharacter* character = Cast< AMainCharacter>(GetOwningActor());

	if (_inter == false)
	{
		if (allAnimations[PLAYER_ANISTATE::LAND] == _anim ||
			allAnimations[PLAYER_ANISTATE::ATTACK1] == _anim ||
			allAnimations[PLAYER_ANISTATE::ATTACK2] == _anim ||
			allAnimations[PLAYER_ANISTATE::ATTACK3] == _anim ||
			allAnimations[PLAYER_ANISTATE::ATTACK4] == _anim
			)
		{
			character->aniState = PLAYER_ANISTATE::IDLE;
			aniState = PLAYER_ANISTATE::IDLE;
			Montage_Play(allAnimations[aniState], 1.0f);
		}
	}
}
