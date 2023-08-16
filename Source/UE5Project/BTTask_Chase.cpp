// Fill out your copyright notice in the Description page of Project Settings.


#include "BTTask_Chase.h"
#include "GlobalCharacter.h"

EBTNodeResult::Type UBTTask_Chase::ExecuteTask(UBehaviorTreeComponent& ownerComp, uint8* nodeMemory)
{
	Super::ExecuteTask(ownerComp, nodeMemory);

	return EBTNodeResult::Type::InProgress;
}

void UBTTask_Chase::TickTask(UBehaviorTreeComponent& ownerComp, uint8* nodeMemory, float deltaSeconds)
{
	Super::TickTask(ownerComp, nodeMemory, deltaSeconds);

	AActor* resultTarget = Cast<AActor>(GetBlackboardComponent(ownerComp)->GetValueAsObject(TEXT("TargetActor")));

	if (nullptr == resultTarget)
	{
		SetStateChange(ownerComp, MONSTER_STATE::IDLE);
		return;
	}

	FVector targetPos = resultTarget->GetActorLocation();
	FVector myPos = GetGlobalCharacter(ownerComp)->GetActorLocation();
	targetPos.Z = 0.0f;
	myPos.Z = 0.0f;

	FVector dir = targetPos - myPos;

	GetGlobalCharacter(ownerComp)->AddMovementInput(dir);

	int tt = GetBlackboardComponent(ownerComp)->GetValueAsInt(TEXT("HP"));

	if (0 >= GetBlackboardComponent(ownerComp)->GetValueAsInt(TEXT("HP")))
	{
		SetStateChange(ownerComp, MONSTER_STATE::DEATH);
		return;
	}

	return;
}
