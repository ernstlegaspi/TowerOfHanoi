#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "LogPickup.generated.h"

UCLASS()
class TOWEROFHANOI_API ALogPickup : public AActor {
	GENERATED_BODY()
	
public:	
	ALogPickup();

	float Pos;

protected:
	virtual void BeginPlay() override;

	UPROPERTY(VisibleAnywhere)
	class UStaticMeshComponent* LogMesh;

public:	
	virtual void Tick(float DeltaTime) override;

};