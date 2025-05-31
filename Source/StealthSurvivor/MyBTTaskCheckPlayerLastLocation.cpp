// Fill out your copyright notice in the Description page of Project Settings.


#include "MyBTTaskCheckPlayerLastLocation.h"
#include "Kismet/GameplayStatics.h"
#include "BehaviorTree/BlackboardComponent.h"



UMyBTTaskCheckPlayerLastLocation :: UMyBTTaskCheckPlayerLastLocation()
{
    NodeName = "CheckPlayerLastLocationOrShootLocation" ;
    WallSphere = FCollisionShape::MakeSphere(100);
    IsUsed = false ;
}

EBTNodeResult::Type UMyBTTaskCheckPlayerLastLocation :: ExecuteTask(UBehaviorTreeComponent & OwnerComp , uint8 * NodeMemory)
{
    Super :: ExecuteTask(OwnerComp , NodeMemory) ;

    if(!IsUsed)
    {
        Player = Cast<ASurvivorCharacter>(UGameplayStatics::GetPlayerPawn(GetWorld(),0)) ;
        Enemy = Cast<ANormalEnemy>(OwnerComp.GetAIOwner()->GetPawn());
        AIController = OwnerComp.GetAIOwner();
        if(Enemy == nullptr)
        {   return EBTNodeResult::Failed ;}
    
        PlayerLastLocation = (Player->GetActorLocation() + Enemy->GetActorRotation().Vector());
        IsUsed = true ;
    }

    
    if(FVector :: Dist(Enemy->GetActorLocation() , PlayerLastLocation) > 30 && !SeeWalls(OwnerComp))
    {
        EnemyMovingRotation = (PlayerLastLocation - Enemy -> GetActorLocation()).Rotation() ;
        Enemy -> SetActorRotation(FRotator(0,EnemyMovingRotation.Yaw,0));
        EnemyMovingDistance = Enemy->GetActorForwardVector()*500*(UGameplayStatics::GetWorldDeltaSeconds(GetWorld())) ;
        Enemy -> SetActorLocation(Enemy->GetActorLocation() + EnemyMovingDistance);
    }
    else
    {
        OwnerComp.GetAIOwner()->GetBlackboardComponent()->ClearValue(GetSelectedBlackboardKey());
        Enemy -> IsDamaged = false ;
        OwnerComp.GetAIOwner()->GetBlackboardComponent() -> ClearValue(TEXT("IsDamagedOrWasOnSight")) ;
        OwnerComp.GetAIOwner()->GetBlackboardComponent()->SetValueAsBool(TEXT("ReturnToStartLocation"),true);
        IsUsed = false ;
    }

    return EBTNodeResult::Succeeded ;
}

bool UMyBTTaskCheckPlayerLastLocation:: SeeWalls(UBehaviorTreeComponent & OwnerComp)
{   
    return OwnerComp.GetAIOwner() -> GetPawn()->GetWorld()->SweepSingleByChannel(HittedWall,OwnerComp.GetAIOwner()-> GetPawn()->GetActorLocation(),(OwnerComp.GetAIOwner()-> GetPawn()->GetActorLocation() + OwnerComp.GetAIOwner()-> GetPawn()->GetActorRotation().Vector()*100),FQuat::Identity,ECollisionChannel::ECC_GameTraceChannel4 ,WallSphere);
}