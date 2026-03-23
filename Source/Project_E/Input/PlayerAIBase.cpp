// Fill out your copyright notice in the Description page of Project Settings.


#include "PlayerAIBase.h"
#include "Navigation/CrowdFollowingComponent.h"

// Sets default values
APlayerAIBase::APlayerAIBase(const FObjectInitializer& ObjectInitializer)
	: Super(ObjectInitializer.SetDefaultSubobjectClass<UCrowdFollowingComponent>(TEXT("PathFollowingComponent")))
{
	PrimaryActorTick.bCanEverTick = true;
}

// Called when the game starts or when spawned
void APlayerAIBase::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void APlayerAIBase::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

