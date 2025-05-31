// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BehaviorTree/Services/BTService_BlackboardBase.h"
#include "AIController.h"
#include "SurvivorCharacter.h"
#include "BTServicePlayerOnSight.generated.h"

/**
 * 
 */
UCLASS()
class STEALTHSURVIVOR_API UBTServicePlayerOnSight : public UBTService_BlackboardBase
{
	GENERATED_BODY()

	public:
		FHitResult HittedPlayer ;
		FHitResult HittedWall ;
		FCollisionShape SightSphere ;
		FCollisionShape WallSphere ;
		UPROPERTY(EditAnywhere)
		USoundBase * SightSound ;
		AAIController * AIController ;

		UBTServicePlayerOnSight();
		bool OnSight(APawn * Pawn);

	protected:

		virtual void TickNode(UBehaviorTreeComponent & OwnerComp , uint8 * NodeMemory , float DeltaTime) override ;
		// To check if the enemy see a wall infront of him
		bool SeeWalls(UBehaviorTreeComponent & OwnerComp);
	
};
