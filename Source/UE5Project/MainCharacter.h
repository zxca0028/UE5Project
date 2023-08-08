// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "Enum.h"
#include "InputActionValue.h"
#include "EnhancedInputComponent.h"
#include "EnhancedInputSubsystems.h"
#include "MainCharacter.generated.h"

UCLASS()
class UE5PROJECT_API AMainCharacter : public ACharacter
{
	GENERATED_BODY()
public:
	PLAYER_STATE eState = PLAYER_STATE::IDLE;
public:
	UPROPERTY(Category = "AnimationValue", EditAnywhere, BlueprintReadWrite)
	PLAYER_ANISTATE aniState = PLAYER_ANISTATE::IDLE;

	UPROPERTY(Category = "AnimationValue", EditAnywhere, BlueprintReadWrite)
	TMap<PLAYER_ANISTATE, class UAnimMontage*> allAnimations;
public:
	// Sets default values for this character's properties
	AMainCharacter();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;
public:
	UPROPERTY(EditAnywhere, Category = "Input")
	class UInputMappingContext* DefalutIMC = nullptr;
	UPROPERTY(EditAnywhere, Category = "Input")
	class UInputAction* JumpAction = nullptr;
	UPROPERTY(EditAnywhere, Category = "Input")
	class UInputAction* MoveAction = nullptr;
	UPROPERTY(EditAnywhere, Category = "Input")
	class UInputAction* LookAction = nullptr;
	UPROPERTY(EditAnywhere, Category = "Input")
	class UInputAction* AttackAction = nullptr;
private:
	void Move(const FInputActionInstance& inst);
	void Look(const FInputActionInstance& inst);
	void Jump() override;
	void Attack();
};
