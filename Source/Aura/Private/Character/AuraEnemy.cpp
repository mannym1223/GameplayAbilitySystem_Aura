// Copyright Manuel Munoz


#include "Character/AuraEnemy.h"

void AAuraEnemy::HighlightActor()
{
	bIsHighlighted = true;
	UE_LOG(LogTemp, Warning, TEXT("Highlighting Actor"));
}

void AAuraEnemy::UnhighlightActor()
{
	bIsHighlighted = false;
	UE_LOG(LogTemp, Warning, TEXT("Un-Highlighting Actor"));
}

