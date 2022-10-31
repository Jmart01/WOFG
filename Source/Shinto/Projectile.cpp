// Fill out your copyright notice in the Description page of Project Settings.


#include "Projectile.h"
#include "MyAIController.h"
#include "SetActorAttributes.h"

// Sets default values
AProjectile::AProjectile()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	SphereComp = CreateDefaultSubobject<USphereComponent>("SphereComp");
	SetRootComponent(SphereComp);
	SphereComp->SetSphereRadius(64.f);
	SphereComp->SetCollisionResponseToAllChannels(ECR_Ignore);
	SphereComp->SetCollisionResponseToChannel(ECC_Pawn, ECR_Overlap);
	LifeDuration = 3.f;
}

// Called when the game starts or when spawned
void AProjectile::BeginPlay()
{
	Super::BeginPlay();
	SetLifeSpan(LifeDuration);
}

// Called every frame
void AProjectile::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	AddActorWorldOffset(Velocity * DeltaTime);
}

void AProjectile::NotifyActorBeginOverlap(AActor* OtherActor)
{
	if (OtherActor == GetOwner())
	{
		return;
	}
	if (SpecToApplyToTarget.IsValid())
	{
		AMyAIController* otherActorAsAIController = Cast<AMyAIController>(OtherActor);
		if (otherActorAsAIController)
		{
			USetActorAttributes* Attributes= Cast<USetActorAttributes>(GetOwner()->GetComponentByClass(USetActorAttributes::StaticClass()));
			otherActorAsAIController->ChangeHealth(Attributes->GetAttackPower());
		}
	}

}



