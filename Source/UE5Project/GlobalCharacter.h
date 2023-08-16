// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "GlobalCharacter.generated.h"

UCLASS()
class UE5PROJECT_API AGlobalCharacter : public ACharacter
{
	GENERATED_BODY()
protected:
	int iHP = 0;
public:
	void SetHP(int _hp)
	{
		iHP = _hp;
	}
private:
	UPROPERTY(Category = "GameModeValue", EditAnywhere, BlueprintReadWrite, meta = (AllowPrivateAccess = "true"))
	int aniState = 0;
	UPROPERTY(Category = "GameModeValue", EditAnywhere, BlueprintReadWrite, meta = (AllowPrivateAccess = "true"))
	TMap<int, class UAnimMontage*> allAnimation;
private:
	class UGlobalAnimInstance* globalAnimInstance = nullptr;
public:
	int GetAniState()
	{
		return aniState;
	}
	template<typename EnumType>
	void SetAniState(EnumType _aniState)
	{
		aniState = static_cast<int8>(_aniState);
	}
	/*void SetAniState(int _aniState)
	{
		aniState = _aniState;
	}*/
	template<typename EnumType>
	class UAnimMontage* GetAnimMontage(EnumType _index)
	{
		return GetAnimMontage(static_cast<int>(_index));
	}

	class UAnimMontage* GetAnimMontage(int _index)
	{
		if (false == allAnimation.Contains(_index))
		{
			return nullptr;
		}

		return allAnimation[_index];
	}
	template<typename EnumType>
	void SetAllAnimation(const TMap<EnumType, class UAnimMontage*>& _mapAnimation)
	{
		for (TPair<EnumType, UAnimMontage*> pair : _mapAnimation)
		{
			allAnimation.Add(static_cast<int8>(pair.Key), pair.Value);
		}
	}
protected:
	template<typename EnumType>
	void PushAnimation(EnumType _index, class UAnimMontage* _montage)
	{
		PushAnimation(static_cast<int8>(_index) _montage);
	}
	void PushAnimation(int _index, class UAnimMontage* _montage)
	{
		if (true == allAnimation.Contains(_index))
		{
			return;
		}

		allAnimation.Add(_index, _montage);
	}
public:
	// Sets default values for this character's properties
	AGlobalCharacter();
protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;
public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;
	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

};
