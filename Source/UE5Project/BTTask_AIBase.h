// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BehaviorTree/Tasks/BTTask_BlackboardBase.h"
#include "Enum.h"
#include <BehaviorTree/BlackboardComponent.h>
#include "BTTask_AIBase.generated.h"

/**
 * 
 */
UCLASS()
class UE5PROJECT_API UBTTask_AIBase : public UBTTask_BlackboardBase
{
	GENERATED_BODY()
public:
	UBTTask_AIBase();
	void OnGameplayTaskActivated(class UGameplayTask&) override;

	float GetStateTime(UBehaviorTreeComponent& ownerComp);

	MONSTER_STATE GetAIState(UBehaviorTreeComponent& ownerComp);

	void ResetStateTime(UBehaviorTreeComponent& ownerComp);

	template<typename EnumType>
	void SetStateChange(UBehaviorTreeComponent& ownerComp, EnumType _state)
	{
		SetStateChange(ownerComp, static_cast<uint8>(_state));
	}

	void SetStateChange(UBehaviorTreeComponent& ownerComp, uint8 _state);

	class AGlobalCharacter* GetGlobalCharacter(UBehaviorTreeComponent& ownerComp);
	class AActor* GetTargetSearch(UBehaviorTreeComponent& ownerComp);
	class UBlackboardComponent* GetBlackboardComponent(UBehaviorTreeComponent& ownerComp);

	EBTNodeResult::Type ExecuteTask(UBehaviorTreeComponent& ownerComp, uint8* nodeMemory) override;

	virtual void TickTask(UBehaviorTreeComponent& ownerComp, uint8* nodeMemory, float deltaSeconds) override;
};
