#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "DiscSpawnerPlatform.generated.h"

UCLASS()
class TOWEROFHANOI_API ADiscSpawnerPlatform : public AActor {
	GENERATED_BODY()
	
public:	
	ADiscSpawnerPlatform();

protected:
	virtual void BeginPlay() override;

	UPROPERTY()
	class UBoxComponent* DiscPlatformTrigger;

	UPROPERTY()
	class UStaticMeshComponent* DiscPlatformMesh;

	UFUNCTION()
	void DiscPlatformOverlap(UPrimitiveComponent* HitComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);

public:	
	virtual void Tick(float DeltaTime) override;

};