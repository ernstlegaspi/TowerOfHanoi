#include "LogPickup.h"

ALogPickup::ALogPickup() {
	PrimaryActorTick.bCanEverTick = true;

	LogMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Log Mesh"));
	RootComponent = LogMesh;
}

void ALogPickup::BeginPlay() {
	Super::BeginPlay();
}

void ALogPickup::Tick(float DeltaTime) {
	Super::Tick(DeltaTime);
}