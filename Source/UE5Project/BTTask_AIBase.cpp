// Fill out your copyright notice in the Description page of Project Settings.


#include "BTTask_AIBase.h"
#include "AIMonsterController.h"
#include "GlobalCharacter.h"
#include "Kismet/GameplayStatics.h"

UBTTask_AIBase::UBTTask_AIBase()
{
	bNotifyTick = true;
	bNotifyTaskFinished = true;
}

void UBTTask_AIBase::OnGameplayTaskActivated(UGameplayTask&)
{
}

float UBTTask_AIBase::GetStateTime(UBehaviorTreeComponent& ownerComp)
{
	UBlackboardComponent* blackBoard = ownerComp.GetBlackboardComponent();

	if (nullptr == blackBoard)
	{
		return 0.0f;
	}

	float stateTime = blackBoard->GetValueAsFloat(TEXT("StateTime"));

	return stateTime;
}

MONSTER_STATE UBTTask_AIBase::GetAIState(UBehaviorTreeComponent& ownerComp)
{
	UBlackboardComponent* blackBoard = ownerComp.GetBlackboardComponent();

	if (nullptr == blackBoard)
	{
		return MONSTER_STATE::NONE;
	}

	uint8 Enum = blackBoard->GetValueAsEnum(TEXT("AIState"));

	return static_cast<MONSTER_STATE>(Enum);
}

void UBTTask_AIBase::ResetStateTime(UBehaviorTreeComponent& ownerComp)
{
	UBlackboardComponent* blackBoard = ownerComp.GetBlackboardComponent();

	if (nullptr == blackBoard)
	{
		return;
	}

	blackBoard->SetValueAsFloat(TEXT("StateTime"), 0.0f);
}

void UBTTask_AIBase::SetStateChange(UBehaviorTreeComponent& ownerComp, uint8 _state)
{
	UBlackboardComponent* blackBoard = ownerComp.GetBlackboardComponent();

	if (nullptr == blackBoard)
	{
		return;
	}

	blackBoard->SetValueAsEnum(TEXT("AIState"), _state);

	ResetStateTime(ownerComp);

	FinishLatentTask(ownerComp, EBTNodeResult::Type::Failed);
}

AGlobalCharacter* UBTTask_AIBase::GetGlobalCharacter(UBehaviorTreeComponent& ownerComp)
{
	AAIMonsterController* aiController = ownerComp.GetOwner<AAIMonsterController>();

	if (nullptr == aiController || false == aiController->IsValidLowLevel())
	{
		return nullptr;
	}

	AGlobalCharacter* character = aiController->GetPawn<AGlobalCharacter>();

	if (nullptr == character || false == character->IsValidLowLevel())
	{
		return nullptr;
	}

	return character;
}

AActor* UBTTask_AIBase::GetTargetSearch(UBehaviorTreeComponent& ownerComp)
{
	FString targetTag = GetBlackboardComponent(ownerComp)->GetValueAsString(TEXT("TargetTag"));
	TArray<AActor*> targetActors;
	UGameplayStatics::GetAllActorsWithTag(GetWorld(), *targetTag, targetActors);

	AGlobalCharacter* pawn = GetGlobalCharacter(ownerComp);

	float searchRange = GetBlackboardComponent(ownerComp)->GetValueAsFloat(TEXT("SearchRange"));

	AActor* resultActor = nullptr;

	if (0 != targetActors.Num())
	{
		float min = TNumericLimits<float>::Max();

		for (AActor* actor : targetActors)
		{
			FVector actorLocation = actor->GetActorLocation();
			FVector myLocation    = pawn->GetActorLocation();

			float distance = (actorLocation - myLocation).Length();

			if (distance <= searchRange)
			{
				if (distance <= min)
				{
					min = distance;
					resultActor = actor;
				}
			}
		}
	}

	return resultActor;
}

UBlackboardComponent* UBTTask_AIBase::GetBlackboardComponent(UBehaviorTreeComponent& ownerComp)
{
	UBlackboardComponent* blackBoard = ownerComp.GetBlackboardComponent();

	if (nullptr == blackBoard)
	{
		return nullptr;
	}

	return blackBoard;
}

EBTNodeResult::Type UBTTask_AIBase::ExecuteTask(UBehaviorTreeComponent& ownerComp, uint8* nodeMemory)
{
	GetGlobalCharacter(ownerComp)->SetAniState(GetAIState(ownerComp));

	return EBTNodeResult::Type::InProgress;
}

void UBTTask_AIBase::TickTask(UBehaviorTreeComponent& ownerComp, uint8* nodeMemory, float deltaSeconds)
{
	UBlackboardComponent* blackBoard = GetBlackboardComponent(ownerComp);

	float stateTime = blackBoard->GetValueAsFloat(TEXT("StateTime"));
	stateTime += deltaSeconds;
	blackBoard->SetValueAsFloat(TEXT("StateTime"), stateTime);

	AActor* resultActor = GetTargetSearch(ownerComp);
	GetBlackboardComponent(ownerComp)->SetValueAsObject(TEXT("TargetActor"), resultActor);
}
