// Fill out your copyright notice in the Description page of Project Settings.


#include "NormalEnemy.h"
#include "Kismet/GameplayStatics.h"
#include "SurvivorCharacter.h"
#include "SurvivorCharacterController.h"
#include "EnemyController.h"
#include "BehaviorTree/BlackboardComponent.h"

// Sets default values

//The Player and PlayerController were decleared here to avoid the circular dependency
ASurvivorCharacter * Player ;
// used to stop shooting by the enemy when the game end`s by accessing GameEnded bool variable
ASurvivorCharacterController * PlayerController ;

ANormalEnemy::ANormalEnemy()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true ;
	
	speed = 150 ;
	MaxHealth = 60 ;
	IsMoving = true ;
	IsDamaged = false ;
	IsTiming = false ;
}

// Called when the game starts or when spawned
void ANormalEnemy::BeginPlay()
{
	Super::BeginPlay();

	CurrentHealth = MaxHealth ;
	IsStanding = false ;
	StopShooting = false ;
	if(TheGun)
	{
		Gun = GetWorld() -> SpawnActor<ATheGun>(TheGun);
		Gun->SetOwner(this);
		Gun->AttachToComponent(GetMesh(), FAttachmentTransformRules::KeepRelativeTransform , TEXT("GunPlace"));
	}
	PlayerController = Cast<ASurvivorCharacterController>(UGameplayStatics::GetPlayerController(GetWorld(),0));
	
}

// Called every frame
void ANormalEnemy::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	if(PlayerController->GameEnded)
	{
		StopShooting = true ;
	}
}

void ANormalEnemy::Shoot()
{
	if(StopShooting)
	{return ;}

	Gun -> Shoot();

	if(Gun->HittedActor.GetActor())
	{
		if(Gun->HittedActor.GetActor()->ActorHasTag("Player"))
		{
			Player = Cast<ASurvivorCharacter>(UGameplayStatics::GetPlayerPawn(GetWorld(),0));
			Player -> PlayerCurrentHealth -= DamageAmount ;
		}
	}
	
}

bool ANormalEnemy::IsDead()
{
	
	if(CurrentHealth <= 0)
	{
		if(IsStalker && !IsTiming)
		{
			// I wrote 19.3 Seconds in the SetTimer Because that the SetTimer seconds may be slower than the real time seconds
			GetWorldTimerManager().SetTimer(TimerForRest , this , &ANormalEnemy::FullHealth , 19.3 , false);
			// the stalker will not move for 8 seconds and will stay down
			GetWorldTimerManager().SetTimer(TimerForFirstIsStandingSet , this , &ANormalEnemy::SetIsStanding , 8 , false);
			// 8(rest) + 11.3(the time needed to finish the standing animation) + 1 (to make sure that the stalker is not dead) = 20 seconds
			GetWorldTimerManager().SetTimer(TimerForSecondIsStandingSet , this , &ANormalEnemy::SetIsStanding , 20.3 , false);
			IsTiming = true ;
			return true ;
		}
		else if(IsStalker && IsTiming)
		{
			return true ;
		}
		else
		{
			DetachFromControllerPendingDestroy();
			return true ;
		}
	}
	return false ;
	
}

void ANormalEnemy::FullHealth()
{
	CurrentHealth = MaxHealth ;
	IsTiming = false ;
}

bool ANormalEnemy::GetIsMoving()
{
	return IsMoving ;
}

bool ANormalEnemy::GetIsStanding()
{
	return IsStanding ;
}

void ANormalEnemy::SetIsStanding()
{
	if(IsStanding)
	{
		IsStanding = false ;
	}
	else 
	{
		IsStanding = true ;
	}
}

