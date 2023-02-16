#include "LevelManager.h"
#include "PlayerManager.h"
#include "TowerOfHanoiGameModeBase.h"
#include "Kismet/GameplayStatics.h"

ALevelManager::ALevelManager() {
	PrimaryActorTick.bCanEverTick = true;
}

void ALevelManager::BeginPlay() {
	Super::BeginPlay();

	// get the main game mode of the game
	GameMode = (ATowerOfHanoiGameModeBase*)UGameplayStatics::GetActorOfClass(GetWorld(), ATowerOfHanoiGameModeBase::StaticClass());
	bOnlyOnce = true;
}

void ALevelManager::Tick(float DeltaTime) {
	Super::Tick(DeltaTime);

	// check if the player has selected his/her log count
	// limit the spawn of logs so that it will not be infinite
	if(GameMode->LogCount > 0 && bOnlyOnce) {
		// get the main character actor
		PlayerManager = Cast<APlayerManager>(GetWorld()->SpawnActor<AActor>(MainCharacter, GetActorTransform()));

		// assign the designated tower
		PlayerManager->TowerOne = TowerOne;
		PlayerManager->TowerTwo = TowerTwo;
		PlayerManager->TowerThree = TowerThree;

		// spawn the log spawner to spawn logs
		GetWorld()->SpawnActor<AActor>(LogSpawner, LogSpawnerPos->GetActorTransform());

		// destroy the starting pawn
		StarterPawn->Destroy();
		bOnlyOnce = false;

		// destroy this class
		Destroy();
	}
}