// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BaseWeapon.h"
#include "SHammer.generated.h"

/**
 * 
 */
UCLASS()
class SGAME_API ASHammer : public ABaseWeapon
{
	GENERATED_BODY()
	
public:
	void OnAttack() override;
};
