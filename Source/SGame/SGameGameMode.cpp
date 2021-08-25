// Copyright Epic Games, Inc. All Rights Reserved.

#include "SGameGameMode.h"
#include "SGameCharacter.h"
#include "GameFramework/PlayerController.h"
#include "UObject/ConstructorHelpers.h"

ASGameGameMode::ASGameGameMode()
{
	// set default pawn class to our Blueprinted character
	// static ConstructorHelpers::FClassFinder<APawn> PlayerPawnBPClass(TEXT("/Game/ThirdPersonCPP/Blueprints/ThirdPersonCharacter"));
	static ConstructorHelpers::FClassFinder<APawn> PlayerPawnBPClass(TEXT("/Game/Blueprints/Character/MY_BPCharacter"));
	if (PlayerPawnBPClass.Class != NULL)
	{
		DefaultPawnClass = PlayerPawnBPClass.Class;
	}

	static ConstructorHelpers::FClassFinder<APlayerController> PCBPClass(TEXT("/Game/AdvancedLocomotionV4/Blueprints/CharacterLogic/ALS_Player_Controller"));
	if (PCBPClass.Class != NULL)
	{
		PlayerControllerClass = PCBPClass.Class;
	}
}
