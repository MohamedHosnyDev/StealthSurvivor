// Fill out your copyright notice in the Description page of Project Settings.


#include "BTTaskFollowPlayer.h"
#include "Kismet/GameplayStatics.h"
#include "BehaviorTree/BlackboardComponent.h"



UBTTaskFollowPlayer::UBTTaskFollowPlayer()
{
    NodeName = "FollowPlayer" ;
    IsUsed = false ;
    
}

EBTNodeResult::Type UBTTaskFollowPlayer::ExecuteTask(UBehaviorTreeComponent & OwnerComp , uint8 * NodeMemory)
{
    Super::ExecuteTask(OwnerComp , NodeMemory) ;

    if(!IsUsed)
    {
        Enemy = Cast<ANormalEnemy>(OwnerComp.GetAIOwner()->GetPawn());
        Player = Cast<ASurvivorCharacter>(UGameplayStatics::GetPlayerPawn(GetWorld(),0));
        IsUsed = true ;
    }

    PlayerOnSight = OwnerComp.GetAIOwner() -> GetBlackboardComponent()->GetValueAsBool(TEXT("PlayerOnSight"));

    if(PlayerOnSight)
    {

        EnemyRotation = FRotator(0,(Player->GetActorLocation() - Enemy->GetActorLocation()).Rotation().Yaw,0);
        EnemyMovingDistance = Enemy->GetActorForwardVector()*600*(UGameplayStatics::GetWorldDeltaSeconds(GetWorld())) ;
        Enemy -> SetActorRotation(EnemyRotation);

        // so that if the player is not on sight and he did not shoot the enemy the CheckShootLocation won`t be actived 
        if(Enemy -> IsDamaged)
        {
            Enemy -> IsDamaged = false ;
        }

        if((FVector::Dist(Enemy -> GetActorLocation() , Player -> GetActorLocation()) < 400))
        {
            OwnerComp.GetAIOwner() -> GetBlackboardComponent()->SetValueAsBool(TEXT("Reached"),true);
            Enemy -> IsMoving = false ;
            return EBTNodeResult::Succeeded;
        }

        Enemy -> SetActorLocation(Enemy -> GetActorLocation() + EnemyMovingDistance);
        OwnerComp.GetAIOwner() -> GetBlackboardComponent()->ClearValue(TEXT("Reached"));
        OwnerComp.GetAIOwner() -> GetBlackboardComponent()->SetValueAsBool(TEXT("PlayerWasOnSight"),true);
        

    }


    return EBTNodeResult::Succeeded ;
}


