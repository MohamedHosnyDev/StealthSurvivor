// Fill out your copyright notice in the Description page of Project Settings.


#include "SurvivorCharacterController.h"
#include "SurvivorCharacter.h"
#include "Blueprint/UserWidget.h"
#include "Kismet/GameplayStatics.h"




ASurvivorCharacterController::ASurvivorCharacterController()
{
    PrimaryActorTick.bCanEverTick = true;
}

void ASurvivorCharacterController::BeginPlay()
{
    Super::BeginPlay();

    GameMode = GetWorld()->GetAuthGameMode<AStealthSurvivorMode>();
    GameEnded = false ;
    if(TheGameplayWidget)
    {
        GameplayWidget = CreateWidget(this,TheGameplayWidget);
        GameplayWidget -> AddToViewport();
    }

    Player = UGameplayStatics::GetPlayerPawn(GetWorld(),0) ;

}

void ASurvivorCharacterController::Tick(float DeltaTime)
{
    Super :: Tick(DeltaTime);
    
    // I wrote the line below in case that the player wanted to play again after going to the main menu
    if(Player && !GameEnded)
    {
        GameHasEnded(Player , false);
    }
    
}

void ASurvivorCharacterController :: GameHasEnded(class AActor * EndGameFocus , bool bIsWinner )
{
    Super :: GameHasEnded(EndGameFocus ,bIsWinner) ;

    ASurvivorCharacter * Survivor = Cast<ASurvivorCharacter>(EndGameFocus);

    if(!bIsWinner && (Survivor->PlayerCurrentHealth) > 0)
    {return;}

    if(TheGameplayWidget)
    {
        GameplayWidget -> RemoveFromParent();
    }
    
    if(bIsWinner)
    {
        GameEnded = true ;
        GameMode->PlayWinWidget();
    }
    else
    {
        GameEnded = true ;
        GameMode->PlayLossWidget();
    }
}

