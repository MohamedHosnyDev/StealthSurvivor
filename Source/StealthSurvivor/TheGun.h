// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "TimerManager.h"
#include "TheGun.generated.h"

class UParticleSystem;
class USoundBase;
UCLASS()
class STEALTHSURVIVOR_API ATheGun : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ATheGun();

	UPROPERTY(EditAnywhere)
	USceneComponent * RootComp;
	UPROPERTY(EditAnywhere)
	UStaticMeshComponent * GunComponent;
	UPROPERTY(EditAnywhere)
	USceneComponent * BulletComponent;
	UPROPERTY(EditAnywhere, category = "Particles")
	UParticleSystem * ShootingParticle ;
	UPROPERTY(EditAnywhere,category = "Particles")
	UParticleSystem * ImpactParticle ;
	UPROPERTY(EditAnywhere,category = "Sound")
	USoundBase * ShootingSound;
	UPROPERTY(EditAnywhere,category = "Sound")
	USoundBase * ImpactSound ;

	bool ActorTakedDamage = false;

	FVector BulletPlace ;
	FVector BulletDistance = FVector(2000,1,1);
	FVector BulletRange;
	FVector ViewLocation;
	FRotator ViewRotation;

	FHitResult HittedActor ;
	FTimerHandle TimerHandler ;

	//This function is used to trace the enemy
	void Shoot();




};
