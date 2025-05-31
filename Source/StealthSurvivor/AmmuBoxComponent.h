// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/BoxComponent.h"
#include "SurvivorCharacter.h"
#include "AmmuBoxComponent.generated.h"

/**
 * 
 */
UCLASS(ClassGroup=(Custom), meta=(BlueprintSpawnableComponent))
class STEALTHSURVIVOR_API UAmmuBoxComponent : public UBoxComponent
{
	GENERATED_BODY()

	public :
		int ExtraAmmu = 10 ;
		ASurvivorCharacter * SurvivorCharacter ;

		UAmmuBoxComponent();
		
		void AddAmmu();
		virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)override ;

};
