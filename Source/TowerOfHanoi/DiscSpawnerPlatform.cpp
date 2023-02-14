#include "DiscSpawnerPlatform.h"
#include "Components/BoxComponent.h"

ADiscSpawnerPlatform::ADiscSpawnerPlatform() {
	PrimaryActorTick.bCanEverTick = true;

	DiscPlatformTrigger = CreateDefaultSubobject<UBoxComponent>(TEXT("Disc Platform Trigger"));
	DiscPlatformTrigger->SetCollisionProfileName(TEXT("OverlapAll"));
	DiscPlatformTrigger->SetGenerateOverlapEvents(true);
	DiscPlatformTrigger->OnComponentBeginOverlap.AddDynamic(this, &ADiscSpawnerPlatform::DiscPlatformOverlap);
	RootComponent = DiscPlatformTrigger;
}

void ADiscSpawnerPlatform::BeginPlay() {
	Super::BeginPlay();
}

void ADiscSpawnerPlatform::Tick(float DeltaTime) {
	Super::Tick(DeltaTime);
}

void ADiscSpawnerPlatform::DiscPlatformOverlap(UPrimitiveComponent* HitComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult) {
	UE_LOG(LogTemp, Warning, TEXT("SDADSA"));
}