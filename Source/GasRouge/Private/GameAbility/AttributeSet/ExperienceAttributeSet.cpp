// Fill out your copyright notice in the Description page of Project Settings.


#include "GameAbility/AttributeSet/ExperienceAttributeSet.h"

#include "GameplayEffectExtension.h"
#include "RougeType.h"
#include "Kismet/DataTableFunctionLibrary.h"
#include "Kismet/KismetSystemLibrary.h"

void UExperienceAttributeSet::PostGameplayEffectExecute(const FGameplayEffectModCallbackData& Data)
{
	Super::PostGameplayEffectExecute(Data);

	if(Data.EvaluatedData.Attribute==GetGainExperienceAttribute())
	{
		float OldGainExperience=GetGainExperience();
		OldGainExperience*=GetExperienceRate();
		float OldExperience=GetCurrExperience()+OldGainExperience;
		float OldNeedExperience=GetNeedExperience();
		float OldLevel=GetLevel();
		
		while(OldExperience>=OldNeedExperience)
		{
			OldExperience=OldExperience-OldNeedExperience;
			SetCurrExperience(OldExperience);
			if(TableNum==-1)
			{
				UDataTableFunctionLibrary::GetDataTableRowNames(ExperienceTable,TableRowName);
				TableNum=TableRowName.Num();
			}

			if(OldLevel<TableNum)
			{
				FExperienceTable* NewExperience=ExperienceTable->FindRow<FExperienceTable>(TableRowName[OldLevel],TEXT("Experience"),true);
				SetNeedExperience(NewExperience->Experience);
			}
			SetLevel(OldLevel+1);
			OldExperience=GetCurrExperience();
			OldNeedExperience=GetNeedExperience();
			UKismetSystemLibrary::PrintString(GetWorld(),"Up");
		}
		SetGainExperience(0.f);
	}
}
