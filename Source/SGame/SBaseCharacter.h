// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "SGame.h"
#include "BaseObject.h"
#include "BaseWeapon.h"
#include "SSword.h"
#include "SBaseCharacter.generated.h"

UCLASS()
class SGAME_API ASBaseCharacter : public ACharacter
{
	GENERATED_BODY()

public:
	ASBaseCharacter();

	UFUNCTION(BlueprintImplementableEvent)
	void fireTest(int signal);

	UFUNCTION(BlueprintCallable)
	ABaseWeapon* GetCurrentWeapon();

	UFUNCTION(BlueprintCallable)
	void CriticalArt();

	UFUNCTION(BlueprintCallable)
	float GetHealth();

	UFUNCTION(BlueprintImplementableEvent)
	void ReportPickUp(bool hasPickUp);

	UFUNCTION(BlueprintCallable)
	void ConfirmPickUp();

	void AddWeapon(ABaseWeapon* NewWeapon);

	// call back function for animNotify
	UFUNCTION(BlueprintCallable)
	void ShiftWeapon();

	UFUNCTION(BlueprintCallable)
	void ThrowWeapon();

	UFUNCTION(BlueprintCallable)
	SWeaponType GetCurrentWeaponType();

	UFUNCTION(BlueprintCallable)
	void NextWeapon();

	UFUNCTION(BlueprintCallable)
	void PlayMyMontage(UAnimMontage* CurrentMontage);

	void TakeHit(FTakeHitInfo MyHitInfo);

	UFUNCTION(BlueprintCallable)
	void OnAttack();

	UFUNCTION(BlueprintCallable)
	ASSword* GetMySword();

protected:
	UPROPERTY(EditDefaultsOnly)
	UAnimMontage* WeaponChangeMontage;

private:
	ABaseObject* DetectPickUp();

	ABaseObject* LastPickUpObject = nullptr;

	TArray<ABaseWeapon*> MyWeapons;

	int WeaponIndex = -1; // -1 for no weapon

	float MyHealth;

	float MaxHealth;

	float LastHitTime;

	int CACount;

	void OnDeath();

	void EnableCrouch();

	void UnableCrouch();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

	virtual void Tick(float DeltaTime) override;
};
