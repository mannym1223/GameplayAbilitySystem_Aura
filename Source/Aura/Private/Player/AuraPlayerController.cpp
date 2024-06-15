// Copyright Manuel Munoz


#include "Player/AuraPlayerController.h"
#include <EnhancedInputSubsystems.h>
#include <EnhancedInputComponent.h>
#include <Interaction/EnemyInterface.h>

AAuraPlayerController::AAuraPlayerController()
{
	bReplicates = true;
}

void AAuraPlayerController::PlayerTick(float DeltaTime)
{
	Super::PlayerTick(DeltaTime);

	CursorTrace();
}

void AAuraPlayerController::BeginPlay()
{
	Super::BeginPlay();

	//initialize input subsystem
	check(AuraContext);
	UEnhancedInputLocalPlayerSubsystem* subsystem = ULocalPlayer::GetSubsystem<UEnhancedInputLocalPlayerSubsystem>(GetLocalPlayer());
	check(subsystem);
	subsystem->AddMappingContext(AuraContext, 0);

	//cursor options
	bShowMouseCursor = true;
	DefaultMouseCursor = EMouseCursor::Default;

	//set input mode
	FInputModeGameAndUI inputModeData;
	inputModeData.SetLockMouseToViewportBehavior(EMouseLockMode::DoNotLock);
	inputModeData.SetHideCursorDuringCapture(false);
	SetInputMode(inputModeData);
}

void AAuraPlayerController::SetupInputComponent()
{
	Super::SetupInputComponent();

	UEnhancedInputComponent* enhancedInputComponent = CastChecked<UEnhancedInputComponent>(InputComponent);

	enhancedInputComponent->BindAction(MoveAction, ETriggerEvent::Triggered, this, &AAuraPlayerController::Move);
}

void AAuraPlayerController::Move(const FInputActionValue& inputActionValue)
{
	const FVector2D inputAxisVector = inputActionValue.Get<FVector2D>();
	const FRotator rotation = GetControlRotation();
	const FRotator yawRotation(0.f, rotation.Yaw, 0.f);

	const FVector forwardDirection = FRotationMatrix(yawRotation).GetUnitAxis(EAxis::X);
	const FVector rightDirection = FRotationMatrix(yawRotation).GetUnitAxis(EAxis::Y);

	if (APawn* controlledPawn = GetPawn<APawn>()) {
		controlledPawn->AddMovementInput(rightDirection, inputAxisVector.X);
		controlledPawn->AddMovementInput(forwardDirection, inputAxisVector.Y);
	}
}

void AAuraPlayerController::CursorTrace()
{
	FHitResult cursorHit;
	GetHitResultUnderCursor(ECC_Visibility, false, cursorHit);
	if (!cursorHit.bBlockingHit) return;

	LastActor = ThisActor;
	ThisActor = cursorHit.GetActor();

	/*
	* Line trace from cursor scenarios:
	* a. LastActor is null & ThisActor is null
	*	- Do nothing
	* b. LastActor is null & ThisActor is valid
	*	- Hovering for first time
	*	- Highlight ThisActor
	* c. LastActor is valid & ThisActor is null
	*	- No longer hovering
	*	- Unhighlight LastActor
	* d. Both actors valid, but LastActor != ThisActor
	*	- Hovering over different actor
	*	- Unhighlight LastActor and highlight ThisActor
	* e. Both actors valid and the same actor
	*	- Hovering same actor
	*	- Do nothing
	*/

	if (LastActor == nullptr) {
		if (ThisActor != nullptr) {
			// case b
			ThisActor->HighlightActor();
		}
		else {
			// case a - both null - do nothing
		}
	}
	else { // last actor valid
		if (ThisActor == nullptr) {
			// case c
			LastActor->UnhighlightActor();
		}
		else { // both valid
			if (LastActor != ThisActor) {
				// case d
				LastActor->UnhighlightActor();
				ThisActor->HighlightActor();
			}
			else {
				// case e - do nothing
			}
		}
	}
}
