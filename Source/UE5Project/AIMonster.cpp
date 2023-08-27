// Fill out your copyright notice in the Description page of Project Settings.


#include "AIMonster.h"
#include "MonsterData.h"
#include "MainCharacter.h"
#include "GlobalGameInstance.h"
#include "Components/CapsuleComponent.h"
#include "BehaviorTree/BlackboardComponent.h"

AAIMonster::AAIMonster()
{
	Tags.Add(TEXT("Monster"));
}

void AAIMonster::BeginPlay()
{
	UGlobalGameInstance* instance = GetWorld()->GetGameInstance<UGlobalGameInstance>();

	if (nullptr != instance)
	{
		currMonsterData = instance->GetMonsterData(dataName);

		SetAllAnimation<MONSTER_STATE>(currMonsterData->MapAnimation);
		SetAniState<MONSTER_STATE>(MONSTER_STATE::IDLE);
		SetHP(currMonsterData->HP);
	}

	Super::BeginPlay();

	GetBlackboardCompoent()->SetValueAsEnum(TEXT("AIState"), static_cast<int>(MONSTER_STATE::IDLE));
	GetBlackboardCompoent()->SetValueAsString(TEXT("TargetTag"), TEXT("Player"));
	GetBlackboardCompoent()->SetValueAsFloat(TEXT("SearchRange"), 3000.f);
	GetBlackboardCompoent()->SetValueAsFloat(TEXT("AttackRange"), 200.f);
	GetBlackboardCompoent()->SetValueAsVector(TEXT("OriginPos"), GetActorLocation());
	GetBlackboardCompoent()->SetValueAsInt(TEXT("HP"), iHP);

	GetCapsuleComponent()->OnComponentBeginOverlap.AddDynamic(this, &AAIMonster::BeginMonsterOverLap);
	/*
	UActorComponent* test = GetComponentsByTag(UCapsuleComponent::StaticClass(), TEXT("Monster"))[0];

	Cast<UCapsuleComponent>(test)->OnComponentBeginOverlap.AddDynamic(this, &AAIMonster::BeginMonsterOverLap);*/
}

void AAIMonster::BeginMonsterOverLap(UPrimitiveComponent* overlappedComponent, AActor* otherActor, UPrimitiveComponent* otherComp, int32 otherBodyIndex, bool bFromSweep, const FHitResult& sweepResult)
{
	AMainCharacter* playerActor = Cast<AMainCharacter>(otherActor);

	if (true != playerActor->IsAttacking())
	{
		return;
	}

	iHP -= 1;

	GetBlackboardCompoent()->SetValueAsInt(TEXT("HP"), iHP);
}
