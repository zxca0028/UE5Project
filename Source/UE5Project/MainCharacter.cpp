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

	eState = PLAYER_STATE::IDLE;
}

// Called every frame
void AMainCharacter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	auto v = GetVelocity();

	UE_LOG(LogTemp, Warning, TEXT("X : %.3f, Y : %.3f, Z : %.3f"), v.X, v.Y, v.Z);


	switch (eState)
	{
	case AMainCharacter::PLAYER_STATE::IDLE:
		aniState = PLAYER_ANISTATE::IDLE;
		break;

	case AMainCharacter::PLAYER_STATE::JUMP:

		if (v.Z >= 0.01f)
		{
			aniState = PLAYER_ANISTATE::JUMP;
		}
		else if (v.Z <= -0.01f)
		{
			aniState = PLAYER_ANISTATE::LAND;

		}
		else
		{
			if (abs(v.X) >= 0.01f || abs(v.Y) >= 0.01f)
			{
				eState = PLAYER_STATE::WALK;
			}
			else
			{
				eState = PLAYER_STATE::IDLE;
			}
		}

		break;
	case AMainCharacter::PLAYER_STATE::LAND:
		aniState = PLAYER_ANISTATE::LAND;
		break;

	case AMainCharacter::PLAYER_STATE::WALK:

		if (abs(v.Z) >= 0.01f)
		{
			break;
		}

		aniState = PLAYER_ANISTATE::WALK;

		if (v.X <= 0.01f && v.Y <= 0.01f)
		{
			eState = PLAYER_STATE::IDLE;
		}

		break;

	default:
		break;
	}
}

// Called to bind functionality to input
void AMainCharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

	UEnhancedInputComponent* input = Cast< UEnhancedInputComponent>(PlayerInputComponent);
	if (nullptr != input)
	{
		input->BindAction(JumpAction, ETriggerEvent::Triggered, this, &AMainCharacter::Jump);

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

		if (eState != PLAYER_STATE::JUMP)
		{
			eState = PLAYER_STATE::WALK;
		}
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

	eState = PLAYER_STATE::JUMP;

	UE_LOG(LogTemp, Warning, TEXT("계속들어옴?"));
}