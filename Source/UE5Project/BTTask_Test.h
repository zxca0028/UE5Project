// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BehaviorTree/Tasks/BTTask_BlackboardBase.h"
#include "BTTask_Test.generated.h"

/**
 * 
 */
UCLASS()
class UE5PROJECT_API UBTTask_Test : public UBTTask_BlackboardBase
{
	GENERATED_BODY()
public:
	UBTTask_Test();
	void OnGameplayTaskActivated(class UGameplayTask&) override;
public:
	EBTNodeResult::Type ExcuteTask(UBehaviorTreeComponent& ownerComp, uint8* nodeMemory);
	virtual void TickTask(UBehaviorTreeComponent& ownerComp, uint8* nodeMemory, float deltaSeconds) override;
};
