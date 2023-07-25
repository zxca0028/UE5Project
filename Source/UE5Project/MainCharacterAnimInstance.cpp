// Fill out your copyright notice in the Description page of Project Settings.


#include "MainCharacterAnimInstance.h"
#include "MainCharacter.h"

void UMainCharacterAnimInstance::NativeBeginPlay()
{
	Super::NativeBeginPlay();

	OnMontageEnded.AddDynamic(this, &UMainCharacterAnimInstance::MontageEnd);

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



	if (false == Montage_IsPlaying(montage))
	{
		Montage_Play(montage, 1.0f);
	}
}

void UMainCharacterAnimInstance::MontageEnd(UAnimMontage* _anim, bool _inter)
{
	TSubclassOf<UMainCharacterAnimInstance> instance = UMainCharacterAnimInstance::StaticClass();

	AMainCharacter* character = Cast< AMainCharacter>(GetOwningActor());
}
