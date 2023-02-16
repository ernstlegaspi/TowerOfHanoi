#include "LevelManager.h"
#include "PlayerManager.h"
#include "TowerOfHanoiGameModeBase.h"
#include "Kismet/GameplayStatics.h"

ALevelManager::ALevelManager() {
	PrimaryActorTick.bCanEverTick = true;
}

void ALevelManager::BeginPlay() {
	Super::BeginPlay();

	GameMode = (ATowerOfHanoiGameModeBase*)UGameplayStatics::GetActorOfClass(GetWorld(), ATowerOfHanoiGameModeBase::StaticClass());
	bOnlyOnce = true;
}

void ALevelManager::Tick(float DeltaTime) {
	Super::Tick(DeltaTime);

	if(GameMode->LogCount > 0 && bOnlyOnce) {
		PlayerManager = Cast<APlayerManager>(GetWorld()->SpawnActor<AActor>(MainCharacter, GetActorTransform()));
		PlayerManager->TowerOne = TowerOne;
		PlayerManager->TowerTwo = TowerTwo;
		PlayerManager->TowerThree = TowerThree;
		GetWorld()->SpawnActor<AActor>(LogSpawner, LogSpawnerPos->GetActorTransform());
		StarterPawn->Destroy();
		bOnlyOnce = false;
		Destroy();
	}
}