// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "SGame.h"
#include "BaseObject.generated.h"

class ASBaseCharacter;

UCLASS()
class SGAME_API ABaseObject : public AActor
{
	GENERATED_BODY()
	
public:
	UPROPERTY(EditDefaultsOnly)
	 	USphereComponent* CollisionComp;
	UPROPERTY(EditDefaultsOnly)
		USphereComponent* PickUpComp;
	UPROPERTY(EditDefaultsOnly)
		USkeletalMeshComponent* MeshComp;
	bool bUsing = false;

	ASBaseCharacter* MyOwner;

	virtual void OnPickUp(ASBaseCharacter* OwnerCharacter);

	// Sets default values for this actor's properties
	ABaseObject();
protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

};
