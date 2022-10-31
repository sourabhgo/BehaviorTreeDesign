// Copyright 2019 Francesco Sapio. All right reserved.

#include "BTService_UpdateChasing.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "AIController.h"
#include "ChasingAIController.h"
//#include "EngineUtils.h"
#include "Runtime/Engine/Classes/Kismet/GameplayStatics.h"

UBTService_UpdateChasing::UBTService_UpdateChasing(const FObjectInitializer& ObjectInitializer)
	: Super(ObjectInitializer)
{
	NodeName = "Update Chasing Behavior";

	bNotifyBecomeRelevant = true;
	bNotifyCeaseRelevant = false;

	// Filter the Blackboard Key Selectors
	PlayerKey.AddObjectFilter(this, GET_MEMBER_NAME_CHECKED(UBTService_UpdateChasing, PlayerKey), AActor::StaticClass());
	LastKnownPositionKey.AddVectorFilter(this, GET_MEMBER_NAME_CHECKED(UBTService_UpdateChasing, LastKnownPositionKey));
	CanSeePlayerKey.AddBoolFilter(this, GET_MEMBER_NAME_CHECKED(UBTService_UpdateChasing, CanSeePlayerKey));
}

void UBTService_UpdateChasing::OnBecomeRelevant(UBehaviorTreeComponent & OwnerComp, uint8 * NodeMemory)
{

	//Get Blackboard Component
	UBlackboardComponent* BlackboardComp = OwnerComp.GetBlackboardComponent();
	if (BlackboardComp == NULL)
	{
		return;
	}

	if (!PlayerKey.IsSet()) {
		//Retrieve Player and Update the Blackboard
		TArray<AActor*> FoundActors;
		UGameplayStatics::GetAllActorsOfClass(GetWorld(), PlayerClass, FoundActors);
		if (FoundActors[0]) {
			UE_LOG(LogTemp, Warning, TEXT("Found Player"));
			BlackboardComp->SetValueAsObject(PlayerKey.SelectedKeyName, FoundActors[0]);
		}
	}

}

void UBTService_UpdateChasing::TickNode(UBehaviorTreeComponent & OwnerComp, uint8 * NodeMemory, float DeltaSeconds)
{

	//Get Blackboard Component
	UBlackboardComponent* BlackboardComp = OwnerComp.GetBlackboardComponent();
	if (BlackboardComp == NULL)
	{
		return;
	}

	//Get AI Controller
	AAIController* AIController = OwnerComp.GetAIOwner();
	if (!AIController) {
		return;
	}

	//Get ChasingAIController (the controller we have created in the previous chapter)
	AChasingAIController* ChasingController = Cast<AChasingAIController>(AIController);
	if (!ChasingController) {
		UE_LOG(LogTemp, Warning, TEXT("Cannot Find Controller message"));
		return;
	}

	//Update the Blackboard with the current value of CanSeePlayer from the Chasing Controller
	BlackboardComp->SetValueAsBool(CanSeePlayerKey.SelectedKeyName, ChasingController->bCanSeePlayer);

	//If the LastCanSeePlayer is different from the current one, then update the LastKnownPlayerPosition
	if (ChasingController->bCanSeePlayer != bLastCanSeePlayer) {
		BlackboardComp->SetValueAsVector(LastKnownPositionKey.SelectedKeyName, ChasingController->LastKnownPlayerPosition);
	}

	//Update the LastCanSeePlayer with the current CanSeePlayer
	bLastCanSeePlayer = ChasingController->bCanSeePlayer;

	//Call to the parent TickNode
	Super::TickNode(OwnerComp, NodeMemory, DeltaSeconds);
	
}

FString UBTService_UpdateChasing::GetStaticDescription() const
{
	return FString::Printf(TEXT("%s: '%s'"), TEXT("Player Class"), PlayerClass ? *PlayerClass->GetName() : TEXT(""))
		.Append(FString::Printf(TEXT("\n%s: '%s'"), TEXT("PlayerKey"), PlayerKey.IsSet() ? *PlayerKey.SelectedKeyName.ToString() : TEXT("")))
		.Append(FString::Printf(TEXT("\n%s: '%s'"), TEXT("LastKnownPositionKey"), LastKnownPositionKey.IsSet() ? *LastKnownPositionKey.SelectedKeyName.ToString() : TEXT("")))
		.Append(FString::Printf(TEXT("\n%s: '%s'"), TEXT("CanSeePlayerKey"), CanSeePlayerKey.IsSet() ? *CanSeePlayerKey.SelectedKeyName.ToString() : TEXT("")));
}
