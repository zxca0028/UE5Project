// Fill out your copyright notice in the Description page of Project Settings.


#include "AIMonsterController.h"
#include "BehaviorTree/BehaviorTreeComponent.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "BehaviorTree/BehaviorTree.h"
#include "AICharacter.h"

AAIMonsterController::AAIMonsterController()
{
	behaviorTreeComponent = CreateDefaultSubobject<UBehaviorTreeComponent>(TEXT("BehaviorTreeComponent"));
	blackboardComponent   = CreateDefaultSubobject<UBlackboardComponent>(TEXT("BlackBoardComponent"));
}

void AAIMonsterController::OnPossess(APawn* _inPawn)
{
	Super::OnPossess(_inPawn);

	if (true != behaviorTreeComponent->IsValidLowLevel() && nullptr != blackboardComponent)
	{
		AAICharacter* aiPawn = Cast<AAICharacter>(_inPawn);

		if (nullptr == aiPawn)
		{
			return;
		}

		UBehaviorTree* behaviorTree = aiPawn->GetBehaviorTree();

		if (nullptr == behaviorTree || false == behaviorTree->IsValidLowLevel())
		{
			return;
		}

		blackboardComponent->InitializeBlackboard(*behaviorTree->BlackboardAsset);
		blackboardComponent->SetValueAsObject(TEXT("SelfActor"), _inPawn);
		behaviorTreeComponent->StartTree(*behaviorTree);
	}
}
