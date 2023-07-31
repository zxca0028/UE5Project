// Fill out your copyright notice in the Description page of Project Settings.


#include "GlobalGameInstance.h"
#include "MonsterData.h"

UGlobalGameInstance::UGlobalGameInstance()
{
	FString dataPath = TEXT("/Script/Engine.DataTable'/Game/Data/DT_MonsterData.DT_MonsterData'");

	ConstructorHelpers::FObjectFinder<UDataTable> dataTable(*dataPath);

	if (dataTable.Succeeded())
	{
		monsterDatas = dataTable.Object;
	}
}

UGlobalGameInstance::~UGlobalGameInstance()
{
}

FMonsterData* UGlobalGameInstance::GetMonsterData(FName _name)
{
	if (nullptr == monsterDatas)
	{
		return nullptr;
	}

	FMonsterData* findTable = monsterDatas->FindRow<FMonsterData>(_name, _name.ToString());

	if (nullptr == findTable)
	{
		return nullptr;
	}

	return findTable;
}
