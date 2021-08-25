// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "SGame.h"
#include "BaseWeapon.h"
#include "SSniper.generated.h"

/**
 * 
 */
UCLASS()
class SGAME_API ASSniper : public ABaseWeapon
{
	GENERATED_BODY()
public:
	void OnAttack() override;
protected:
	UPROPERTY(EditDefaultsOnly)
	UAnimMontage* TakeHitMontage;
	UPROPERTY(EditDefaultsOnly)
	UParticleSystem* ExplosionEffect;
};
