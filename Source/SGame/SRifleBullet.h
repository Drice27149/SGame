// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "SGame.h"
#include "SRifleBullet.generated.h"

UCLASS()
class SGAME_API ASRifleBullet : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ASRifleBullet();

public:
	UFUNCTION(BlueprintImplementableEvent)
	void fireTest(int signal);

protected:
	UPROPERTY(EditDefaultsOnly)
		class USphereComponent* SphereCollisionComp;

	// Movement component for handling projectile movement.
	UPROPERTY(EditDefaultsOnly)
		class UProjectileMovementComponent* ProjectileMovementComp;

	UPROPERTY(EditDefaultsOnly)
		UAnimMontage* TakeHitMontage;

	UPROPERTY(EditDefaultsOnly)
		UParticleSystem* ExplosionEffect;

private:
	UFUNCTION()
	void OnBulletImpact(UPrimitiveComponent* HitComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, FVector NormalImpulse, const FHitResult& Hit);

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

};
