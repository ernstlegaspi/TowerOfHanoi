#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "PickupLocation.generated.h"

UCLASS()
class TOWEROFHANOI_API APickupLocation : public AActor {
	GENERATED_BODY()
	
public:	
	APickupLocation();

protected:
	virtual void BeginPlay() override;

	// create a pickup location trigger for the player to step on
	UPROPERTY(VisibleAnywhere)
	class UBoxComponent* LocationTrigger;

	// create a pickup location mesh
	UPROPERTY(VisibleAnywhere)
	class UStaticMeshComponent* LocationMesh;

public:	
	virtual void Tick(float DeltaTime) override;

};
