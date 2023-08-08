#pragma once

#include "CoreMinimal.h"

UENUM(BlueprintType)
enum class PLAYER_ANISTATE : uint8
{
	NONE,
	IDLE,
	WALK,
	DASH,
	JUMP,
	LAND,
	ATTACK1,
	ATTACK2,
	ATTACK3,
	ATTACK4
};

UENUM(BlueprintType)
enum class PLAYER_STATE : uint8
{
	IDLE,
	JUMP,
	LAND,
	ATTACK1,
	ATTACK2,
	ATTACK3,
	ATTACK4,
	WALK
};

UENUM(BlueprintType)
enum class MONSTER_STATE : uint8
{
	NONE,
	IDLE,
	ATTACK,
	HIT,
	CHASE,
	PATROL,
	RETURN,
	DEATH
};
