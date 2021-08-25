// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BaseWeapon.h"
#include "SGame.h"

#include "SSword.generated.h"

/**
 * 
 */
UCLASS()
class SGAME_API ASSword : public ABaseWeapon
{
	GENERATED_BODY()
public:
	ASSword();

	void OnAttack() override;

	UFUNCTION(BlueprintCallable)
	void StartTrace();

	UFUNCTION(BlueprintCallable)
	void EndTrace();

	void Tick(float DeltaTime) override;

	UFUNCTION(BlueprintCallable)
	void RefreshCombo();

	UFUNCTION(BlueprintCallable)
	void SaveCombo();

	UFUNCTION(BlueprintImplementableEvent)
	void FireTest(int signal);

protected:
	UPROPERTY(EditDefaultsOnly)
	UAnimMontage* SlashA;
	UPROPERTY(EditDefaultsOnly)
	UAnimMontage* SlashB;
	UPROPERTY(EditDefaultsOnly)
	UAnimMontage* TakeHitMontage;
private:
	bool bTracing;
	bool bSaveCombo;
};
