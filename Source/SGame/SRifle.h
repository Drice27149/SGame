// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "SGame.h"
#include "BaseWeapon.h"
#include "SRifleBullet.h"
#include "SRifle.generated.h"

/**
 * 
 */
UCLASS()
class SGAME_API ASRifle : public ABaseWeapon
{
	GENERATED_BODY()
public:
	UPROPERTY(EditDefaultsOnly)
	TSubclassOf<ASRifleBullet> RifleBulletClass;

public:
	UPROPERTY(EditDefaultsOnly)
	UAnimMontage* CAMontage;

	void OnAttack() override;
	void CriticalArt() override;
	void CriticalArtTick() override;
};
