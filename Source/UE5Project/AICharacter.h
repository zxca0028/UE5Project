// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GlobalCharacter.h"
#include "AICharacter.generated.h"

/**
 * 
 */
UCLASS()
class UE5PROJECT_API AAICharacter : public AGlobalCharacter
{
	GENERATED_BODY()
public:
	FORCEINLINE class UBehaviorTree* GetBehaviorTree()
	{
		return behaviorTree;
	}
	class UBlackboardComponent* GetBlackboardCompoent();
public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Data")
	class UBehaviorTree* behaviorTree;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Data")
	class UBlackboardComponent* blackboardComponent;
};
