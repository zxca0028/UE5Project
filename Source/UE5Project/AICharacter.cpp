// Fill out your copyright notice in the Description page of Project Settings.


#include "AICharacter.h"
#include "AIMonsterController.h"

UBlackboardComponent* AAICharacter::GetBlackboardCompoent()
{
    if (nullptr == blackboardComponent)
    {
        AAIMonsterController* aiController = GetController<AAIMonsterController>();

        if (nullptr == aiController)
        {
            return nullptr;
        }

        blackboardComponent = aiController->GetBlackboardComponent();
    }

    return blackboardComponent;
}
