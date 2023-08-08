// Fill out your copyright notice in the Description page of Project Settings.


#include "BTTask_Idle.h"

EBTNodeResult::Type UBTTask_Idle::ExecuteTask(UBehaviorTreeComponent& ownerComp, uint8* nodeMemory)
{
	Super::ExecuteTask(ownerComp, nodeMemory);

	return EBTNodeResult::Type::InProgress;
}

void UBTTask_Idle::TickTask(UBehaviorTreeComponent& ownerComp, uint8* nodeMemory, float deltaSeconds)
{
	Super::TickTask(ownerComp, nodeMemory, deltaSeconds);

	AActor* resultTarget = Cast<AActor>(GetBlackboardComponent(ownerComp)->GetValueAsObject(TEXT("TargetActor")));

	if (nullptr != resultTarget)
	{
		SetStateChange(ownerComp, MONSTER_STATE::CHASE);
		return;
	}

	return;
}
