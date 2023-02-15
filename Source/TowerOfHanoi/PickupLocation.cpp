#include "PickupLocation.h"
#include "Components/BoxComponent.h"

APickupLocation::APickupLocation() {
	PrimaryActorTick.bCanEverTick = true;

	LocationTrigger = CreateDefaultSubobject<UBoxComponent>(TEXT("Location Trigger"));
	LocationTrigger->SetCollisionProfileName(TEXT("OverlapAll"));
	LocationTrigger->SetGenerateOverlapEvents(true);
	RootComponent = LocationTrigger;

	LocationMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Location Mesh"));
	LocationMesh->SetupAttachment(LocationTrigger);
}

void APickupLocation::BeginPlay() {
	Super::BeginPlay();

	LocationTrigger->OnComponentBeginOverlap.AddDynamic(this, &APickupLocation::LocationInsideOverlap);
	LocationTrigger->OnComponentEndOverlap.AddDynamic(this, &APickupLocation::LocationOutsideOverlap);
}

void APickupLocation::Tick(float DeltaTime) {
	Super::Tick(DeltaTime);
}

void APickupLocation::LocationInsideOverlap(UPrimitiveComponent* HitComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult) {

}

void APickupLocation::LocationOutsideOverlap(UPrimitiveComponent* HitComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex) {

}