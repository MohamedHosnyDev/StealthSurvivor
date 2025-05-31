// Fill out your copyright notice in the Description page of Project Settings.


#include "TheGun.h"
#include "Particles/ParticleSystem.h"
#include "Kismet/KismetSystemLibrary.h"
#include "Kismet/GameplayStatics.h"
#include "DrawDebugHelpers.h"

// Sets default values
ATheGun::ATheGun()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	RootComp = CreateDefaultSubobject<USceneComponent>(TEXT("RootComp"));
	SetRootComponent(RootComp);
	GunComponent = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("GunComponent"));
	GunComponent->SetupAttachment(RootComp);
	BulletComponent = CreateDefaultSubobject<USceneComponent>(TEXT("BulletComponent"));
	BulletComponent -> SetupAttachment(GunComponent);

}


void ATheGun ::Shoot()
{
	BulletPlace = BulletComponent->GetComponentLocation();
	
	if(GetOwner() == nullptr)
	{return;}

	APawn * owner = Cast<APawn>(GetOwner());
	
	BulletRange = owner->GetController()->GetViewTarget()->GetActorLocation() + (owner->GetController()->GetViewTarget()->GetActorRotation()).Vector()*3500;
	
	FCollisionQueryParams IgnoredParams;
	IgnoredParams.AddIgnoredActor(this);
	IgnoredParams.AddIgnoredActor(GetOwner());

	bool trace = GetWorld()->LineTraceSingleByChannel(HittedActor,BulletPlace,BulletRange,ECollisionChannel::ECC_GameTraceChannel1,IgnoredParams);
	
	if(ShootingParticle)
		UGameplayStatics::SpawnEmitterAtLocation(this,ShootingParticle,BulletPlace);

	if(ShootingSound)
		UGameplayStatics::PlaySoundAtLocation(this,ShootingSound,BulletPlace);

	if(ImpactParticle && trace)
		UGameplayStatics::SpawnEmitterAtLocation(this,ImpactParticle,HittedActor.Location);

	if(ImpactSound && trace)
		UGameplayStatics::PlaySoundAtLocation(this,ImpactSound,HittedActor.Location);

	if(HittedActor.GetActor())
	{
		ActorTakedDamage = true ; 
	}
	

}



