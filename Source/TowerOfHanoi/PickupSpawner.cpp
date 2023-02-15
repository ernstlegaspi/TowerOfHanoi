#include "PickupSpawner.h"
#include "LogPickup.h"
#include "PlayerManager.h"
#include "Kismet/GameplayStatics.h"

APickupSpawner::APickupSpawner() {
	PrimaryActorTick.bCanEverTick = true;
}

void APickupSpawner::BeginPlay() {
	Super::BeginPlay();

	PickupCount = 3.f;
	DecreaseScale = FVector(0, 0, 0);

	Player = (APlayerManager*)UGameplayStatics::GetActorOfClass(GetWorld(), APlayerManager::StaticClass());
}

void APickupSpawner::Tick(float DeltaTime) {
	Super::Tick(DeltaTime);

	if(PickupCount > 0.f) {
		ALog = GetWorld()->SpawnActor<AActor>(LogToSpawn, GetActorTransform());
		ALog->SetActorScale3D(FVector(1, 1, 1) - DecreaseScale);
		DecreaseScale += FVector(.2, .2, .2);
		Log = Cast<ALogPickup>(ALog);
		Log->Pos = PickupCount--;
		Player->TowerOneArray.Emplace(Log);
	}
}