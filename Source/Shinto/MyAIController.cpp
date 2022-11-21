// Fill out your copyright notice in the Description page of Project Settings.


#include "MyAIController.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "Kismet/GameplayStatics.h"
#include "AIModule/Classes/Navigation/CrowdFollowingComponent.h"
#include "GameFramework/Controller.h"


AMyAIController::AMyAIController()
{
	PerceptionComp = CreateDefaultSubobject<UAIPerceptionComponent>("PerceptionComp");
	SightConfig = CreateDefaultSubobject<UAISenseConfig_Sight>("SightConfig");
	if (SightConfig && PerceptionComp)
	{
		SightConfig->SightRadius = AISightRadius;
		SightConfig->LoseSightRadius = AILoseSightRadius;
		SightConfig->PeripheralVisionAngleDegrees = AISightAngle;

		SightConfig->DetectionByAffiliation.bDetectNeutrals = true;
		SightConfig->DetectionByAffiliation.bDetectEnemies = true;
		SightConfig->DetectionByAffiliation.bDetectFriendlies = true;

		PerceptionComp->SetDominantSense(*SightConfig->GetSenseImplementation());
		PerceptionComp->ConfigureSense(*SightConfig);
	}
}

void AMyAIController::BeginPlay()
{
	Super::BeginPlay();

	CurrentHealth = MaxHealth;
	if (PerceptionComp)
	{
		PerceptionComp->OnTargetPerceptionUpdated.AddDynamic(this, &AMyAIController::PerceptionUpdated);
	}
	

}

void AMyAIController::OnPossess(APawn* PawnToPossess)
{
	Super::OnPossess(PawnToPossess);
	if (BehaviorTreeToUse)
	{
		RunBehaviorTree(BehaviorTreeToUse);
	}
	
}

void AMyAIController::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}


void AMyAIController::PerceptionUpdated(AActor* Target, FAIStimulus Stimulus)
{
	ACharacterBase* TargetAsCharacterBase = Cast<ACharacterBase>(Target);
	if (!TargetAsCharacterBase)
		return;

	if (Stimulus.WasSuccessfullySensed())
	{
		GetBlackboardComponent()->SetValueAsObject(FName("Target"), Target);
	}
	else
	{
		auto actorInfo = PerceptionComp->GetActorInfo(*Target);
		if (!actorInfo->HasAnyCurrentStimulus())
		{
			GetBlackboardComponent()->ClearValue(FName("Target"));
		}
	}
	//if (Stimulus.WasSuccessfullySensed())
	//{
	//	auto ExistingTarget = GetBlackboardComponent()->GetValueAsObject(FName("Target"));
	//	UAISenseConfig* StimulusConfig = PerceptionComp->GetSenseConfig(Stimulus.Type);
	//	if (!ExistingTarget || StimulusConfig->GetClass() == UAISenseConfig_Sight::StaticClass())
	//	{
	//		if (Target == Cast<ACharacterBase, AActor>(Target))
	//		{
	//			
	//			GetBlackboardComponent()->SetValueAsObject(FName("Target"), Target);
	//		}
	//	}
	//	else
	//	{
	//		TArray<AActor*> ActorInSight;
	//		PerceptionComp->GetCurrentlyPerceivedActors(UAISenseConfig_Sight::StaticClass(), ActorInSight);
	//		for (int i = 0; i < ActorInSight.Num(); i++)
	//		{
	//			if (ActorInSight.Num() == 0)
	//			{
	//				GetBlackboardComponent()->ClearValue(FName("Target"));
	//			}
	//		}
	//	}
	//}
	//else
	//{
	//	GetBlackboardComponent()->ClearValue(FName("Target"));
	//}
}

void AMyAIController::ChangeHealth(float changeAmount)
{
	UE_LOG(LogTemp, Warning, TEXT("Gets to ChangeHealth"));
	if (CurrentHealth > 0)
	{
		UE_LOG(LogTemp, Warning, TEXT("Changes Health Of the Snail"));
		CurrentHealth -= changeAmount;
	}
	else if (CurrentHealth <= 0)
	{
		SetDeath();
	}
}

void AMyAIController::SetDeath()
{
	//Should Set the animation to the death state
	UE_LOG(LogTemp, Warning, TEXT("Is dead"));
	GetPawn()->Destroy();
	Destroy();
}
