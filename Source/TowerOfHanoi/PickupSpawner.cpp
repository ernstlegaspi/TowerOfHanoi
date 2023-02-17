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

	// assign to fvector zero as a defualt value
	DecreaseScale = FVector(0, 0, 0);

	// get the main game mode
	GameMode = (ATowerOfHanoiGameModeBase*)UGameplayStatics::GetActorOfClass(GetWorld(), ATowerOfHanoiGameModeBase::StaticClass());

	// get the main character
	Player = (APlayerManager*)UGameplayStatics::GetActorOfClass(GetWorld(), APlayerManager::StaticClass());

	// assign the log count that the player has picked in the instruction stage
	LogCount = GameMode->LogCount;
	SpawnTimer = 0.f;
}

void APickupSpawner::Tick(float DeltaTime) {
	Super::Tick(DeltaTime);

	if(LogCount > 0.f) {
		SpawnTimer -= DeltaTime;

		if(SpawnTimer <= 0.f) {
			// assign the spawned log to an actor variable
			ALog = GetWorld()->SpawnActor<AActor>(LogToSpawn, GetActorTransform());

			// set the scale of the spawn log
			// the scale of the log is decreasing per spawn
			ALog->SetActorScale3D(FVector(.65, .65, .65) - DecreaseScale);

			// the variable used to decrease the scale of the log
			DecreaseScale += FVector(.05, .05, .05);

			// assign the position of the spawned log by descending order (8 is the biggest log and n is the smallest log)
			Log = Cast<ALogPickup>(ALog);
			Log->Pos = LogCount--;

			// insert the logs to an array
			Player->TowerOneArray.Emplace(Log);
			SpawnTimer = 1.f;
		}
	}
}