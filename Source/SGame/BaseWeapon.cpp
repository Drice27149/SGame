// Fill out your copyright notice in the Description page of Project Settings.


#include "BaseWeapon.h"
#include "SBaseCharacter.h"

// Sets default values
ABaseWeapon::ABaseWeapon()
{
	bBusy = false;
}

// Called when the game starts or when spawned
void ABaseWeapon::BeginPlay()
{
	Super::BeginPlay();
}

void ABaseWeapon::CriticalArt()
{
	
}

void ABaseWeapon::CriticalArtTick()
{

}

void ABaseWeapon::RefreshWeapon()
{
	bBusy = false;
}

void ABaseWeapon::OnAttack()
{
	bBusy = true;
	FTimerManager& MyTimerManager = GetWorldTimerManager();
	MyTimerManager.SetTimer(CooldownTimer, this,  &ABaseWeapon::RefreshWeapon, CoolDownTime, false);
}

void ABaseWeapon::OnPickUp(ASBaseCharacter* OwnerCharacter)
{
	if (!bUsing)
	{
		bBusy = false;
		Super::OnPickUp(OwnerCharacter);
		OwnerCharacter->AddWeapon(this);
		OnAttachPlace();
	}
}

void ABaseWeapon::OnAttachUse()
{
	DetachFromActor(FDetachmentTransformRules::KeepWorldTransform);
	AttachToComponent(MyOwner->GetMesh(), FAttachmentTransformRules::SnapToTargetNotIncludingScale, UseSocket);
}

void ABaseWeapon::OnAttachPlace()
{
	DetachFromActor(FDetachmentTransformRules::KeepWorldTransform);
	AttachToComponent(MyOwner->GetMesh(), FAttachmentTransformRules::SnapToTargetNotIncludingScale, PlaceSocket);
}

void ABaseWeapon::OnThrow()
{
	bUsing = false;
	MyOwner = nullptr;
	DetachFromActor(FDetachmentTransformRules::KeepWorldTransform);
}

SWeaponType ABaseWeapon::GetWeaponType()
{
	return MyWeaponType;
}