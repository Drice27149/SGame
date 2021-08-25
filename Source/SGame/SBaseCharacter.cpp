// Fill out your copyright notice in the Description page of Project Settings.


#include "SBaseCharacter.h"
#include "SCharacterMovementComponent.h"

// Sets default values
ASBaseCharacter::ASBaseCharacter()
{
	PrimaryActorTick.bCanEverTick = true;

	MaxHealth = 100.0f;
	MyHealth = MaxHealth;
	LastHitTime = 0.0f;
	CACount = 5;
}

// Called when the game starts or when spawned
void ASBaseCharacter::BeginPlay()
{
	Super::BeginPlay();
}

ABaseWeapon* ASBaseCharacter::GetCurrentWeapon()
{
	if (WeaponIndex != -1 && MyWeapons.Num() > 0)
	{
		return MyWeapons[WeaponIndex % MyWeapons.Num()];
	}
	else
	{
		return nullptr;
	}
}

void ASBaseCharacter::CriticalArt()
{
	if (CACount > 0)
	{
		CACount--;
		ABaseWeapon* MyWeapon = ASBaseCharacter::GetCurrentWeapon();
		MyWeapon->CriticalArt();
	}
}

float ASBaseCharacter::GetHealth()
{
	return MyHealth;
}

ASSword* ASBaseCharacter::GetMySword()
{
	if (WeaponIndex != -1 && MyWeapons.Num() > 0)
	{
		ASSword* MySword = Cast<ASSword>(MyWeapons[WeaponIndex % MyWeapons.Num()]);
		if (MySword)
		{
			return MySword;
		}
		else
		{
			return nullptr;
		}
	}
	else
	{
		return nullptr;
	}
}

void ASBaseCharacter::OnDeath()
{
	SetLifeSpan(5.0f);
}

void ASBaseCharacter::OnAttack()
{
	if (WeaponIndex != -1 && MyWeapons.Num() != 0)
	{
		MyWeapons[WeaponIndex % MyWeapons.Num()]->OnAttack();
	}
}

void ASBaseCharacter::TakeHit(FTakeHitInfo MyHitInfo)
{
	if (MyHealth <= 0) return;
	UWorld* MyWorld = GetWorld();
	if (MyWorld)
	{
		float CurrentTime = MyWorld->GetTimeSeconds();
		if (CurrentTime - LastHitTime > 0.2f)
		{
			LastHitTime = CurrentTime;
			MyHealth -= MyHitInfo.damage;
			if (MyHealth <= 0)
			{
				OnDeath();
				return ;
			}
			if (MyHitInfo.TakeHitMontage)
			{
				ASBaseCharacter::PlayMyMontage(MyHitInfo.TakeHitMontage);
			}
		}
	}
}

void ASBaseCharacter::PlayMyMontage(UAnimMontage* CurrentMontage)
{
	if (CurrentMontage && GetMesh() && GetMesh()->AnimScriptInstance)
	{
		GetMesh()->AnimScriptInstance->Montage_Play(CurrentMontage);
	}
}

void ASBaseCharacter::NextWeapon()
{
	PlayMyMontage(WeaponChangeMontage);
}

SWeaponType ASBaseCharacter::GetCurrentWeaponType()
{
	if (WeaponIndex != -1)
	{
		return MyWeapons[WeaponIndex]->GetWeaponType();
	}
	else
	{
		return SWeaponType::SEmpty;
	}
}

ABaseObject* ASBaseCharacter::DetectPickUp()
{
	// the object that trace and found
	ABaseObject* FoundObject = nullptr;

	FVector StartPostion = GetMesh()->GetSocketLocation("PickUpStart");
	FVector EndPosition = GetMesh()->GetSocketLocation("PickUpEnd");
	UWorld* MyWorld = GetWorld();
	if (MyWorld)
	{
		FHitResult MyHitReuslt;
		bool isHit = MyWorld->LineTraceSingleByChannel(MyHitReuslt, StartPostion, EndPosition, ECC_Visibility);
		if (isHit)
		{
			FoundObject = Cast<ABaseObject>(MyHitReuslt.GetActor());
			if (FoundObject != nullptr && FoundObject->bUsing)
			{
				FoundObject = nullptr;
			}
		}
	}

	return FoundObject;
}

void ASBaseCharacter::ConfirmPickUp()
{
	if (LastPickUpObject && !LastPickUpObject->bUsing)
	{
		LastPickUpObject->OnPickUp(this);
	}
}

void ASBaseCharacter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	
	LastPickUpObject = DetectPickUp();
	ReportPickUp(LastPickUpObject != nullptr);
}

void ASBaseCharacter::AddWeapon(ABaseWeapon* NewWeapon)
{
	MyWeapons.Add(NewWeapon);
}

void ASBaseCharacter::ShiftWeapon()
{
	if (MyWeapons.Num() != 0)
	{	
		if (WeaponIndex != -1)
		{
			WeaponIndex = WeaponIndex % MyWeapons.Num();
			MyWeapons[WeaponIndex]->OnAttachPlace();
		}
		WeaponIndex = (WeaponIndex + 1) % MyWeapons.Num();
		MyWeapons[WeaponIndex]->OnAttachUse();
	}
}

void ASBaseCharacter::ThrowWeapon()
{
	if (WeaponIndex != -1)
	{
		MyWeapons[WeaponIndex]->OnAttachPlace();
		MyWeapons[WeaponIndex]->OnThrow();
		MyWeapons.RemoveAt(WeaponIndex);
		WeaponIndex = -1;
	}
}

void ASBaseCharacter::EnableCrouch()
{
	Crouch();
}

void ASBaseCharacter::UnableCrouch()
{
	UnCrouch();
}

// Camera and character movement, copy from third person template
void ASBaseCharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

	PlayerInputComponent->BindAction("PickUp", IE_Pressed, this, &ASBaseCharacter::ConfirmPickUp);
	PlayerInputComponent->BindAction("Attack", IE_Pressed, this, &ASBaseCharacter::OnAttack);
	PlayerInputComponent->BindAction("Throw", IE_Pressed, this, &ASBaseCharacter::ThrowWeapon);
	PlayerInputComponent->BindAction("Shift", IE_Pressed, this, &ASBaseCharacter::ShiftWeapon);
	PlayerInputComponent->BindAction("Crouch", IE_Pressed, this, &ASBaseCharacter::EnableCrouch);
	PlayerInputComponent->BindAction("Crouch", IE_Released, this, &ASBaseCharacter::UnableCrouch);
}
