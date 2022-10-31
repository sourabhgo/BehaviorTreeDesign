#include "BehaviorTreeDesignGameMode.h"
#include "BehaviorTreeDesignCharacter.h"
#include "UObject/ConstructorHelpers.h"

ABehaviorTreeDesignGameMode::ABehaviorTreeDesignGameMode()
{
	// set default pawn class to our Blueprinted character
	static ConstructorHelpers::FClassFinder<APawn> PlayerPawnBPClass(TEXT("/Game/ThirdPersonCPP/Blueprints/ThirdPersonCharacter"));
	if (PlayerPawnBPClass.Class != NULL)
	{
		DefaultPawnClass = PlayerPawnBPClass.Class;
	}
}
