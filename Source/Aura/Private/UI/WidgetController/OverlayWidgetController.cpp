// Copyright Manuel Munoz


#include "UI/WidgetController/OverlayWidgetController.h"

#include "AbilitySystem/AuraAttributeSet.h"

void UOverlayWidgetController::BroadcastInitialValues()
{
	const UAuraAttributeSet* AuraSet = CastChecked<UAuraAttributeSet>(AttributeSet);

	OnHealthChanged.Broadcast(AuraSet->GetHealth());
	OnMaxMaxHealthChanged.Broadcast(AuraSet->GetMaxHealth());

	OnManaChanged.Broadcast(AuraSet->GetMana());
	OnMaxManaChanged.Broadcast(AuraSet->GetMaxMana());
}

void UOverlayWidgetController::BindCallbacksToDependencies()
{
	const UAuraAttributeSet* auraSet = CastChecked<UAuraAttributeSet>(AttributeSet);

	AbilitySystem->GetGameplayAttributeValueChangeDelegate(
		auraSet->GetHealthAttribute()).AddUObject(
			this, &UOverlayWidgetController::HealthChanged);

	AbilitySystem->GetGameplayAttributeValueChangeDelegate(
		auraSet->GetMaxHealthAttribute()).AddUObject(
			this, &UOverlayWidgetController::MaxHealthChanged);
}

void UOverlayWidgetController::HealthChanged(const FOnAttributeChangeData& Data) const
{
	OnHealthChanged.Broadcast(Data.NewValue);
}

void UOverlayWidgetController::MaxHealthChanged(const FOnAttributeChangeData& Data) const
{
	OnMaxMaxHealthChanged.Broadcast(Data.NewValue);
}
