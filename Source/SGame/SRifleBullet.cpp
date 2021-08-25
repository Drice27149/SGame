// Fill out your copyright notice in the Description page of Project Settings.


#include "SRifleBullet.h"
#include "SBaseCharacter.h"

// Sets default values
ASRifleBullet::ASRifleBullet()
{
	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	SphereCollisionComp = CreateDefaultSubobject<USphereComponent>(TEXT("MyCollisionComp"));
	RootComponent = SphereCollisionComp;
	ProjectileMovementComp = CreateDefaultSubobject<UProjectileMovementComponent>(TEXT("MyProjectileMovementComp"));
	ProjectileMovementComp->SetUpdatedComponent(RootComponent);
}

void ASRifleBullet::OnBulletImpact(UPrimitiveComponent* HitComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, FVector NormalImpulse, const FHitResult& Hit)
{
	ASBaseCharacter* OtherBaseCharacter = Cast<ASBaseCharacter>(OtherActor);
	if (OtherBaseCharacter)
	{
		UGameplayStatics::SpawnEmitterAtLocation(this, ExplosionEffect, GetActorLocation(), FRotator::ZeroRotator, true, EPSCPoolMethod::AutoRelease);
		FTakeHitInfo MyHitInfo;
		MyHitInfo.damage = 15.0;
		MyHitInfo.Sender = GetInstigator();
		MyHitInfo.TakeHitMontage = TakeHitMontage;
		OtherBaseCharacter->TakeHit(MyHitInfo);
	}
	Destroy();
}

// Called when the game starts or when spawned
void ASRifleBullet::BeginPlay()
{
	Super::BeginPlay();
	
	SphereCollisionComp->OnComponentHit.AddDynamic(this,&ASRifleBullet::OnBulletImpact);
}

// Called every frame
void ASRifleBullet::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

