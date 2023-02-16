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

	// declare an array to store the logs that the player has pick up
	// specified with its tower number
	UPROPERTY()
	TArray<ALogPickup*> TowerOneArray;

	UPROPERTY()
	TArray<ALogPickup*> TowerTwoArray;

	UPROPERTY()
	TArray<ALogPickup*> TowerThreeArray;

	// get the tower with its specific number
	UPROPERTY()
	class AActor* TowerOne;

	UPROPERTY()
	class AActor* TowerTwo;

	UPROPERTY()
	class AActor* TowerThree;

protected:
	virtual void BeginPlay() override;

	// create the main character's trigger
	UPROPERTY(VisibleAnywhere)
	class UCapsuleComponent* PlayerTrigger;

	// get the log blueprint that will be spawn
	UPROPERTY(EditAnywhere)
	TSubclassOf<AActor> LogToSpawn;

	// get the log class that will be spawn
	UPROPERTY(EditAnywhere)
	TSubclassOf<AActor> LogPickupToSpawn;

	// assign the run animation montage
	UPROPERTY(EditAnywhere)
	class UAnimMontage* AM_Run;

	// assign the idle animation montage
	UPROPERTY(EditAnywhere)
	class UAnimMontage* AM_Idle;

	// assign the niagara system portal effect
	UPROPERTY(EditAnywhere)
	class UNiagaraSystem* NS_Portal;

	// create a variable of actor that will be used in PlayerManager.cpp
	UPROPERTY()
	class AActor* CurrentLog;

	UPROPERTY()
	class AActor* LastActor;

	UPROPERTY()
	class AActor* NewLog;

	// create a variable of LogPickup that will be used in PlayerManager.cpp

	UPROPERTY()
	class ALogPickup* SmallestLog;
	
	UPROPERTY()
	class ALogPickup* Log;

	// get the main game mode
	UPROPERTY()
	class ATowerOfHanoiGameModeBase* GameMode;

	// declare the main anim instance of the player
	UPROPERTY()
	class UAnimInstance* AnimInstance;

	// declare a niagara component for the portal
	UPROPERTY()
	class UNiagaraComponent* NC_Portal;

	// this is where the collision and overlap of other actors with the player happens
	UFUNCTION()
	void PlayerOverlap(UPrimitiveComponent* HitComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);

	// create a function where the player is carrying or not carrying a log
	void IsNotCarrying(class ALogPickup* ALP);
	void IsCarrying(FVector TowerLocation);

	// declare a variable of fstring that wil lbe used in PlayerManager.cpp to optimize the text
	FString BiggerLogText;

	// declare the rotation off the current log
	FVector RotateLog;

	// check whether the player is carrying a log or not
	// check if the player has won the game
	bool bIsCarryingLog, bGameWon;

	// currentpos will be used to get the current position of the current held log
	// prevpos will be used to get the previous position of the previous held log
	// the rotation speed of the held log
	// check whether the current log count of the third yard (right yard) is equal to the log count that the player clicks on the instruction stage
	// portal timer is the timer to destroy the portal niagara effect
	float CurrentPos, PrevPos, RotateSpeed, CurrentLogCount, BiggerLogTimer, PortalTimer;

public:
	virtual void Tick(float DeltaTime) override;

	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

};
