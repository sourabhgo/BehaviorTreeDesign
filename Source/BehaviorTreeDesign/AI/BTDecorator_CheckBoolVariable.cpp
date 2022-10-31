// Copyright 2019 Francesco Sapio. All right reserved.

#include "BTDecorator_CheckBoolVariable.h"
#include "BehaviorTree/BlackboardComponent.h"

UBTDecorator_CheckBoolVariable::UBTDecorator_CheckBoolVariable(const FObjectInitializer & ObjectInitializer)
	: Super(ObjectInitializer)
{
	NodeName = "Check Bool Variable";

	BoolVariableToCheck.AddBoolFilter(this, GET_MEMBER_NAME_CHECKED(UBTDecorator_CheckBoolVariable, BoolVariableToCheck));
}

bool UBTDecorator_CheckBoolVariable::CalculateRawConditionValue(UBehaviorTreeComponent & OwnerComp, uint8 * NodeMemory) const
{
	//Get BlackboardComponent
	const UBlackboardComponent* BlackboardComp = OwnerComp.GetBlackboardComponent();
	if (BlackboardComp == NULL)
	{
		return false;
	}

	//Perform Boolean Variable Check
	return BlackboardComp->GetValueAsBool(BoolVariableToCheck.SelectedKeyName);

	//UE_LOG(LogTemp, Warning, TEXT("test's Bool is %s"), (test ? TEXT("True") : TEXT("False")));
}

FString UBTDecorator_CheckBoolVariable::GetStaticDescription() const
{
	FString ReturnDesc = Super::GetStaticDescription();
	ReturnDesc += "\n\n";
	ReturnDesc += FString::Printf(TEXT("%s: '%s'"), TEXT("Bool Variable to Check"), BoolVariableToCheck.IsSet() ? *BoolVariableToCheck.SelectedKeyName.ToString() : TEXT(""));
	return ReturnDesc;
}
