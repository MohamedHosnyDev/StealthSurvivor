// Fill out your copyright notice in the Description page of Project Settings.


#include "MovingRightLeftBTTask.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "AIController.h"
#include "BrainComponent.h"
#include "Kismet/GameplayStatics.h"



UMovingRightLeftBTTask::UMovingRightLeftBTTask()
{
    NodeName = "MovingRightLeft" ;
    MovingSpeed = 3 ;
    IsUsed = false ;
}

EBTNodeResult::Type UMovingRightLeftBTTask::ExecuteTask(UBehaviorTreeComponent & OwnerComp , uint8 * NodeMemory)
{
    Super::ExecuteTask(OwnerComp , NodeMemory) ;

    Restart = OwnerComp.GetAIOwner() -> GetBlackboardComponent() -> GetValueAsBool(TEXT("Restart"));
    DeltaSeconds = UGameplayStatics::GetWorldDeltaSeconds(GetWorld());

    if(Restart || !IsUsed)
    {
        EnemyController = Cast<AEnemyController>(OwnerComp.GetAIOwner());
        StartLocation = EnemyController -> GetStartLocation();
        CurrentLocation = StartLocation;
        IsUsed = true ;
        OwnerComp.GetAIOwner() -> GetBlackboardComponent() -> SetValueAsBool(TEXT("Restart"),false);

    }

    APawn *Enemy = OwnerComp.GetAIOwner()->GetPawn() ; 
    
    if(Enemy)
    {
        Roll = Enemy->GetActorRotation().Roll;
        Yaw = Enemy->GetActorRotation().Yaw;
        Pitch = Enemy->GetActorRotation().Pitch;
        MovingDistance = CurrentLocation + ((Enemy->GetActorForwardVector()*200)*DeltaSeconds) ;

        if(FVector::Dist(StartLocation,CurrentLocation) > 1500)
        {
            Yaw += 180;
            ChangeRotation = FRotator(Roll,Yaw,Pitch) ;
            Enemy->SetActorRotation(ChangeRotation);
            StartLocation = CurrentLocation;
        }

        Enemy->SetActorLocation(MovingDistance);
        CurrentLocation = MovingDistance;
        CurrentLocation = Enemy->GetActorLocation();
        return EBTNodeResult::Succeeded ;
    }

    return EBTNodeResult::Failed;
}

