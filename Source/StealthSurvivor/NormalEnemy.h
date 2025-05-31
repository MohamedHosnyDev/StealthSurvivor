// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "TheGun.h"
#include "TimerManager.h"
#include "BehaviorTree/BehaviorTree.h"
#include "NormalEnemy.generated.h"

UCLASS()
class STEALTHSURVIVOR_API ANormalEnemy : public ACharacter
{
	GENERATED_BODY()

public:
	// Sets default values for this character's properties
	float speed ;
	UPROPERTY(EditAnywhere)
	TSubclassOf<ATheGun> TheGun ;
	ATheGun * Gun ;
	bool StopShooting ;
	UPROPERTY(EditAnywhere)
	int MaxHealth;
	int CurrentHealth ;
	UPROPERTY(EditAnywhere)
	int DamageAmount = 10 ;
	UPROPERTY(BlueprintReadOnly)
	bool IsMoving ;
	// Made to Activate CheckLastLocationOrShootLocationBTTask
	bool IsDamaged ;
	// I declared the behavior tree here to have the ability to put multible AI enemies with out the need to make a copy of every controller 
	UPROPERTY(EditAnywhere)
	UBehaviorTree * BehaviorTree ;
	// The following 3 bool variables are used for the stalker
	UPROPERTY(EditAnywhere)
	bool IsStalker = false;
	// To avoid restarting his rest time
	bool IsTiming ;
	bool IsStanding ;
	// I used 3 timer to avoid a lag that happened with me when i was playing the game
	FTimerHandle TimerForRest ;
	FTimerHandle TimerForFirstIsStandingSet ;
	FTimerHandle TimerForSecondIsStandingSet ;

	ANormalEnemy();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	//This function will damage the player using Gun -> HittedActor
	void Shoot();
	UFUNCTION(BlueprintPure)
	bool IsDead();
	void FullHealth();
	UFUNCTION(BlueprintPure)
	bool GetIsMoving() ;
	UFUNCTION(BlueprintPure)
	bool GetIsStanding();
	// set IsStanding true if it is false and vice versa
	void SetIsStanding();

};
