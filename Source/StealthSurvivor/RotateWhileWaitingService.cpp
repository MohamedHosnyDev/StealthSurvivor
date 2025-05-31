// Fill out your copyright notice in the Description page of Project Settings.


#include "RotateWhileWaitingService.h"
#include "Kismet/GameplayStatics.h"
#include "AIController.h"


URotateWhileWaitingService::URotateWhileWaitingService()
{
    NodeName = "RotateWhileWaiting" ;
    IsUsed = false ;
}

void URotateWhileWaitingService::TickNode(UBehaviorTreeComponent & OwnerComp , uint8 * NodeMemory , float DeltaTime)
{
    Super::TickNode(OwnerComp , NodeMemory , DeltaTime);

    if(!IsUsed)
    {
        Player = UGameplayStatics::GetPlayerPawn(GetWorld(),0) ;
        Enemy = OwnerComp.GetAIOwner()->GetPawn();
        IsUsed = true ;
    }

    EnemyRotator = (Player->GetActorLocation() - Enemy->GetActorLocation()).Rotation() ;
    Enemy -> SetActorRotation(EnemyRotator) ;
}