// Fill out your copyright notice in the Description page of Project Settings.


#include "BTTask_Test.h"

UBTTask_Test::UBTTask_Test()
{
	bNotifyTick = true;
	bNotifyTaskFinished = true;
}

void UBTTask_Test::OnGameplayTaskActivated(UGameplayTask&)
{
}

EBTNodeResult::Type UBTTask_Test::ExcuteTask(UBehaviorTreeComponent& ownerComp, uint8* nodeMemory)
{
	Super::ExecuteTask(ownerComp, nodeMemory);

	return EBTNodeResult::Type::InProgress;
}

void UBTTask_Test::TickTask(UBehaviorTreeComponent& ownerComp, uint8* nodeMemory, float deltaSeconds)
{
	Super::TickTask(ownerComp, nodeMemory, deltaSeconds);

	return;
}
