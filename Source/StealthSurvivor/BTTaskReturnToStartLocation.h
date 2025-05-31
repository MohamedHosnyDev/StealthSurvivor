// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BehaviorTree/Tasks/BTTask_BlackboardBase.h"
#include "NormalEnemy.h"
#include "BTTaskReturnToStartLocation.generated.h"

/**
 * 
 */
UCLASS()
class STEALTHSURVIVOR_API UBTTaskReturnToStartLocation : public UBTTask_BlackboardBase
{
	GENERATED_BODY()
	
	public:
		// IsUsed is the variable that helped me to replace the BeginPlay()
		bool IsUsed ;
		ANormalEnemy * Enemy ;
		FVector StartLocation ;
		FRotator StartRotation ;
		FVector EnemyMovingDistance ;
		FRotator EnemyMovingRotation ;

		UBTTaskReturnToStartLocation();
		virtual EBTNodeResult::Type ExecuteTask(UBehaviorTreeComponent & OwnerComp , uint8 * NodeMemory) override ;
	
};
