// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BehaviorTree/Tasks/BTTask_BlackboardBase.h"
#include "NormalEnemy.h"
#include "SurvivorCharacter.h"
#include "AIController.h"
#include "BTTaskFollowPlayer.generated.h"

/**
 * 
 */
UCLASS()
class STEALTHSURVIVOR_API UBTTaskFollowPlayer : public UBTTask_BlackboardBase
{
	GENERATED_BODY()

	public:
		FVector PlayerLocation ;
		FVector PlayerLastLocation ;
		FVector EnemyMovingDistance ;
		FRotator EnemyRotation ;
		FHitResult HittedWall ;
		ANormalEnemy * Enemy ;
		ASurvivorCharacter * Player ;
		// IsUsed is the variable that helped me to replace the BeginPlay()
		bool IsUsed ;
		bool PlayerOnSight;

		UBTTaskFollowPlayer();

		virtual EBTNodeResult::Type ExecuteTask(UBehaviorTreeComponent & OwnerComp , uint8 * NodeMemory)override;
	
};
