// Fill out your copyright notice in the Description page of Project Settings.


#include "BTTaskReturnToStartLocation.h"
#include "Kismet/GameplayStatics.h"
#include "AIController.h"
#include "BehaviorTree/BlackboardComponent.h"



UBTTaskReturnToStartLocation :: UBTTaskReturnToStartLocation()
{
    NodeName = "ReturnToStartLocation" ;
    IsUsed = false ;
}

EBTNodeResult::Type UBTTaskReturnToStartLocation :: ExecuteTask(UBehaviorTreeComponent & OwnerComp , uint8 * NodeMemory)
{
    Super :: ExecuteTask(OwnerComp , NodeMemory) ;

    if(!IsUsed)
    {
        StartLocation = OwnerComp.GetAIOwner()->GetBlackboardComponent()->GetValueAsVector(GetSelectedBlackboardKey());
        Enemy = Cast<ANormalEnemy>(OwnerComp.GetAIOwner()->GetPawn());
        if(Enemy == nullptr)
        {   return EBTNodeResult::Failed ;}
        
        Enemy -> SetActorRotation(EnemyMovingRotation);
        StartRotation = OwnerComp.GetAIOwner()->GetBlackboardComponent()->GetValueAsRotator(TEXT("StartRotation"));
        IsUsed = true ;
    }

    
    if(FVector :: Dist(Enemy->GetActorLocation() , StartLocation) > 30)
    {
        EnemyMovingRotation = FRotator(0, (StartLocation - Enemy->GetActorLocation()).Rotation().Yaw ,0);
        Enemy -> SetActorRotation(EnemyMovingRotation);
        EnemyMovingDistance = Enemy->GetActorForwardVector()*500*(UGameplayStatics::GetWorldDeltaSeconds(GetWorld())) ;
        Enemy -> SetActorLocation(Enemy->GetActorLocation() + EnemyMovingDistance);
    }
    else
    {
        Enemy -> SetActorLocation(StartLocation);
        Enemy -> SetActorRotation(StartRotation);
        OwnerComp.GetAIOwner()->GetBlackboardComponent()->SetValueAsBool(TEXT("Restart"),true);
        OwnerComp.GetAIOwner()->GetBlackboardComponent()->ClearValue(TEXT("ReturnToStartLocation"));
        IsUsed = false ;
    }

    return EBTNodeResult::Succeeded ;
}
