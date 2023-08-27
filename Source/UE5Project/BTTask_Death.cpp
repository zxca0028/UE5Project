// Fill out your copyright notice in the Description page of Project Settings.


#include "BTTask_Death.h"
#include "GameFramework/CharacterMovementComponent.h"

EBTNodeResult::Type UBTTask_Death::ExecuteTask(UBehaviorTreeComponent& ownerComp, uint8* nodeMemory)
{
	Super::ExecuteTask(ownerComp, nodeMemory);

	AGlobalCharacter* character = GetGlobalCharacter(ownerComp);

	UCharacterMovementComponent* movement = character->GetCharacterMovement();

	FVector impulseVector = character->GetActorForwardVector() * -300.f;

	impulseVector.Z = 300.f;

	movement->AddImpulse(impulseVector, true);

	return EBTNodeResult::Type::InProgress;
}

void UBTTask_Death::TickTask(UBehaviorTreeComponent& ownerComp, uint8* nodeMemory, float deltaSeconds)
{
	Super::TickTask(ownerComp, nodeMemory, deltaSeconds);

	AGlobalCharacter* character = GetGlobalCharacter(ownerComp);

	UAnimMontage* montage = character->GetAnimMontage(GetAIState(ownerComp));
	float time = montage->CalculateSequenceLength();

	if (time / 4.f <= GetStateTime(ownerComp) )
	{
		GetGlobalCharacter(ownerComp)->GetMesh()->SetSimulatePhysics(true);
		GetGlobalCharacter(ownerComp)->GetCharacterMovement()->DisableMovement();
	}

	if (time*5 <= GetStateTime(ownerComp))
	{
		character->Destroy();
	}

	return;
}
