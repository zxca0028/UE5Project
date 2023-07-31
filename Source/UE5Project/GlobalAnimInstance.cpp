// Fill out your copyright notice in the Description page of Project Settings.


#include "GlobalAnimInstance.h"
#include "GlobalCharacter.h"

void UGlobalAnimInstance::NativeBeginPlay()
{
	Super::NativeBeginPlay();
}

void UGlobalAnimInstance::NativeUpdateAnimation(float _deltaTime)
{
	Super::NativeUpdateAnimation(_deltaTime);

	if (0 == allAnimation.Num())
	{
		return;
	}

	AGlobalCharacter* character = Cast<AGlobalCharacter>(GetOwningActor());

	if (nullptr == character && false == character->IsValidLowLevel())
	{
		return;
	}

	aniState = character->GetAniState();

	class UAnimMontage* montage = allAnimation[aniState];

	if (nullptr == montage)
	{
		return;
	}

	if (false == Montage_IsPlaying(montage))
	{
		Montage_Play(montage, 1.0f);
	}
}
