// Fill out your copyright notice in the Description page of Project Settings.

#include "BTTaskShootPlayer.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "Kismet/GameplayStatics.h"



UBTTaskShootPlayer::UBTTaskShootPlayer()
{
    NodeName = "ShootPlayer" ;
    IsUsed = false ;
}

EBTNodeResult::Type UBTTaskShootPlayer::ExecuteTask(UBehaviorTreeComponent & OwnerComp , uint8 * NodeMemory)
{
    Super::ExecuteTask(OwnerComp , NodeMemory) ;

    if(!IsUsed)
    {
        Enemy = Cast<ANormalEnemy>(OwnerComp.GetAIOwner()->GetPawn());
        Player = Cast<ASurvivorCharacter>(UGameplayStatics::GetPlayerPawn(GetWorld() , 0));
        IsUsed = true ;
    }

    if(Enemy)
    {
        Enemy -> Shoot();
    }

    if(Enemy && Player)
    {
        if(FVector::Dist(Enemy->GetActorLocation() , Player->GetActorLocation() ) >= 200)
        {
            OwnerComp.GetAIOwner()->GetBlackboardComponent()->ClearValue(TEXT("Reached"));
            Enemy -> IsMoving = true ;
        }
    }

    return EBTNodeResult::Succeeded ;
}