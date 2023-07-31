// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/GameInstance.h"
#include "Engine/DataTable.h"
#include "GlobalGameInstance.generated.h"

/**
 * 
 */
UCLASS()
class UE5PROJECT_API UGlobalGameInstance : public UGameInstance
{
	GENERATED_BODY()
public:
	UGlobalGameInstance();
	~UGlobalGameInstance();

	struct FMonsterData* GetMonsterData(FName _name);
private:
	UPROPERTY()
	UDataTable* monsterDatas;
};
