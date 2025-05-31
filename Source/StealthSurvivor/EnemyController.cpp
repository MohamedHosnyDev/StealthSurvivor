// Fill out your copyright notice in the Description page of Project Settings.


#include "EnemyController.h"
#include "BehaviorTree/BlackBoardComponent.h"



AEnemyController::AEnemyController()
{
    PrimaryActorTick.bCanEverTick = true ;
    IsUsed = false ;

} 


void AEnemyController:: Tick(float DeltaTime)
{
    Super::Tick(DeltaTime);
    
    if(!IsUsed)
    {
        Enemy = Cast<ANormalEnemy>(GetPawn());
        if(Enemy -> BehaviorTree)
        {
            RunBehaviorTree(Enemy -> BehaviorTree);
            StartLocation = GetPawn()->GetActorLocation();
            StartRotation = GetPawn()->GetActorRotation();
            GetBlackboardComponent()->SetValueAsVector(TEXT("StartLocation"),StartLocation);
            GetBlackboardComponent()->SetValueAsRotator(TEXT("StartRotation"),StartRotation);
            GetBlackboardComponent()->ClearValue(TEXT("PlayerLastSeenLocation"));
        }

        IsUsed = true ;
    }
    if(Enemy -> BehaviorTree)
    {
        IsDamagedOrWasOnSight = Enemy -> IsDamaged || GetBlackboardComponent()->GetValueAsBool(TEXT("PlayerWasOnSight")) ;
        GetBlackboardComponent() -> SetValueAsBool(TEXT("IsDamagedOrWasOnSight"),IsDamagedOrWasOnSight) ; 
        GetBlackboardComponent()->SetValueAsBool(TEXT("IsDead"),Enemy->IsDead() && Enemy->IsStalker);
    }
   
}


FVector AEnemyController::GetStartLocation()
{
    if(Enemy -> BehaviorTree)
    {
        return GetBlackboardComponent() -> GetValueAsVector(TEXT("StartLocation"));
    }
    return FVector(0,0,0);
}