#include "PickupSpawner.h"
#include "TowerOfHanoiGameModeBase.h"
#include "LogPickup.h"
#include "PlayerManager.h"
#include "Kismet/GameplayStatics.h"

APickupSpawner::APickupSpawner() {
	PrimaryActorTick.bCanEverTick = true;
}

void APickupSpawner::BeginPlay() {
	Super::BeginPlay();

	DecreaseScale = FVector(0, 0, 0);
	GameMode = (ATowerOfHanoiGameModeBase*)UGameplayStatics::GetActorOfClass(GetWorld(), ATowerOfHanoiGameModeBase::StaticClass());
	Player = (APlayerManager*)UGameplayStatics::GetActorOfClass(GetWorld(), APlayerManager::StaticClass());
	LogCount = GameMode->LogCount;
}

void APickupSpawner::Tick(float DeltaTime) {
	Super::Tick(DeltaTime);

	if(LogCount > 0.f) {
		ALog = GetWorld()->SpawnActor<AActor>(LogToSpawn, GetActorTransform());
		ALog->SetActorScale3D(FVector(.5, .5, .5) - DecreaseScale);
		DecreaseScale += FVector(.03, .03, .03);
		Log = Cast<ALogPickup>(ALog);
		Log->Pos = LogCount--;
		Player->TowerOneArray.Emplace(Log);
	}
}