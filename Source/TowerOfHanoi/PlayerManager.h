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

	UPROPERTY()
	class AActor* TowerOne;

	UPROPERTY()
	class AActor* TowerTwo;

	UPROPERTY()
	class AActor* TowerThree;

protected:
	virtual void BeginPlay() override;

	UPROPERTY(EditAnywhere)
	class AActor* MySequence;

	class ALevelSequenceActor* ALS;

	UPROPERTY(VisibleAnywhere)
	class UCapsuleComponent* PlayerTrigger;

	UPROPERTY(EditAnywhere)
	TSubclassOf<AActor> LogToSpawn;

	UPROPERTY(EditAnywhere)
	TSubclassOf<AActor> LogPickupToSpawn;

	UPROPERTY(EditAnywhere)
	class UAnimMontage* AM_Run;

	UPROPERTY(EditAnywhere)
	class UAnimMontage* AM_Idle;

	UPROPERTY(EditAnywhere)
	class UNiagaraSystem* NS_Portal;

	UPROPERTY()
	class AActor* CurrentLog;

	UPROPERTY()
	class AActor* LastActor;

	UPROPERTY()
	class AActor* NewLog;

	UPROPERTY()
	class ALogPickup* SmallestLog;
	
	UPROPERTY()
	class ALogPickup* Log;

	UPROPERTY()
	class ATowerOfHanoiGameModeBase* GameMode;

	UPROPERTY()
	class UAnimInstance* AnimInstance;

	UPROPERTY()
	class UNiagaraComponent* NC_Portal;

	UFUNCTION()
	void PlayerOverlap(UPrimitiveComponent* HitComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);

	void IsNotCarrying(class ALogPickup* ALP);
	void IsCarrying(FVector TowerLocation);

	FString BiggerLogText;
	FVector RotateLog;
	bool bIsCarryingLog, bGameWon;
	float CurrentPos, PrevPos, RotateSpeed, CurrentLogCount, BiggerLogTimer, PortalTimer;

public:
	virtual void Tick(float DeltaTime) override;

	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

};
