// Copyright Manuel Munoz


#include "Character/AuraPlayerCharacter.h"
#include "Player/AuraPlayerState.h"
#include "GameFramework/CharacterMovementComponent.h"
#include <AbilitySystem/AuraAbilitySystemComponent.h>
#include <AbilitySystem/AuraAttributeSet.h>

#include "UI/HUD/AuraHUD.h"

AAuraPlayerCharacter::AAuraPlayerCharacter()
{
	GetCharacterMovement()->bOrientRotationToMovement = true;
	GetCharacterMovement()->RotationRate = FRotator(0.f, 400.f, 0.f);
	GetCharacterMovement()->bConstrainToPlane = true;
	GetCharacterMovement()->bSnapToPlaneAtStart = true;

	//dont use controller rotation
	bUseControllerRotationPitch = false;
	bUseControllerRotationRoll = false;
	bUseControllerRotationYaw = false;
}

void AAuraPlayerCharacter::PossessedBy(AController* controller)
{
	Super::PossessedBy(controller);

	//init ability actor info for server
	InitializeAbilityActorInfo();

	//init HUD
	InitializeHUD();
}

void AAuraPlayerCharacter::OnRep_PlayerState()
{
	Super::OnRep_PlayerState();

	//init ability actor info for client
	InitializeAbilityActorInfo();

	//init HUD
	InitializeHUD();
}

void AAuraPlayerCharacter::InitializeAbilityActorInfo()
{
	AAuraPlayerState* playerState = GetPlayerState<AAuraPlayerState>();
	check(playerState);
	playerState->GetAbilitySystemComponent()->InitAbilityActorInfo(playerState, this);
	AbilitySystemComponent = playerState->GetAbilitySystemComponent();
	AttributeSet = playerState->GetAttributeSet();
}

void AAuraPlayerCharacter::InitializeHUD()
{
	APlayerController* controller = GetController<APlayerController>();
	AAuraHUD* hud = Cast<AAuraHUD>((controller)->GetHUD());
	AAuraPlayerState* playerState = GetPlayerState<AAuraPlayerState>();
	
	hud->InitOverlay(controller, playerState, AbilitySystemComponent, AttributeSet);
}
