// Fill out your copyright notice in the Description page of Project Settings.


#include "SRifle.h"
#include "SBaseCharacter.h"

void ASRifle::CriticalArt()
{
	if (MyOwner)
	{
		MyOwner->PlayMyMontage(CAMontage);
	}
}

void ASRifle::CriticalArtTick()
{
	UWorld* MyWorld = GetWorld();
	if (MyWorld)
	{
		FVector StartLocation = MeshComp->GetSocketLocation("BulletSocket");
		FVector ShootVector = MeshComp->GetSocketRotation("BulletSocket").Vector();
		ShootVector.Normalize();
		FVector EndLocation = StartLocation + 10000.0f * ShootVector;
		TArray<FHitResult> MyHitResults;
		if (MyWorld->LineTraceMultiByChannel(MyHitResults, StartLocation, EndLocation, ECC_Camera))
		{
			for (FHitResult MyHitResult : MyHitResults)
			{
				ASBaseCharacter* OtherCharacter = Cast<ASBaseCharacter>(MyHitResult.GetActor());
				if (OtherCharacter)
				{
					FTakeHitInfo MyHitInfo;
					MyHitInfo.damage = 100.0f;
					MyHitInfo.Sender = MyOwner;
					MyHitInfo.TakeHitMontage = nullptr;
					OtherCharacter->TakeHit(MyHitInfo);
				}
			}
		}
	}
}

void ASRifle::OnAttack()
{
	if (bBusy) return;
	Super::OnAttack();

	FTransform StartTransform = MeshComp->GetSocketTransform("BulletSocket");
	if (RifleBulletClass)
	{
		ASRifleBullet* MyBullet = Cast<ASRifleBullet>(UGameplayStatics::BeginDeferredActorSpawnFromClass(this, RifleBulletClass, StartTransform));
		if (MyBullet)
		{
			MyBullet->SetInstigator(MyOwner);
			UGameplayStatics::FinishSpawningActor(MyBullet, StartTransform);
		}
	}
}

