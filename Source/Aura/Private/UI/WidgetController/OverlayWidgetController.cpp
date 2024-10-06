// Copyright Manuel Munoz


#include "UI/WidgetController/OverlayWidgetController.h"

#include "AbilitySystem/AuraAttributeSet.h"

void UOverlayWidgetController::BroadcastInitialValues()
{
	const UAuraAttributeSet* auraSet = CastChecked<UAuraAttributeSet>(AttributeSet);

	OnHealthChanged.Broadcast(auraSet->GetHealth());
	OnMaxMaxHealthChanged.Broadcast(auraSet->GetMaxHealth());
}
