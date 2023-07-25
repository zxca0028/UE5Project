// Fill out your copyright notice in the Description page of Project Settings.


#include "MainCharacter.h"
#include "InputActionValue.h"
#include "EnhancedInputComponent.h"
#include "EnhancedInputSubsystems.h"

// Sets default values
AMainCharacter::AMainCharacter()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

// Called when the game starts or when spawned
void AMainCharacter::BeginPlay()
{
	Super::BeginPlay();
	
	APlayerController* playerController = Cast<APlayerController>(Controller);
	if (nullptr != playerController)
	{
		UEnhancedInputLocalPlayerSubsystem* subsystem = ULocalPlayer::GetSubsystem< UEnhancedInputLocalPlayerSubsystem>(playerController->GetLocalPlayer());
		if (nullptr != subsystem)
		{
			subsystem->AddMappingContext(DefalutIMC, 0);
		}
	}
}

// Called every frame
void AMainCharacter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

// Called to bind functionality to input
void AMainCharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

	UEnhancedInputComponent* input = Cast< UEnhancedInputComponent>(PlayerInputComponent);
	if (nullptr != input)
	{
		input->BindAction(JumpAction, ETriggerEvent::Triggered, this, &AMainCharacter::Jump);
		input->BindAction(JumpAction, ETriggerEvent::Completed, this, &AMainCharacter::StopJumping);

		input->BindAction(MoveAction, ETriggerEvent::Triggered, this, &AMainCharacter::Move);
		
		input->BindAction(LookAction, ETriggerEvent::Triggered, this, &AMainCharacter::Look);
	}
}

void AMainCharacter::Move(const FInputActionInstance& inst)
{
	FVector2D movementVector = inst.GetValue().Get<FVector2D>();

	if (nullptr != Controller)
	{
		const FRotator rotation    = Controller->GetControlRotation();
		const FRotator yawRotation = FRotator(0, rotation.Yaw, 0);
		const FVector  forward     = FRotationMatrix(yawRotation).GetUnitAxis(EAxis::X);
		const FVector  right       = FRotationMatrix(yawRotation).GetUnitAxis(EAxis::Y);

		AddMovementInput(forward, movementVector.Y);
		AddMovementInput(right,   movementVector.X);
	}
}

void AMainCharacter::Look(const FInputActionInstance& inst)
{
	FVector2D lookVector = inst.GetValue().Get<FVector2D>();

	if (nullptr != Controller)
	{
		AddControllerYawInput(lookVector.X);
		AddControllerPitchInput(lookVector.Y);
	}
}

void AMainCharacter::Jump()
{
	Super::Jump();

	aniState = PLAYER_ANISTATE::JUMP;
}

void AMainCharacter::StopJumping()
{
	Super::StopJumping();

	aniState = PLAYER_ANISTATE::LAND;
}

