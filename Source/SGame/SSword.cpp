// Fill out your copyright notice in the Description page of Project Settings.


#include "SSword.h"
#include "SBaseCharacter.h"

ASSword::ASSword()
{
	PrimaryActorTick.bCanEverTick = true;
	bSaveCombo = false;
}

void ASSword::SaveCombo()
{
	bSaveCombo = true;
}

void ASSword::RefreshCombo()
{
	bSaveCombo = false;
}

void ASSword::OnAttack()
{
	if (!bBusy)
	{
		Super::OnAttack();
		ASBaseCharacter* MyCharacter = Cast<ASBaseCharacter>(MyOwner);
		if (MyCharacter)
		{
			if (bSaveCombo)
			{
				MyCharacter->PlayMyMontage(SlashB);
			}
			else
			{
				MyCharacter->PlayMyMontage(SlashA);
			}
		}
	}
}

void ASSword::StartTrace()
{
	bTracing = true;
}

void ASSword::EndTrace()
{
	bTracing = false;
}

void ASSword::Tick(float DeltaTime)
{
	if (bTracing)
	{
		UWorld* MyWorld = GetWorld();
		if (MyWorld)
		{
			FHitResult MyHitResult;
			FVector StartLocation = MeshComp->GetSocketLocation("StartSocket");
			FVector EndLocation = MeshComp->GetSocketLocation("EndSocket");

			if (MyWorld->LineTraceSingleByChannel(MyHitResult, StartLocation, EndLocation, ECC_Camera))
			{
				ASBaseCharacter* OtherCharacter = Cast<ASBaseCharacter>(MyHitResult.GetActor());
				if (OtherCharacter && OtherCharacter != MyOwner)
				{
					FTakeHitInfo MyHitInfo;
					MyHitInfo.damage = 15.0f;
					MyHitInfo.Sender = MyOwner;
					MyHitInfo.TakeHitMontage = TakeHitMontage;
					OtherCharacter->TakeHit(MyHitInfo);
				}
			}
		}
	}
}