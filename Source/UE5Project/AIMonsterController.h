// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "AIController.h"
#include "AIMonsterController.generated.h"

/**
 * 
 */
UCLASS()
class UE5PROJECT_API AAIMonsterController : public AAIController
{
	GENERATED_BODY()
public:
	AAIMonsterController();
public:
	void OnPossess(APawn* _inPawn) override;
public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Data")
	class UBehaviorTreeComponent* behaviorTreeComponent;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Data")
	class UBlackboardComponent* blackboardComponent;
};
