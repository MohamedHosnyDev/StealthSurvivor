// Fill out your copyright notice in the Description page of Project Settings.


#include "TriggerComponent.h"



UTriggerComponent :: UTriggerComponent ()
{
    PrimaryComponentTick.bCanEverTick = true;
} 


void UTriggerComponent :: TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
    Super :: TickComponent(DeltaTime , TickType , ThisTickFunction);

    FindTheKey();
    
    if(IsMoving)
    {
        MoveTheDoor();
    }

} 


void UTriggerComponent :: FindTheKey()
{
    TArray<AActor *>  OverLappingActors;
    bool OnlyTheKey = false;
    GetOverlappingActors(OverLappingActors);
    if(OverLappingActors.Num() == 0)
    {return ;}
    for(AActor * Actor : OverLappingActors)
    {
        if(Actor->ActorHasTag("Key"))
        {
            OnlyTheKey = true;
            
        }
        else
        {
            OnlyTheKey = false ;
        }
        
    }

    IsMoving = OnlyTheKey ;
    
}

void UTriggerComponent :: MoveTheDoor()
{
    CurrentLocation = GetOwner()->GetActorLocation();
    GetOwner()->SetActorLocation(CurrentLocation - FVector(0,0,1));
}

