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

	UPROPERTY(EditAnywhere)
	class AActor* StarterPawn;

	UPROPERTY(EditAnywhere)
	class AActor* LogSpawnerPos;

	UPROPERTY(EditAnywhere)
	class AActor* TowerOne;

	UPROPERTY(EditAnywhere)
	class AActor* TowerTwo;

	UPROPERTY(EditAnywhere)
	class AActor* TowerThree;

	UPROPERTY(EditAnywhere)
	TSubclassOf<AActor> MainCharacter;

	UPROPERTY(EditAnywhere)
	TSubclassOf<AActor> LogSpawner;

	UPROPERTY()
	class ATowerOfHanoiGameModeBase* GameMode;

	UPROPERTY()
	class APlayerManager* PlayerManager;

	bool bOnlyOnce;

public:	
	virtual void Tick(float DeltaTime) override;

};
