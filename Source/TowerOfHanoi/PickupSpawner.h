#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "PickupSpawner.generated.h"

UCLASS()
class TOWEROFHANOI_API APickupSpawner : public AActor {
	GENERATED_BODY()
	
public:	
	APickupSpawner();

protected:
	virtual void BeginPlay() override;

	// assign the log to spawn blueprint
	UPROPERTY(EditAnywhere)
	TSubclassOf<AActor> LogToSpawn;

	// create a logpickup variable to hold the cast variable and access its content
	UPROPERTY()
	class ALogPickup* Log;

	// create a actor variable to hold the spawned log
	UPROPERTY()
	class AActor* ALog;

	// get the player to get its array
	UPROPERTY()
	class APlayerManager* Player;

	// get the main game mode
	UPROPERTY()
	class ATowerOfHanoiGameModeBase* GameMode;

	FVector DecreaseScale;
	float LogCount, SpawnTimer;

public:	
	virtual void Tick(float DeltaTime) override;

};
