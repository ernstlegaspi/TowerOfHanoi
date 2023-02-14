// Fill out your copyright notice in the Description page of Project Settings.


#include "DiscActor.h"

// Sets default values
ADiscActor::ADiscActor()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

// Called when the game starts or when spawned
void ADiscActor::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void ADiscActor::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

