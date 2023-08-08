// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BTTask_AIBase.h"
#include "BTTask_Chase.generated.h"

/**
 * 
 */
UCLASS()
class UE5PROJECT_API UBTTask_Chase : public UBTTask_AIBase
{
	GENERATED_BODY()
protected:
	EBTNodeResult::Type ExecuteTask(UBehaviorTreeComponent& ownerComp, uint8* nodeMemory) override;

	void TickTask(UBehaviorTreeComponent& ownerComp, uint8* nodeMemory, float deltaSeconds) override;
};
