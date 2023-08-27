// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Animation/AnimInstance.h"
#include "Enum.h"
#include "MainCharacterAnimInstance.generated.h"

/**
 * 
 */
UCLASS()
class UE5PROJECT_API UMainCharacterAnimInstance : public UAnimInstance
{
	GENERATED_BODY()
private:
	class UAnimMontage* currMontage = nullptr;
protected:
	void NativeBeginPlay() override;
	void NativeUpdateAnimation(float deltaTime) override;
public:
	UPROPERTY(Category = "AnimationValue", EditAnywhere, BlueprintReadWrite)
	PLAYER_ANISTATE aniState = PLAYER_ANISTATE::IDLE;

	TMap<PLAYER_ANISTATE, class UAnimMontage*> allAnimations;

	UFUNCTION()
	void MontageEnd(UAnimMontage* _anim, bool _inter);

	UFUNCTION()
	void AnimNotify_COMBO();
};
