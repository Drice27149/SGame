// Copyright Epic Games, Inc. All Rights Reserved.

#pragma once

#include "Camera/CameraComponent.h"
#include "CoreMinimal.h"
#include "Components/CapsuleComponent.h"
#include "Components/InputComponent.h"
#include "Components/SphereComponent.h"
#include "DrawDebugHelpers.h"
#include "Engine/World.h"
#include "GameFramework/Character.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "GameFramework/Controller.h"
#include "GameFramework/ProjectileMovementComponent.h"
#include "GameFramework/SpringArmComponent.h"
#include "Kismet/GameplayStatics.h"

UENUM(BlueprintType)
enum class SWeaponType: uint8 
{
	SEmpty		UMETA(DisplayName = "NoWeapon"), 
	SRifle		UMETA(DisplayName = "Rifle"),
	SHammer		UMETA(DisplayName = "Hammer"),
	SSniper		UMETA(DisplayName = "Sniper"), 
	SPistol     UMETA(DisplayName = "Pistol"),
};

struct FTakeHitInfo 
{
	float damage;
	AActor* Sender;
	UAnimMontage* TakeHitMontage;
};