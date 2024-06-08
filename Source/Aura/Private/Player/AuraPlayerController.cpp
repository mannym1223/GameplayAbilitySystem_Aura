// Copyright Manuel Munoz


#include "Player/AuraPlayerController.h"
#include <EnhancedInputSubsystems.h>

AAuraPlayerController::AAuraPlayerController()
{
	bReplicates = true;
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
