#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "DiscSpawner.generated.h"

UCLASS()
class TOWEROFHANOI_API ADiscSpawner : public AActor {
	GENERATED_BODY()
	
public:	
	ADiscSpawner();

protected:
	virtual void BeginPlay() override;

public:	
	virtual void Tick(float DeltaTime) override;

};
