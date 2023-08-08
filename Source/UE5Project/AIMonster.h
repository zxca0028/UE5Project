// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "AICharacter.h"
#include "Enum.h"
#include "MonsterData.h"
#include "AIMonster.generated.h"

/**
 * 
 */
UCLASS()
class UE5PROJECT_API AAIMonster : public AAICharacter
{
	GENERATED_BODY()
public:
	AAIMonster();
private:
	const struct FMonsterData* currMonsterData;
public:
	void BeginPlay() override;
private:
	UPROPERTY(Category = "Animation", EditAnywhere, BlueprintReadWrite, meta = (AllowPrivateAccess = "true"))
	FName dataName = "NONE";
};
