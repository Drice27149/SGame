// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "BaseObject.h"
#include "BaseWeapon.generated.h"

class ASBaseCharacter;

UCLASS()
class SGAME_API ABaseWeapon : public ABaseObject
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ABaseWeapon();

public:
	UPROPERTY(EditDefaultsOnly)
	FName PlaceSocket;

	UPROPERTY(EditDefaultsOnly)
	FName UseSocket;

	UPROPERTY(EditDefaultsOnly)
	float CoolDownTime;

	UPROPERTY(EditAnywhere)
	SWeaponType MyWeaponType;

	void OnPickUp(ASBaseCharacter* OwnerCharacter) override;

	void OnThrow();

	void OnAttachUse();

	void OnAttachPlace();

	virtual void OnAttack();

	virtual void CriticalArt();

	virtual SWeaponType GetWeaponType();

	UFUNCTION(BlueprintCallable)
	virtual void CriticalArtTick();

protected:
	// TODO: set timer
	FTimerHandle CooldownTimer;
	bool bBusy;

private:
	UFUNCTION()
	void RefreshWeapon();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	

};
