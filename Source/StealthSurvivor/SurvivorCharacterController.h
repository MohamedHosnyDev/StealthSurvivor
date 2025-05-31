// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerController.h"
#include "StealthSurvivorMode.h"
#include "TimerManager.h"
#include "SurvivorCharacterController.generated.h"

/**
 * 
 */
UCLASS()
class STEALTHSURVIVOR_API ASurvivorCharacterController : public APlayerController
{
	GENERATED_BODY()

	public:

		APawn * Player ;
		bool GameEnded ;
		UPROPERTY(EditDefaultsOnly)
		TSubclassOf<class UUserWidget> TheGameplayWidget;
		class UUserWidget * GameplayWidget ;
		AStealthSurvivorMode * GameMode ;
		FTimerHandle MainMenuTimeHandler ;
		
		ASurvivorCharacterController();

		virtual void Tick(float DeltaTime) override ;
		virtual void GameHasEnded(class AActor * EndGameFocus , bool bIsWinner ) override;

	protected:

		virtual void BeginPlay()override ;

	
};
