// Copyright Manuel Munoz

#pragma once

#include "CoreMinimal.h"
#include "Character/AuraCharacterBase.h"
#include "AuraPlayerCharacter.generated.h"

class AAuraPlayerState;

/**
 * 
 */
UCLASS()
class AURA_API AAuraPlayerCharacter : public AAuraCharacterBase
{
	GENERATED_BODY()
	
public:
	AAuraPlayerCharacter();

	virtual void PossessedBy(AController* controller) override;
	virtual void OnRep_PlayerState() override;

	void InitializeAbilityActorInfo();
	void InitializeHUD();
};
