// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameAbility/AttributeSet/RougeAttributeSet.h"
#include "AbilitySystemComponent.h"
#include "ExperienceAttributeSet.generated.h"

#define ATTRIBUTE_ACCESSORS(ClassName, PropertyName) \
GAMEPLAYATTRIBUTE_PROPERTY_GETTER(ClassName, PropertyName) \
GAMEPLAYATTRIBUTE_VALUE_GETTER(PropertyName) \
GAMEPLAYATTRIBUTE_VALUE_SETTER(PropertyName) \
GAMEPLAYATTRIBUTE_VALUE_INITTER(PropertyName)
/**
 * 
 */
UCLASS()
class GASROUGE_API UExperienceAttributeSet : public URougeAttributeSet
{
	GENERATED_BODY()
	
protected:
	UPROPERTY(BlueprintReadOnly,EditDefaultsOnly)
	UDataTable* ExperienceTable;

	int32 TableNum=-1;

	TArray<FName> TableRowName;

public:

	//等级
	UPROPERTY(BlueprintReadOnly,Category=Attribute)
	FGameplayAttributeData Level;
	ATTRIBUTE_ACCESSORS(UExperienceAttributeSet, Level);
	
	//当前经验值
	UPROPERTY(BlueprintReadOnly,Category=Attribute)
	FGameplayAttributeData CurrExperience;
	ATTRIBUTE_ACCESSORS(UExperienceAttributeSet, CurrExperience);

	//升级所需经验
	UPROPERTY(BlueprintReadOnly,Category=Attribute)
	FGameplayAttributeData NeedExperience;
	ATTRIBUTE_ACCESSORS(UExperienceAttributeSet, NeedExperience);

	//经验倍率
	UPROPERTY(BlueprintReadOnly,Category=Attribute)
	FGameplayAttributeData ExperienceRate;
	ATTRIBUTE_ACCESSORS(UExperienceAttributeSet, ExperienceRate);

	UPROPERTY(BlueprintReadOnly,Category=Attribute)
	FGameplayAttributeData GainExperience;
	ATTRIBUTE_ACCESSORS(UExperienceAttributeSet, GainExperience);

	virtual void PostGameplayEffectExecute(const FGameplayEffectModCallbackData& Data) override;
};
