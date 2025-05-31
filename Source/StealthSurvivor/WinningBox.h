// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/BoxComponent.h"
#include "SurvivorCharacterController.h"
#include "WinningBox.generated.h"

/**
 * 
 */
UCLASS(ClassGroup = (Custom) , meta = (BlueprintSpawnableComponent))
class STEALTHSURVIVOR_API UWinningBox : public UBoxComponent
{
	GENERATED_BODY()

	public:
		//The player controller is used to call GameHasEnded()
		ASurvivorCharacterController * PlayerController ;
		TArray<AActor *> OverLappingActors ;

		UWinningBox();

		virtual void BeginPlay() override ;
		virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)override ;
	
};
