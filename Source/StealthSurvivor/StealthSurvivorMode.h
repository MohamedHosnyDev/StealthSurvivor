// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameModeBase.h"
#include "NormalEnemy.h"
#include "StealthSurvivorMode.generated.h"

/**
 * 
 */

UCLASS()
class STEALTHSURVIVOR_API AStealthSurvivorMode : public AGameModeBase
{
	GENERATED_BODY()

	public: 

		UPROPERTY(EditDefaultsOnly)
		TSubclassOf< class UUserWidget> TheStartWidget ;
		UUserWidget * StartWidget ;
		UPROPERTY(EditDefaultsOnly)
		TSubclassOf< class UUserWidget> TheWinWidget ;
		UUserWidget * WinWidget ;
		UPROPERTY(EditDefaultsOnly)
		TSubclassOf< class UUserWidget> TheLossWidget ;
		UUserWidget * LossWidget ;
		ANormalEnemy * NormalEnemy ;
		ANormalEnemy * Stalker ;

		void RemoveStartWidget();
		void PlayWinWidget();
		void PlayLossWidget();

	protected:

		virtual void BeginPlay()override ;	

};
