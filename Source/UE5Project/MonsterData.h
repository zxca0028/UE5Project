// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/DataTable.h"
#include "UObject/NoExportTypes.h"
#include "Enum.h"
#include "MonsterData.generated.h"

/**
 * 
 */
USTRUCT(BlueprintType)
struct UE5PROJECT_API FMonsterData : public FTableRowBase
{
	GENERATED_BODY()
public:
	 FMonsterData() {}
	~FMonsterData() {}
public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Data")
	int HP;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Data")
	int ATK;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Data")
	class UBehaviorTree* AI;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Data")
	TMap<MONSTER_STATE, class UAnimMontage*> MapAnimation;
};
