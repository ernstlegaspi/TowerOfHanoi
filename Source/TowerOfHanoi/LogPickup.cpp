#include "LogPickup.h"

ALogPickup::ALogPickup() {
	PrimaryActorTick.bCanEverTick = true;

	// create a new static mesh
	LogMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Log Mesh"));

	// assign it as a root component
	RootComponent = LogMesh;
}

void ALogPickup::BeginPlay() {
	Super::BeginPlay();
}

void ALogPickup::Tick(float DeltaTime) {
	Super::Tick(DeltaTime);
}