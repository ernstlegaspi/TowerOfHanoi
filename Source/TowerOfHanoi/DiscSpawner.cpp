#include "DiscSpawner.h"
ADiscSpawner::ADiscSpawner() {
	PrimaryActorTick.bCanEverTick = true;
}

void ADiscSpawner::BeginPlay() {
	Super::BeginPlay();
}

void ADiscSpawner::Tick(float DeltaTime) {
	Super::Tick(DeltaTime);
}