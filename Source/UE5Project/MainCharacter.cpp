// Fill out your copyright notice in the Description page of Project Settings.


#include "MainCharacter.h"
#include "InputActionValue.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "EnhancedInputComponent.h"
#include "EnhancedInputSubsystems.h"

// Sets default values
AMainCharacter::AMainCharacter()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	Tags.Add(TEXT("Player"));
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

	aniState = PLAYER_ANISTATE::IDLE;
}

// Called every frame
void AMainCharacter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	vel = GetVelocity();

	GetCharacterMovement()->MaxWalkSpeed;

	switch (aniState)
	{
	case PLAYER_ANISTATE::IDLE:
		break;
	case PLAYER_ANISTATE::WALK:
		if (vel.IsZero())
		{
			aniState = PLAYER_ANISTATE::IDLE;
			break;
		}
		GetCharacterMovement()->MaxWalkSpeed = fSpeed * (isDash + 1.f);
		break;
	case PLAYER_ANISTATE::DASH:
		if (vel.IsZero())
		{
			aniState = PLAYER_ANISTATE::IDLE;
			break;
		}
		GetCharacterMovement()->MaxWalkSpeed = fSpeed * (isDash + 1.f);
		break;
	case PLAYER_ANISTATE::JUMP:
		if (vel.IsZero())
		{
			aniState = PLAYER_ANISTATE::LAND;
		}
		break;
	case PLAYER_ANISTATE::LAND:
		break;
	case PLAYER_ANISTATE::ATTACK1:
		break;
	case PLAYER_ANISTATE::ATTACK2:
		break;
	case PLAYER_ANISTATE::ATTACK3:
		break;
	case PLAYER_ANISTATE::ATTACK4:
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
		input->BindAction(AttackAction, ETriggerEvent::Triggered, this, &AMainCharacter::Attack);
		input->BindAction(DashAction, ETriggerEvent::Triggered, this, &AMainCharacter::Dash);
	}
}

void AMainCharacter::Move(const FInputActionInstance& inst)
{
	if (aniState == PLAYER_ANISTATE::JUMP)
	{
		return;
	}

	FVector2D movementVector = inst.GetValue().Get<FVector2D>();

	if (nullptr != Controller)
	{
		const FRotator rotation    = Controller->GetControlRotation();
		const FRotator yawRotation = FRotator(0, rotation.Yaw, 0);
		const FVector  forward     = FRotationMatrix(yawRotation).GetUnitAxis(EAxis::X);
		const FVector  right       = FRotationMatrix(yawRotation).GetUnitAxis(EAxis::Y);

		AddMovementInput(forward, movementVector.Y);
		AddMovementInput(right,   movementVector.X);

		aniState = PLAYER_ANISTATE::WALK;
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

void AMainCharacter::Dash(const FInputActionInstance& inst)
{
	if (aniState == PLAYER_ANISTATE::JUMP)
	{
		return;
	}

	isDash = inst.GetValue().Get<float>();

	if (!vel.IsZero())
	{
		aniState = PLAYER_ANISTATE::DASH;
	}
}

void AMainCharacter::Attack()
{
	if (aniState == PLAYER_ANISTATE::ATTACK1)
	{
		aniState = PLAYER_ANISTATE::ATTACK2;
	}
	else if (aniState == PLAYER_ANISTATE::ATTACK2)
	{
		aniState = PLAYER_ANISTATE::ATTACK3;
	}
	else if (aniState == PLAYER_ANISTATE::ATTACK3)
	{
		aniState = PLAYER_ANISTATE::ATTACK4;
	}
	else
	{ 
		aniState = PLAYER_ANISTATE::ATTACK1;
	}
}
