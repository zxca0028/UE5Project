// Fill out your copyright notice in the Description page of Project Settings.


#include "AIMonster.h"
#include "MonsterData.h"
#include "GlobalGameInstance.h"
#include "BehaviorTree/BlackboardComponent.h"

void AAIMonster::BeginPlay()
{
	UGlobalGameInstance* instance = GetWorld()->GetGameInstance<UGlobalGameInstance>();

	if (nullptr != instance)
	{
		currMonsterData = instance->GetMonsterData(dataName);

		SetAllAnimation<MONSTER_STATE>(currMonsterData->MapAnimation);
		SetAniState<MONSTER_STATE>(MONSTER_STATE::IDLE);
	}

	Super::BeginPlay();

	GetBlackboardCompoent()->SetValueAsEnum(TEXT("AISTATE"), static_cast<int>(MONSTER_STATE::IDLE));
	GetBlackboardCompoent()->SetValueAsString(TEXT("TargetTag"), TEXT("Player"));
	GetBlackboardCompoent()->SetValueAsFloat(TEXT("SearchRange"), 1500.f);
	GetBlackboardCompoent()->SetValueAsFloat(TEXT("AttackRange"), 200.f);
	GetBlackboardCompoent()->SetValueAsVector(TEXT("OriginPos"), GetActorLocation());
}
