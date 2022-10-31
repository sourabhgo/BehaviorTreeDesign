// Copyright 2019 Francesco Sapio. All right reserved.

#pragma once

#include "CoreMinimal.h"
#include "BehaviorTree/BTService.h"
#include "BTService_UpdateChasing.generated.h"

/**
 * 
 */
UCLASS()
class BEHAVIORTREEDESIGN_API UBTService_UpdateChasing : public UBTService
{
	GENERATED_BODY()

	UBTService_UpdateChasing(const FObjectInitializer& ObjectInitializer = FObjectInitializer::Get());

	UPROPERTY(EditAnywhere, Category = PlayerClass)
	TSubclassOf<AActor> PlayerClass;

	UPROPERTY(EditAnywhere, Category = Blackboard)
	FBlackboardKeySelector CanSeePlayerKey;

	UPROPERTY(EditAnywhere, Category = Blackboard)
	FBlackboardKeySelector PlayerKey;

	UPROPERTY(EditAnywhere, Category = Blackboard)
	FBlackboardKeySelector LastKnownPositionKey;

private:
	
	bool bLastCanSeePlayer;

protected:

	virtual void OnBecomeRelevant(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory) override;

	virtual void TickNode(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory, float DeltaSeconds) override;

	virtual FString GetStaticDescription() const override;
	
};
