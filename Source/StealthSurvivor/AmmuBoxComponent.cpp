// Fill out your copyright notice in the Description page of Project Settings.


#include "AmmuBoxComponent.h"
#include "SurvivorCharacter.h"
#include "Kismet/GameplayStatics.h"


UAmmuBoxComponent :: UAmmuBoxComponent()
{
    PrimaryComponentTick.bCanEverTick = true;
}

void UAmmuBoxComponent:: TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
    Super :: TickComponent( DeltaTime,  TickType, ThisTickFunction);
    
    if(GetOwner())
    {
        TArray<AActor*> OverlappingActors ;
        GetOverlappingActors(OverlappingActors);
        if(OverlappingActors.Num() == 0)
        {return;}

        for(AActor * Actor : OverlappingActors)
        {
           
            if(Actor->ActorHasTag("Player"))
            {
                AddAmmu();
                GetOwner()->Destroy();
            }
        }
    }
    
}

void UAmmuBoxComponent :: AddAmmu()
{
    SurvivorCharacter = Cast<ASurvivorCharacter>(UGameplayStatics::GetPlayerPawn(GetWorld(),0));
    SurvivorCharacter -> PlayerAmmu += ExtraAmmu ;
}