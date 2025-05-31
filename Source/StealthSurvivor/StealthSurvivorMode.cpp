// Fill out your copyright notice in the Description page of Project Settings.


#include "StealthSurvivorMode.h"
#include "TimerManager.h"
#include "Blueprint/UserWidget.h"
#include "Kismet/GameplayStatics.h"



void AStealthSurvivorMode :: BeginPlay()
{
    Super::BeginPlay();

    FTimerHandle RemoveStartHandler ;
    
    if(TheStartWidget)
    {
        StartWidget = CreateWidget(UGameplayStatics::GetPlayerController(GetWorld(),0) , TheStartWidget);
        StartWidget -> AddToViewport();
        GetWorldTimerManager().SetTimer(RemoveStartHandler,this,&AStealthSurvivorMode::RemoveStartWidget,4,false);
    }
    
}


void AStealthSurvivorMode :: RemoveStartWidget()
{
    if(TheStartWidget)
    {
        StartWidget -> RemoveFromParent();
    }
    
}

void AStealthSurvivorMode :: PlayWinWidget()
{
    if(TheWinWidget)
    {
        WinWidget = CreateWidget(UGameplayStatics::GetPlayerController(GetWorld(),0) , TheWinWidget) ;
        WinWidget -> AddToViewport();
    }
    
}

void AStealthSurvivorMode :: PlayLossWidget()
{
    if(TheLossWidget)
    {
        LossWidget = CreateWidget(UGameplayStatics::GetPlayerController(GetWorld(),0) , TheLossWidget) ;
        LossWidget -> AddToViewport();
    }
    
}

