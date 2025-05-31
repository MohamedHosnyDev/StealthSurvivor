// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/BoxComponent.h"
#include "TriggerComponent.generated.h"

/**
 * 
 */
UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class STEALTHSURVIVOR_API UTriggerComponent : public UBoxComponent
{
	GENERATED_BODY()


	public :
		UTriggerComponent();

		//This is the speed used of moving the door , the door current location and target location
		int MoveSpeed = 30 ;
		FVector CurrentLocation ;
		FVector TargetLocation ;
		bool IsMoving = false ;

		virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)override ;

		//This function check if the key is placed in the door
		void FindTheKey();
		void MoveTheDoor();



	
};


