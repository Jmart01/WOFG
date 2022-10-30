// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/SphereComponent.h"
#include "GameFramework/Actor.h"

#include "Projectile.generated.h"

UCLASS()
class SHINTO_API AProjectile : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AProjectile();
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Collision")
		USphereComponent* SphereComp;
	//leave room for a niagara system

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "GameplayAbility", Meta = (ExposeOnSpawn = "true"))
		FVector Velocity;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "GameplayAbility", Meta = (ExposeOnSpawn = "true"))
		float LifeDuration;

	//UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "GameplayAbility", Meta = (ExposeOnSpawn = "true"))
		//FGameplayEffectSpecHandle SpecToApplyToTarget;
protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

};
