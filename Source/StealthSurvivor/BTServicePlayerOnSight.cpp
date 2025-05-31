// Fill out your copyright notice in the Description page of Project Settings.


#include "BTServicePlayerOnSight.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "DrawDebugHelpers.h"
#include "Kismet/GameplayStatics.h"


UBTServicePlayerOnSight::UBTServicePlayerOnSight()
{
    NodeName = "PlayerOnSightService" ;
    SightSphere = FCollisionShape::MakeSphere(400);
    WallSphere = FCollisionShape::MakeSphere(100) ;

}

void UBTServicePlayerOnSight::TickNode(UBehaviorTreeComponent & OwnerComp , uint8 * NodeMemory , float DeltaTime)
{
    Super::TickNode(OwnerComp , NodeMemory , DeltaTime) ;
    
    AIController = OwnerComp.GetAIOwner();
    if(OnSight(AIController->GetPawn()) && !SeeWalls(OwnerComp))
    {
        if(SightSound && AIController->GetBlackboardComponent()->GetValueAsBool(TEXT("PlayerOnSight")) != true && AIController->GetBlackboardComponent()->GetValueAsBool(TEXT("IsDead")) != true)
        {
            UGameplayStatics::PlaySoundAtLocation( this , SightSound , AIController->GetPawn()->GetActorLocation()) ;
        }
        AIController->GetBlackboardComponent()->SetValueAsBool(TEXT("PlayerOnSight"),true);
    }
    else 
    {
        AIController->GetBlackboardComponent()->ClearValue(TEXT("PlayerOnSight"));
    }
}

bool UBTServicePlayerOnSight::OnSight(APawn * Pawn)
{
    return Pawn->GetWorld()->SweepSingleByChannel(HittedPlayer,Pawn->GetActorLocation(),(Pawn->GetActorLocation() + Pawn->GetActorRotation().Vector()*1300),FQuat::Identity,ECollisionChannel::ECC_GameTraceChannel3 ,SightSphere);
}

bool UBTServicePlayerOnSight::SeeWalls(UBehaviorTreeComponent & OwnerComp)
{
    return OwnerComp.GetAIOwner() -> GetPawn()->GetWorld()->SweepSingleByChannel(HittedWall,OwnerComp.GetAIOwner()-> GetPawn()->GetActorLocation(),(OwnerComp.GetAIOwner()-> GetPawn()->GetActorLocation() + OwnerComp.GetAIOwner()-> GetPawn()->GetActorRotation().Vector()*100),FQuat::Identity,ECollisionChannel::ECC_GameTraceChannel4 ,WallSphere);
}