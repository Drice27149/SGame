// Fill out your copyright notice in the Description page of Project Settings.


#include "BaseObject.h"
#include "SBaseCharacter.h"

// Sets default values
ABaseObject::ABaseObject()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	CollisionComp = CreateDefaultSubobject<USphereComponent>(TEXT("MyCollisionComponent"));
	RootComponent = CollisionComp;
	PickUpComp = CreateDefaultSubobject<USphereComponent>(TEXT("MyPickUpComponent"));
	PickUpComp->SetupAttachment(RootComponent);
	MeshComp = CreateDefaultSubobject<USkeletalMeshComponent>(TEXT("MyMesh"));
	MeshComp->SetupAttachment(RootComponent);

	bUsing = false;
}

void ABaseObject::OnPickUp(ASBaseCharacter* OwnerCharacter)
{
	if (!bUsing)
	{
		bUsing = true;
		MyOwner = OwnerCharacter;
	}
}

// Called when the game starts or when spawned
void ABaseObject::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void ABaseObject::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

