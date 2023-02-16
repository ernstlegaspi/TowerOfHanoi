#include "PickupLocation.h"
#include "Components/BoxComponent.h"

APickupLocation::APickupLocation() {
	PrimaryActorTick.bCanEverTick = true;

	// create a pickup location trigger for the player to step on
	LocationTrigger = CreateDefaultSubobject<UBoxComponent>(TEXT("Location Trigger"));

	// set the collision to overlap all
	LocationTrigger->SetCollisionProfileName(TEXT("OverlapAll"));
	LocationTrigger->SetGenerateOverlapEvents(true);
	RootComponent = LocationTrigger;

	// create a pickup location mesh
	LocationMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Location Mesh"));

	// attach it to the root component, the location trigger
	LocationMesh->SetupAttachment(LocationTrigger);
}

void APickupLocation::BeginPlay() {
	Super::BeginPlay();
}

void APickupLocation::Tick(float DeltaTime) {
	Super::Tick(DeltaTime);
}