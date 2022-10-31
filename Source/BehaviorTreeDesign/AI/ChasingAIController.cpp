// Copyright 2019 Francesco Sapio. All right reserved.

#include "ChasingAIController.h"
#include "BehaviorTree/BehaviorTree.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "BehaviorTreeDesignCharacter.h"

AChasingAIController::AChasingAIController(const FObjectInitializer & ObjectInitializer)
	: Super(ObjectInitializer)
{

	//Creating the AI Perception Component
	PerceptionComponent = CreateDefaultSubobject<UAIPerceptionComponent>(TEXT("SightPerceptionComponent"));

	//Create the Sight Sense and Configure it
	SightConfig = CreateDefaultSubobject<UAISenseConfig_Sight>(FName("Sight Config"));
	SightConfig->DetectionByAffiliation.bDetectEnemies = true;
	SightConfig->DetectionByAffiliation.bDetectNeutrals = true;
	SightConfig->DetectionByAffiliation.bDetectFriendlies = true;

	//Assigning the Sight Sense to the AI Perception Component
	PerceptionComponent->ConfigureSense(*SightConfig);
	PerceptionComponent->SetDominantSense(SightConfig->GetSenseImplementation());

	//Binding the OnTargetPerceptionUpdate function
	PerceptionComponent->OnTargetPerceptionUpdated.AddDynamic(this, &AChasingAIController::OnTargetPerceptionUpdate);
}

void AChasingAIController::OnPossess(APawn * InPawn)
{
	Super::OnPossess(InPawn);
	if (BehaviorTree != nullptr) {
		RunBehaviorTree(BehaviorTree);
	}
}


void AChasingAIController::OnTargetPerceptionUpdate(AActor * Actor, FAIStimulus Stimulus)
{
	if(Cast<ABehaviorTreeDesignCharacter>(Actor)){
		LastKnownPlayerPosition = Stimulus.StimulusLocation;
		bCanSeePlayer = Stimulus.WasSuccessfullySensed();
	}
}
