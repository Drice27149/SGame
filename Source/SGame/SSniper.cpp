// Fill out your copyright notice in the Description page of Project Settings.


#include "SSniper.h"
#include "SBaseCharacter.h"

void ASSniper::OnAttack()
{
	if (bBusy) return;
	Super::OnAttack();

	FVector StartLocation = MeshComp->GetSocketLocation("BulletSocket");
	FVector ShootVector = MeshComp->GetSocketRotation("BulletSocket").Vector();
	ShootVector.Normalize();
	FVector EndLocation = StartLocation + 2000.0f * ShootVector;
	UWorld* MyWorld = GetWorld();
	if (MyWorld)
	{
		FHitResult MyHitResult;
		if (MyWorld->LineTraceSingleByChannel(MyHitResult, StartLocation, EndLocation, ECC_Camera))
		{
			UGameplayStatics::SpawnEmitterAtLocation(this, ExplosionEffect, MyHitResult.Location, FRotator::ZeroRotator, true, EPSCPoolMethod::AutoRelease);
			ASBaseCharacter* HitCharacter = Cast<ASBaseCharacter>(MyHitResult.GetActor());
			if (HitCharacter)
			{
				FTakeHitInfo MyHitInfo;
				MyHitInfo.damage = 30.0f;
				MyHitInfo.Sender = MyOwner;
				MyHitInfo.TakeHitMontage = TakeHitMontage;
				HitCharacter->TakeHit(MyHitInfo);
			}
		}
	}
}