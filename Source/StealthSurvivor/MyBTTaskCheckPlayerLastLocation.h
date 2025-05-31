// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BehaviorTree/Tasks/BTTask_BlackboardBase.h"
#include "NormalEnemy.h"
#include "AIController.h"
#include "SurvivorCharacter.h"
#include "MyBTTaskCheckPlayerLastLocation.generated.h"

/**
 * 
 */
UCLASS()
//I am sorry , when i was naming this task i forgot to delete "My" from the name
class STEALTHSURVIVOR_API UMyBTTaskCheckPlayerLastLocation : public UBTTask_BlackboardBase
{
	GENERATED_BODY()

	public:
		// IsUsed is the variable that helped me to replace the BeginPlay()
		bool IsUsed ;
		bool PlayerOnSight ;
		ASurvivorCharacter * Player ;
		ANormalEnemy * Enemy ;
		AAIController * AIController ;
		FHitResult HittedWall ;
		FVector PlayerLastLocation ;
		FVector EnemyMovingDistance ;
		FRotator EnemyMovingRotation ;
		FCollisionShape WallSphere ;

		UMyBTTaskCheckPlayerLastLocation();

		virtual EBTNodeResult::Type ExecuteTask(UBehaviorTreeComponent & OwnerComp , uint8 * NodeMemory) override ;
		// To check if the enemy see a wall infront of him
		bool SeeWalls(UBehaviorTreeComponent & OwnerComp);
	
};
