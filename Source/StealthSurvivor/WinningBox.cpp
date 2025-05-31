// Fill out your copyright notice in the Description page of Project Settings.


#include "WinningBox.h"
#include "Kismet/GameplayStatics.h"


UWinningBox::UWinningBox()
{
    PrimaryComponentTick.bCanEverTick = true ;
}

void UWinningBox::BeginPlay()
{
    Super::BeginPlay();

    PlayerController = Cast<ASurvivorCharacterController>(UGameplayStatics::GetPlayerController(GetWorld(),0));
}

void UWinningBox::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
    Super::TickComponent( DeltaTime, TickType, ThisTickFunction) ;

    GetOverlappingActors(OverLappingActors);
    for(AActor * Actor : OverLappingActors)
    {
        if(Actor -> ActorHasTag("Player"))
        {
            PlayerController -> GameHasEnded(UGameplayStatics::GetPlayerPawn(GetWorld(),0) , true);
        }
    }
}
