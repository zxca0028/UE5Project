// Fill out your copyright notice in the Description page of Project Settings.


#include "BTTask_Attack.h"

EBTNodeResult::Type UBTTask_Attack::ExecuteTask(UBehaviorTreeComponent& ownerComp, uint8* nodeMemory)
{
	Super::ExecuteTask(ownerComp, nodeMemory);

	return EBTNodeResult::Type::InProgress;
}

void UBTTask_Attack::TickTask(UBehaviorTreeComponent& ownerComp, uint8* nodeMemory, float deltaSeconds)
{
	Super::TickTask(ownerComp, nodeMemory, deltaSeconds);

	AGlobalCharacter* character = GetGlobalCharacter(ownerComp);

	UAnimMontage* montage = character->GetAnimMontage(GetAIState(ownerComp));
	float time = montage->CalculateSequenceLength();

	if (time <= GetStateTime(ownerComp))
	{
		SetStateChange(ownerComp, MONSTER_STATE::CHASE);
		return;
	}

	return;
}
