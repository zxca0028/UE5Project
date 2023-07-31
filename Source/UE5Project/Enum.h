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
	ATTACK
};

UENUM(BlueprintType)
enum class PLAYER_STATE : uint8
{
	IDLE,
	JUMP,
	LAND,
	WALK
};

UENUM(BlueprintType)
enum class MONSTER_STATE : uint8
{
	IDLE,
	ATTACK,
	HIT,
	CHASE,
	PATROL,
	RETURN,
	DEATH
};
