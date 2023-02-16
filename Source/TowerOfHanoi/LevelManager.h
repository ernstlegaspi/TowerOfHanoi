#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "LevelManager.generated.h"

UCLASS()
class TOWEROFHANOI_API ALevelManager : public AActor {
	GENERATED_BODY()
	
public:	
	ALevelManager();

protected:
	virtual void BeginPlay() override;

	// assign the starterpawn that views the scene
	// will be destroyed later if the player has finish pick on how many log will he/she play
	UPROPERTY(EditAnywhere)
	class AActor* StarterPawn;

	// assign the log spawner position
	UPROPERTY(EditAnywhere)
	class AActor* LogSpawnerPos;

	// assign the tower one
	UPROPERTY(EditAnywhere)
	class AActor* TowerOne;

	// assign the tower two
	UPROPERTY(EditAnywhere)
	class AActor* TowerTwo;

	// assign the tower three
	UPROPERTY(EditAnywhere)
	class AActor* TowerThree;

	// assign the main character of the game
	// can start playing this character if the player is finished picking on how many log counts
	UPROPERTY(EditAnywhere)
	TSubclassOf<AActor> MainCharacter;

	// assign the log spawner
	// this is where the starting logs will spawn
	UPROPERTY(EditAnywhere)
	TSubclassOf<AActor> LogSpawner;

	// declare the main game mode
	UPROPERTY()
	class ATowerOfHanoiGameModeBase* GameMode;

	// declare a playermanager actor to get its variables
	UPROPERTY()
	class APlayerManager* PlayerManager;

	// declare a boolean variable so that the starting spawn of log will not be infinite
	bool bOnlyOnce;

public:	
	virtual void Tick(float DeltaTime) override;

};
