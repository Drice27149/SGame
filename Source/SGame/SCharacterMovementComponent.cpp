// Fill out your copyright notice in the Description page of Project Settings.


#include "SCharacterMovementComponent.h"

float USCharacterMovementComponent::GetMaxSpeed() const
{
	float ResultSpeed = Super::GetMaxSpeed();
	if (bRun)
	{
		ResultSpeed *= SpeedUpScale;
	}
	return ResultSpeed;
}

void USCharacterMovementComponent::EnableSpeedUp()
{
	bRun = true;
}

void USCharacterMovementComponent::UnableSpeedUp()
{
	bRun = false;
}

