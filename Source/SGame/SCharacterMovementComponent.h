// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "SGame.h"
#include "SCharacterMovementComponent.generated.h"

/**
 * 
 */
UCLASS()
class SGAME_API USCharacterMovementComponent : public UCharacterMovementComponent
{
	GENERATED_BODY()

	virtual float GetMaxSpeed() const override;
public:
	void EnableSpeedUp();
	void UnableSpeedUp();
private:
	const float SpeedUpScale = 2.5f;
	bool bRun = false;
};
