// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "NormalEnemy.h"
#include "AIController.h"
#include "BehaviorTree/BehaviorTree.h"
#include "TimerManager.h"
#include "EnemyController.generated.h"

/**
 * 
 */
UCLASS()
class STEALTHSURVIVOR_API AEnemyController : public AAIController
{
	GENERATED_BODY()

	public:
		ANormalEnemy * Enemy ;
		FVector StartLocation ;
		FRotator StartRotation;
		//will be used to activate a BTTask
		bool IsDamagedOrWasOnSight ;
		// IsUsed will be used in the Tick instead of BeginPlay because when we spawn AI in the world in the game mode BeginPlay it crash
		bool IsUsed ;
		
		AEnemyController();

		virtual void Tick(float DeltaTime)override ;
		//Used in the moving right and left BTTask
		FVector GetStartLocation();

	
};
