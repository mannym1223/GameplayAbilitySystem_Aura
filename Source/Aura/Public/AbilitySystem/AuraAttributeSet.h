// Copyright Manuel Munoz

#pragma once

#include "CoreMinimal.h"
#include "AttributeSet.h"
#include "AuraAttributeSet.generated.h"

/**
 * 
 */
UCLASS()
class AURA_API UAuraAttributeSet : public UAttributeSet
{
	GENERATED_BODY()
	
public:
	UAuraAttributeSet();

	virtual void GetLifeTimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const;

	/* Attributes */
	UPROPERTY(BlueprintReadOnly, ReplicatedUsing = OnRep_Health, Category = "Attributes | Vital")
	FGameplayAttributeData Health;

	UPROPERTY(BlueprintReadOnly, ReplicatedUsing = OnRep_MaxHealth, Category = "Attributes | Vital")
	FGameplayAttributeData MaxHealth;

	UPROPERTY(BlueprintReadOnly, ReplicatedUsing = OnRep_Mana, Category = "Attributes | Combat")
	FGameplayAttributeData Mana;

	UPROPERTY(BlueprintReadOnly, ReplicatedUsing = OnRep_MaxMana, Category = "Attributes | Combat")
	FGameplayAttributeData MaxMana;
	/* Attributes */

	/* Replication functions*/
	UFUNCTION()
	void OnRep_Health(const FGameplayAttributeData& oldHealth) const;

	UFUNCTION()
	void OnRep_MaxHealth(const FGameplayAttributeData& oldMaxHealth) const;

	UFUNCTION()
	void OnRep_Mana(const FGameplayAttributeData& oldMana) const;

	UFUNCTION()
	void OnRep_MaxMana(const FGameplayAttributeData& oldMaxMana) const;
	/* Replication functions*/
};
