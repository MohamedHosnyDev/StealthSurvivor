// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "SurvivorCharacterController.h"
#include"PhysicsEngine/PhysicsHandleComponent.h"
#include "NormalEnemy.h"
#include "SurvivorCharacter.generated.h"


// class ATheGun
UCLASS()
class STEALTHSURVIVOR_API ASurvivorCharacter : public ACharacter
{
	GENERATED_BODY()

public:
	// Sets default values for this character's properties

	ASurvivorCharacter();

	UPROPERTY(EditAnywhere)
	class USpringArmComponent * SpringArm ;
	UPROPERTY(EditAnywhere)
	class UCameraComponent * CameraComponent; 
	FTransform TransformThirdPerson ;
	FTransform TransformTopDown ;
	ASurvivorCharacterController * PlayerController ;
	// to get the moving direction
	float MovingRotationYaw ;
	bool ThirdPerson ;
	class ATheGun * Gun;
	UPROPERTY(EditAnywhere)
	TSubclassOf<class ATheGun> TheGun;
	UPROPERTY(EditAnywhere)
	int PlayerAmmu = 20 ;	
	UPROPERTY(EditAnywhere)
	float PlayerMaxHealth ;
	float PlayerCurrentHealth ;
	UPROPERTY(EditAnywhere)
	float PlayerSpeed = 5;
	bool PlayerIsDead ;
	ANormalEnemy * Enemy ;
	int DamageEnemy = 20 ;


	FCollisionShape Sphere = FCollisionShape::MakeSphere(400);
	FHitResult HittedKey ;
	FVector GrabingRange ;
	UPrimitiveComponent * DoorKey;
	UPhysicsHandleComponent * PhysicsHandler;


protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

	void MoveForward(float scale);
	void MoveRight(float scale);
	UFUNCTION(BlueprintPure)
	//This function is used to determine which moving animation will be played
	float GetMovingRotationYaw();
	void ChangeCamera();

	//This function will damage the enemy using Gun -> HittedActor
	void Shooting();
	UFUNCTION(BlueprintPure)
	//Used in the UI
	int GetAmmu();
	void GrabKey();
	void LeaveKey();

	UFUNCTION(BlueprintPure)
	//Used in the UI
	float GetHealthPercentage();
	UFUNCTION(BlueprintPure)
	bool IsDead();
	void GoToMainMenu();
	

};
