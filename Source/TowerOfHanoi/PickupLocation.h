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

	UPROPERTY(VisibleAnywhere)
	class UBoxComponent* LocationTrigger;

	UPROPERTY(VisibleAnywhere)
	class UStaticMeshComponent* LocationMesh;

	UFUNCTION()
	void LocationInsideOverlap(UPrimitiveComponent* HitComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);

	UFUNCTION()
	void LocationOutsideOverlap(UPrimitiveComponent* HitComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex);

public:	
	virtual void Tick(float DeltaTime) override;

};
