// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "AttributeSet.h"
#include "AbilitySystemComponent.h"
#include "RougeAttributeSet.h"
#include "BaseAttributeSet.generated.h"

#define ATTRIBUTE_ACCESSORS(ClassName, PropertyName) \
GAMEPLAYATTRIBUTE_PROPERTY_GETTER(ClassName, PropertyName) \
GAMEPLAYATTRIBUTE_VALUE_GETTER(PropertyName) \
GAMEPLAYATTRIBUTE_VALUE_SETTER(PropertyName) \
GAMEPLAYATTRIBUTE_VALUE_INITTER(PropertyName)
/**
 * 
 */
UCLASS()
class GASROUGE_API UBaseAttributeSet : public URougeAttributeSet
{
	GENERATED_BODY()

private:
public:
	//攻击
	UPROPERTY(BlueprintReadOnly,Category=Attribute)
	FGameplayAttributeData Attack;
	ATTRIBUTE_ACCESSORS(UBaseAttributeSet, Attack);
	
	//防御
	UPROPERTY(BlueprintReadOnly,Category=Attribute)
	FGameplayAttributeData Defense;
	ATTRIBUTE_ACCESSORS(UBaseAttributeSet, Defense);

	//暴击率
	UPROPERTY(BlueprintReadOnly,Category=Attribute)
	FGameplayAttributeData CriticalChance;
	ATTRIBUTE_ACCESSORS(UBaseAttributeSet, CriticalChance);

	//暴击伤害
	UPROPERTY(BlueprintReadOnly,Category=Attribute)
	FGameplayAttributeData CriticalRate;
	ATTRIBUTE_ACCESSORS(UBaseAttributeSet, CriticalRate);

	//速度
	UPROPERTY(BlueprintReadWrite,Category=Attribute)
	FGameplayAttributeData Speed;
	ATTRIBUTE_ACCESSORS(UBaseAttributeSet, Speed);

	//最大速度
	UPROPERTY(BlueprintReadWrite,Category=Attribute)
	FGameplayAttributeData MaxSpeed;
	ATTRIBUTE_ACCESSORS(UBaseAttributeSet, MaxSpeed);
};
