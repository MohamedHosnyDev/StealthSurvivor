// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BehaviorTree/Services/BTService_BlackboardBase.h"
#include "RotateWhileWaitingService.generated.h"

/**
 * 
 */
UCLASS()
class STEALTHSURVIVOR_API URotateWhileWaitingService : public UBTService_BlackboardBase
{
	GENERATED_BODY()

	public:
		APawn * Player ;
		APawn * Enemy ;
		FRotator EnemyRotator ;
		// IsUsed is the variable that helped me to replace the BeginPlay()
		bool IsUsed ;

		URotateWhileWaitingService() ;
		virtual void TickNode(UBehaviorTreeComponent & OwnerComp , uint8 * NodeMemory , float DeltaTime) override ;

	
};
