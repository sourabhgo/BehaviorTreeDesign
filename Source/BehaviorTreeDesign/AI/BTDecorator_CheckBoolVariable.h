// Copyright 2019 Francesco Sapio. All right reserved.

#pragma once

#include "CoreMinimal.h"
#include "BehaviorTree/BTDecorator.h"
#include "BTDecorator_CheckBoolVariable.generated.h"

/**
 * 
 */
UCLASS()
class BEHAVIORTREEDESIGN_API UBTDecorator_CheckBoolVariable : public UBTDecorator
{
	GENERATED_BODY()

	UBTDecorator_CheckBoolVariable(const FObjectInitializer& ObjectInitializer = FObjectInitializer::Get());

protected:

	/** blackboard key selector */
	UPROPERTY(EditAnywhere, Category = Blackboard)
	FBlackboardKeySelector BoolVariableToCheck;

public:

	virtual bool CalculateRawConditionValue(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory) const override;

	virtual FString GetStaticDescription() const override;
};
