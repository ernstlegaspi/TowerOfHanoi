#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "LogPickup.generated.h"

UCLASS()
class TOWEROFHANOI_API ALogPickup : public AActor {
	GENERATED_BODY()
	
public:	
	ALogPickup();

	// declare a public variable that will be use in determining on what position of the log will be
	// plays a vital role in determining the size of the log
	float Pos;

protected:
	virtual void BeginPlay() override;

	UPROPERTY(VisibleAnywhere)
	class UStaticMeshComponent* LogMesh;

public:	
	virtual void Tick(float DeltaTime) override;

};