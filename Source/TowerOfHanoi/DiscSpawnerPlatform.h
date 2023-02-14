#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "DiscSpawnerPlatform.generated.h"

UCLASS()
class TOWEROFHANOI_API ADiscSpawnerPlatform : public AActor {
	GENERATED_BODY()
	
public:	
	ADiscSpawnerPlatform();

	bool bInPlatform;

protected:
	virtual void BeginPlay() override;

	UPROPERTY()
	class UBoxComponent* DiscPlatformTrigger;

	UPROPERTY()
	class UStaticMeshComponent* DiscPlatformMesh;

	UFUNCTION()
	void DiscPlatformInsideOverlap(UPrimitiveComponent* HitComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);

	UFUNCTION()
	void DiscPlatformOutsideOverlap(UPrimitiveComponent* HitComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex);

public:	
	virtual void Tick(float DeltaTime) override;

};