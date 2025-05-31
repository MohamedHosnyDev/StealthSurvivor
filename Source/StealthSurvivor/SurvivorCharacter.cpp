// Fill out your copyright notice in the Description page of Project Settings.


#include "SurvivorCharacter.h"
#include "TheGun.h"
#include "Kismet/GameplayStatics.h"
#include "GameFramework/SpringArmComponent.h"
#include "Camera/CameraComponent.h"




// Sets default values
ASurvivorCharacter::ASurvivorCharacter()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	
	PhysicsHandler = CreateDefaultSubobject<UPhysicsHandleComponent>(TEXT("PhysicsHandler"));
	SpringArm = CreateDefaultSubobject<USpringArmComponent>(TEXT("SpringArm"));
	SpringArm->SetupAttachment(RootComponent);
	CameraComponent = CreateDefaultSubobject<UCameraComponent>(TEXT("Camera"));
	CameraComponent->SetupAttachment(SpringArm);
	ThirdPerson = false ;
	MovingRotationYaw = 0 ;
	PlayerMaxHealth = 150 ;
	PlayerCurrentHealth = PlayerMaxHealth;
	
}

// Called when the game starts or when spawned
void ASurvivorCharacter::BeginPlay()
{
	Super::BeginPlay();

	TransformThirdPerson.SetLocation(FVector(70,75,38));
	FQuat ThirdPersonRotation ;
	ThirdPersonRotation.X = 0 ;
	ThirdPersonRotation.Y = 0 ;
	ThirdPersonRotation.Z = 0 ;
	TransformThirdPerson.SetRotation(ThirdPersonRotation);
	TransformTopDown = SpringArm -> GetRelativeTransform();
	PlayerController = Cast<ASurvivorCharacterController>(GetController()) ;

	if(TheGun)
	{
		Gun = GetWorld()->SpawnActor<ATheGun>(TheGun);
		Gun->SetOwner(this);
		Gun->AttachToComponent(GetMesh(),FAttachmentTransformRules::KeepRelativeTransform,TEXT("GunPlace"));
	}
	
}

// Called every frame
void ASurvivorCharacter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	if(PhysicsHandler)
	{
		PhysicsHandler->SetTargetLocationAndRotation(GetActorLocation()+GetActorForwardVector()*200,GetActorRotation());
	}

}

// Called to bind functionality to input
void ASurvivorCharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

	PlayerInputComponent->BindAxis(TEXT("MoveForward"),this,&ASurvivorCharacter::MoveForward);

	PlayerInputComponent->BindAxis(TEXT("MoveBackward"),this,&ASurvivorCharacter::MoveForward);

	PlayerInputComponent->BindAxis(TEXT("MoveRight"),this,&ASurvivorCharacter::MoveRight);

	PlayerInputComponent->BindAxis(TEXT("MoveLeft"),this,&ASurvivorCharacter::MoveRight);

	PlayerInputComponent->BindAction(TEXT("Shoot"),EInputEvent::IE_Pressed,this,&ASurvivorCharacter::Shooting);

	PlayerInputComponent->BindAxis(TEXT("MoveCamera"),this,&APawn::AddControllerYawInput);

	PlayerInputComponent->BindAction(TEXT("Grab"),EInputEvent::IE_Pressed,this,&ASurvivorCharacter::GrabKey);

	PlayerInputComponent->BindAction(TEXT("Grab"),EInputEvent::IE_Released,this,&ASurvivorCharacter::LeaveKey);

	PlayerInputComponent->BindAction(TEXT("ChangeCamera"),EInputEvent::IE_Pressed,this,&ASurvivorCharacter::ChangeCamera);

	PlayerInputComponent->BindAction(TEXT("MainMenu"),EInputEvent::IE_Pressed,this,&ASurvivorCharacter::GoToMainMenu);

}

void ASurvivorCharacter::MoveForward(float scale)
{
	if(PlayerController->GameEnded)
	{return ;}

	if(scale == 1.0)
	{
		MovingRotationYaw = 0 ;
	}
	else if (scale == -1.0)
	{
		MovingRotationYaw = 180 ;
	}
	else
	{
		return ;
	}

	AddMovementInput(GetActorForwardVector() * PlayerSpeed * scale);

}

void ASurvivorCharacter::MoveRight(float scale)
{
	if(PlayerController->GameEnded)
	{return ;}
	
	if(scale == 1.0)
	{
		MovingRotationYaw = 90 ;
	}
	else if (scale == -1.0)
	{
		MovingRotationYaw = -90 ;
	}
	else
	{
		return ;
	}

	AddMovementInput(GetActorRightVector() * PlayerSpeed * scale);

}

float ASurvivorCharacter::GetMovingRotationYaw()
{
	return MovingRotationYaw ;
}

void ASurvivorCharacter::ChangeCamera()
{
	if(!ThirdPerson)
	{
		SpringArm -> SetRelativeTransform(TransformThirdPerson);
		ThirdPerson = true ;
	}
	else
	{
		SpringArm -> SetRelativeTransform(TransformTopDown);
		ThirdPerson = false ;
	}
}

void ASurvivorCharacter::Shooting()
{
	if(PlayerController->GameEnded)
	{return ;}
	
	if(PlayerAmmu>0)
	{
		Gun->Shoot();
		PlayerAmmu--;
		if(Gun -> HittedActor.GetActor() && Gun -> HittedActor.GetActor() -> ActorHasTag("Enemy"))
		{
			Enemy = Cast<ANormalEnemy>(Gun->HittedActor.GetActor());
			Enemy->CurrentHealth -= DamageEnemy ;
			Enemy->IsDamaged = true ;
		}
	}
}

int32 ASurvivorCharacter::GetAmmu()
{
	return PlayerAmmu;
}

void ASurvivorCharacter::GrabKey()
{
	GrabingRange = this->GetController()->GetViewTarget()->GetActorLocation() + (this->GetController()->GetViewTarget()->GetActorRotation().Vector())*300 ;

	bool sweep = GetWorld()->SweepSingleByChannel(HittedKey,GetActorLocation(),GrabingRange,FQuat::Identity,ECC_GameTraceChannel2,Sphere);
	if(sweep && HittedKey.GetComponent() && PhysicsHandler)
	{
		DoorKey = HittedKey.GetComponent();
		DoorKey->SetSimulatePhysics(true);
		DoorKey->WakeAllRigidBodies();

		PhysicsHandler->GrabComponentAtLocationWithRotation(DoorKey,NAME_None,HittedKey.ImpactPoint,GetActorRotation());
	}
	
	
}

void ASurvivorCharacter::LeaveKey()
{
	PhysicsHandler->ReleaseComponent();
}


float  ASurvivorCharacter::GetHealthPercentage()
{
	return PlayerCurrentHealth/PlayerMaxHealth ;
}

bool ASurvivorCharacter::IsDead()
{
	if(PlayerCurrentHealth <=0)
	{
		return true;
	}
	return false ;
}

void ASurvivorCharacter::GoToMainMenu()
{
	UGameplayStatics::OpenLevel(GetWorld(),"MainMenu");
}
