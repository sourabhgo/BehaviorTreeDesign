// Copyright 2019 Francesco Sapio. All right reserved.

#include "BTTaskNode_FindRandomLocation.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "NavigationSystem.h"
#include "AIController.h"


UBTTaskNode_FindRandomLocation::UBTTaskNode_FindRandomLocation(const FObjectInitializer & ObjectInitializer)
	: Super(ObjectInitializer)
{
	NodeName = "Find Random Location";

	DestinationVector.AddVectorFilter(this, GET_MEMBER_NAME_CHECKED(UBTTaskNode_FindRandomLocation, DestinationVector));
}

EBTNodeResult::Type UBTTaskNode_FindRandomLocation::ExecuteTask(UBehaviorTreeComponent & OwnerComp, uint8 * NodeMemory)
{
	
	//Get Blackboard Component
	UBlackboardComponent* BlackboardComp = OwnerComp.GetBlackboardComponent();
	if (BlackboardComp == NULL)
	{
		return EBTNodeResult::Failed;
	}

	//Get Controlled Pawn
	APawn* ControlledPawn = OwnerComp.GetAIOwner()->GetPawn();
	if (!ControlledPawn) {
		return EBTNodeResult::Failed;
	}
	
	//Get Navigation System
	UNavigationSystemV1* NavSys = UNavigationSystemV1::GetCurrent(GetWorld());
	if (!NavSys)
	{
		return EBTNodeResult::Failed;
	}

	//Prepare variables for Query
	FNavLocation Result;
	FVector Origin = ControlledPawn->GetActorLocation();

	//Perform Query
	bool bSuccess = NavSys->GetRandomReachablePointInRadius(Origin, Radius, Result);
	if (!bSuccess) {
		return EBTNodeResult::Failed;
	}

	//Save Result and return success
	BlackboardComp->SetValueAsVector(DestinationVector.SelectedKeyName, Result.Location);
	return EBTNodeResult::Succeeded;
}

FString UBTTaskNode_FindRandomLocation::GetStaticDescription() const
{
	
	return FString::Printf(TEXT("%s: '%s'"), TEXT("DestinationKey"), DestinationVector.IsSet() ? *DestinationVector.SelectedKeyName.ToString() : TEXT(""))
			.Append(FString::Printf(TEXT("\n%s: '%s'"), TEXT("Radius"), *FString::SanitizeFloat(Radius)));
}
