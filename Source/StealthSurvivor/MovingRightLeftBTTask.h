// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
// #include "BehaviorTree/BTTaskNode.h"
#include "BehaviorTree/Tasks/BTTask_BlackboardBase.h"
#include "EnemyController.h"
#include "MovingRightLeftBTTask.generated.h"

/**
 * 
 */
UCLASS()
class STEALTHSURVIVOR_API UMovingRightLeftBTTask : public UBTTaskNode
{
	GENERATED_BODY()
	
	public:
		float Roll ;
		float Yaw ;
		float Pitch ;
		float DeltaSeconds ;
		int MovingSpeed ;
		// IsUsed is the variable that helped me to replace the BeginPlay()
		bool IsUsed ;
		bool Restart ;
		FVector MovingDistance ;
		FVector StartLocation ;
		FVector CurrentLocation ;
		FRotator ChangeRotation ;
		AEnemyController * EnemyController ;
		
		UMovingRightLeftBTTask();

		virtual EBTNodeResult::Type ExecuteTask(UBehaviorTreeComponent & OwnerComp , uint8 * NodeMemory)override;

	


};
