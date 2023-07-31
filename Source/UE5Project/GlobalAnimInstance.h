// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Animation/AnimInstance.h"
#include "GlobalAnimInstance.generated.h"

/**
 * 
 */
UCLASS()
class UE5PROJECT_API UGlobalAnimInstance : public UAnimInstance
{
	GENERATED_BODY()
public:
	UPROPERTY(Category = "GameModeValue", EditAnywhere, BlueprintReadWrite)
	int aniState = 0;
	
	TMap<int, class UAnimMontage*> allAnimation;
protected:
	void NativeBeginPlay() override;
	void NativeUpdateAnimation(float _deltaTime) override;
};
