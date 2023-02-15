#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "LogPickup.h"
#include "PlayerManager.generated.h"

UCLASS()
class TOWEROFHANOI_API APlayerManager : public ACharacter {
	GENERATED_BODY()

public:
	APlayerManager();

	UPROPERTY()
	TArray<ALogPickup*> TowerOneArray;

	UPROPERTY()
	TArray<ALogPickup*> TowerTwoArray;

	UPROPERTY()
	TArray<ALogPickup*> TowerThreeArray;

protected:
	virtual void BeginPlay() override;

	UPROPERTY(VisibleAnywhere)
	class UCapsuleComponent* PlayerTrigger;

	UPROPERTY(EditAnywhere)
	TSubclassOf<AActor> LogToSpawn;

	UPROPERTY(EditAnywhere)
	TSubclassOf<AActor> LogPickupToSpawn;

	UPROPERTY(EditAnywhere)
	class AActor* TowerOne;

	UPROPERTY(EditAnywhere)
	class AActor* TowerTwo;

	UPROPERTY(EditAnywhere)
	class AActor* TowerThree;

	UPROPERTY()
	class AActor* LastActor;

	UPROPERTY()
	class AActor* CurrentLog;

	UPROPERTY()
	class AActor* NewLog;

	UPROPERTY()
	class ALogPickup* SmallestLog;
	
	UPROPERTY()
	class ALogPickup* Log;

	UFUNCTION()
	void PlayerOverlap(UPrimitiveComponent* HitComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);

	void IsNotCarrying(class ALogPickup* ALP);
	void IsCarrying(FVector TowerLocation);

	FVector RotateLog;
	bool bIsCarryingLog;
	float CurrentPos, PrevPos, RotateSpeed, CurrentLogCount;

public:
	virtual void Tick(float DeltaTime) override;

	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

};
