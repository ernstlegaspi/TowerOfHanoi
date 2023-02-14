#include "DiscSpawnerPlatform.h"
#include "Components/BoxComponent.h"

ADiscSpawnerPlatform::ADiscSpawnerPlatform() {
	PrimaryActorTick.bCanEverTick = true;

	DiscPlatformTrigger = CreateDefaultSubobject<UBoxComponent>(TEXT("Disc Platform Trigger"));
	DiscPlatformTrigger->SetCollisionProfileName(TEXT("OverlapAll"));
	DiscPlatformTrigger->SetGenerateOverlapEvents(true);
	RootComponent = DiscPlatformTrigger;

	DiscPlatformMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Disc Platform Mesh"));
	DiscPlatformMesh->SetupAttachment(DiscPlatformTrigger);
}

void ADiscSpawnerPlatform::BeginPlay() {
	Super::BeginPlay();

	DiscPlatformTrigger->OnComponentBeginOverlap.AddDynamic(this, &ADiscSpawnerPlatform::DiscPlatformInsideOverlap);
	DiscPlatformTrigger->OnComponentEndOverlap.AddDynamic(this, &ADiscSpawnerPlatform::DiscPlatformOutsideOverlap);
}

void ADiscSpawnerPlatform::Tick(float DeltaTime) {
	Super::Tick(DeltaTime);
}

void ADiscSpawnerPlatform::DiscPlatformInsideOverlap(UPrimitiveComponent* HitComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult) {
	if(OtherActor->GetFName().ToString().Contains("PlayerManager")) bInPlatform = true;
}

void ADiscSpawnerPlatform::DiscPlatformOutsideOverlap(UPrimitiveComponent* HitComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex) {
	if(OtherActor->GetFName().ToString().Contains("PlayerManager")) bInPlatform = false;
}