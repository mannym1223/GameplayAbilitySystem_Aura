// Copyright Manuel Munoz


#include "UI/HUD/AuraHUD.h"

#include "UI/WidgetController/OverlayWidgetController.h"

UOverlayWidgetController* AAuraHUD::GetOverlayWidgetController(const FWidgetControllerParams& WCParams)
{
	if(OverlayWidgetController == nullptr)
	{
		OverlayWidgetController = NewObject<UOverlayWidgetController>(this, OverlayWidgetControllerClass);
		OverlayWidgetController->SetWidgetControllerParams(WCParams);
		//return OverlayWidgetController;
	}
	return OverlayWidgetController;
}

void AAuraHUD::InitOverlay(APlayerController* PC, APlayerState* PS, UAbilitySystemComponent* ASC, UAttributeSet* AS)
{
	checkf(OverlayWidgetClass, TEXT("Overlay widget class not initialized. Please fill out BP_AuraHUD"));
	checkf(OverlayWidgetControllerClass, TEXT("Overlay widget controller class not initialized. Please fill out BP_AuraHUD"));
	
	UUserWidget* widget = CreateWidget<UUserWidget>(GetWorld(), OverlayWidgetClass);
	OverlayWidget = Cast<UAuraUserWidget>(widget);

	const FWidgetControllerParams widgetControllerParams(PC, PS, ASC, AS);
	UOverlayWidgetController* widgetController = GetOverlayWidgetController(widgetControllerParams);

	OverlayWidget->SetWidgetController(widgetController);
	widgetController->BroadcastInitialValues();
	widgetController->BindCallbacksToDependencies();
	widget->AddToViewport();
}
