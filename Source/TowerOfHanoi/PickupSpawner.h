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

	UPROPERTY(EditAnywhere)
	TSubclassOf<AActor> LogToSpawn;

	UPROPERTY()
	class ALogPickup* Log;

	UPROPERTY()
	class AActor* ALog;

	UPROPERTY()
	class APlayerManager* Player;

	UPROPERTY()
	class ATowerOfHanoiGameModeBase* GameMode;

	FVector DecreaseScale;
	float LogCount;

public:	
	virtual void Tick(float DeltaTime) override;

};
