// Copyright 2019 Francesco Sapio. All right reserved.

#pragma once

#include "CoreMinimal.h"
#include "AIController.h"
#include "Perception/AIPerceptionComponent.h"
#include "Perception/AISense_Sight.h"
#include "Perception/AISenseConfig_Sight.h"
#include "ChasingAIController.generated.h"

/**
 * 
 */
UCLASS()
class BEHAVIORTREEDESIGN_API AChasingAIController : public AAIController
{
	GENERATED_BODY()

	AChasingAIController(const FObjectInitializer& ObjectInitializer = FObjectInitializer::Get());

	virtual void OnPossess(class APawn* InPawn) override;

    //UAIPerceptionComponent* PerceptionComponent;
	UAISenseConfig_Sight* SightConfig;

protected:
	UFUNCTION()
	void OnTargetPerceptionUpdate(AActor* Actor, FAIStimulus Stimulus);


public:
	FVector LastKnownPlayerPosition;
	bool bCanSeePlayer;

	UPROPERTY(EditAnywhere)
	UBehaviorTree* BehaviorTree;
	
};
