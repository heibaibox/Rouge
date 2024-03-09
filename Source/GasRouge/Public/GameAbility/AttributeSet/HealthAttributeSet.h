// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "AttributeSet.h"
#include "AbilitySystemComponent.h"
#include "RougeAttributeSet.h"
#include "HealthAttributeSet.generated.h"
/**
 * 
 */

#define ATTRIBUTE_ACCESSORS(ClassName, PropertyName) \
GAMEPLAYATTRIBUTE_PROPERTY_GETTER(ClassName, PropertyName) \
GAMEPLAYATTRIBUTE_VALUE_GETTER(PropertyName) \
GAMEPLAYATTRIBUTE_VALUE_SETTER(PropertyName) \
GAMEPLAYATTRIBUTE_VALUE_INITTER(PropertyName)

UCLASS()
class GASROUGE_API UHealthAttributeSet : public URougeAttributeSet
{
	GENERATED_BODY()

public:
	//生命
	UPROPERTY(BlueprintReadOnly,Category=Attribute)
	FGameplayAttributeData Health;
	ATTRIBUTE_ACCESSORS(UHealthAttributeSet, Health);
	
	//最大生命
	UPROPERTY(BlueprintReadOnly,Category=Attribute)
	FGameplayAttributeData MaxHealth;
	ATTRIBUTE_ACCESSORS(UHealthAttributeSet, MaxHealth);

	//护盾
	UPROPERTY(BlueprintReadOnly,Category=Attribute)
	FGameplayAttributeData Shield;
	ATTRIBUTE_ACCESSORS(UHealthAttributeSet, Shield);

	//最大护盾
	UPROPERTY(BlueprintReadOnly,Category=Attribute)
	FGameplayAttributeData MaxShield;
	ATTRIBUTE_ACCESSORS(UHealthAttributeSet, MaxShield);

	//最终伤害
	UPROPERTY(BlueprintReadOnly,Category=Attribute)
	FGameplayAttributeData FinalDamage;
	ATTRIBUTE_ACCESSORS(UHealthAttributeSet, FinalDamage);

	virtual void PostGameplayEffectExecute(const FGameplayEffectModCallbackData& Data) override;
};
