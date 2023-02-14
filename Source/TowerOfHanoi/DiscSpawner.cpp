// Fill out your copyright notice in the Description page of Project Settings.


#include "DiscSpawner.h"

// Sets default values
ADiscSpawner::ADiscSpawner()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

// Called when the game starts or when spawned
void ADiscSpawner::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void ADiscSpawner::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

