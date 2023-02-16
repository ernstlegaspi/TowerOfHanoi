#include "PlayerManager.h"
#include "TowerOfHanoiGameModeBase.h"
#include "Components/CapsuleComponent.h"
#include "Kismet/GameplayStatics.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "NiagaraComponent.h"
#include "NiagaraFunctionLibrary.h"

APlayerManager::APlayerManager() {
	PrimaryActorTick.bCanEverTick = true;

	bUseControllerRotationPitch = false;
	bUseControllerRotationYaw = false;
	bUseControllerRotationRoll = false;

	PlayerTrigger = CreateDefaultSubobject<UCapsuleComponent>(TEXT("Player Trigger"));
	PlayerTrigger->InitCapsuleSize(50.f, 50.f);
	PlayerTrigger->OnComponentBeginOverlap.AddDynamic(this, &APlayerManager::PlayerOverlap);
	PlayerTrigger->SetupAttachment(RootComponent);
}

void APlayerManager::BeginPlay() {
	Super::BeginPlay();

	GameMode = (ATowerOfHanoiGameModeBase*)UGameplayStatics::GetActorOfClass(GetWorld(), ATowerOfHanoiGameModeBase::StaticClass());
	RotateLog = FVector();
	LastActor = nullptr;
	NC_Portal = nullptr;
	RotateSpeed = 100.f;
	AnimInstance = GetMesh()->GetAnimInstance();
	BiggerLogTimer = 0.f;
	BiggerLogText = "The wood log you are holding is bigger than the last wood log in the yard.";
}

void APlayerManager::Tick(float DeltaTime) {
	Super::Tick(DeltaTime);

	// continuously rotate the current held log on top of player
	if(bIsCarryingLog && !bGameWon) {
		CurrentLog->SetActorLocation(FVector(GetActorLocation().X, GetActorLocation().Y, CurrentLog->GetActorLocation().Z));
		CurrentLog->SetActorEnableCollision(false);
		RotateLog.X += DeltaTime * RotateSpeed;
		RotateLog.Y += DeltaTime * RotateSpeed;
		RotateLog.Z += DeltaTime * RotateSpeed;
		CurrentLog->SetActorRotation(FRotator(RotateLog.X, RotateLog.Y, RotateLog.Z));
	}

	// check if the character is on ground
	if(GetCharacterMovement()->IsMovingOnGround()) {
		// check if the character is moving
		if(GetVelocity() != FVector(0, 0, 0)) {
			// check if the current idle animation is playing, if so, stop it and play the run animation
			if(AnimInstance->Montage_IsPlaying(AM_Idle)) AnimInstance->Montage_Stop(.5f, AM_Idle);
			if(!AnimInstance->Montage_IsPlaying(AM_Run)) AnimInstance->Montage_Play(AM_Run);
		}
		else {
			// check if the current run animation is playing, if so, stop it and play the idle animation
			if(AnimInstance->Montage_IsPlaying(AM_Run)) AnimInstance->Montage_Stop(.5f, AM_Run);
			if(!AnimInstance->Montage_IsPlaying(AM_Idle)) AnimInstance->Montage_Play(AM_Idle);
		}
	}

	// check if the guide of bigger log text is created and count down to destroy it
	if(GameMode->BiggerLogText != "") {
		BiggerLogTimer -= DeltaTime;

		if(BiggerLogTimer <= 0.1f) GameMode->BiggerLogText = "";
	}

	// check if the portal is created and count down to destroy it
	if(NC_Portal != nullptr) {
		PortalTimer -= DeltaTime;

		if(PortalTimer <= 0.f) {
			NC_Portal->DestroyInstance();
			NC_Portal = nullptr;
		}
	}

	if(bGameWon) GetCharacterMovement()->MaxWalkSpeed = 0.f;
}

void APlayerManager::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent) {
	Super::SetupPlayerInputComponent(PlayerInputComponent);
}

void APlayerManager::PlayerOverlap(UPrimitiveComponent* HitComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult) {
	// check if the player has won the game yet
	// if the player has won the game, other features of the game will be paused
	if(!bGameWon) {

		// check if the player has entered/overlap a PickupLocation actor
		if(OtherActor->GetName().Contains("PickupLocation")) {
			// get the position of the pickuplocation
			// 1 means the towerone
			if(OtherActor->GetName().Contains("_1")) {

				// check if the player is carrying a log
				if(bIsCarryingLog) {

					// check if the current yard has a log in it or is it not empty
					if(TowerOneArray.Num() > 0) {

						// check whether the current held log is bigger than the one that is inside the specific yard
						if(CurrentPos > TowerOneArray[TowerOneArray.Num() - 1]->Pos) {
							
							// notify the player that the current log is bigger
							GameMode->BiggerLogText = BiggerLogText;
							BiggerLogTimer = 3.f;
						}
						else {
							// place the current held log if it is smaller than the existing log inside
							IsCarrying(TowerOne->GetActorLocation());

							//insert it into the array to help in comparing the position of the logs
							TowerOneArray.Emplace(Log);
						}
					}
					else {
						// place the current held log if it is smaller than the existing log inside
						IsCarrying(TowerOne->GetActorLocation());

						//insert it into the array to help in comparing the position of the logs
						TowerOneArray.Emplace(Log);
					}
				}
				else {
					if(TowerOneArray.Num() > 0) {
						// place the current log on the specific yard
						IsNotCarrying(TowerOneArray[TowerOneArray.Num() - 1]);

						//insert it into the array to help in comparing the position of the logs
						TowerOneArray.SetNum(TowerOneArray.Num() - 1);
					}
				}
			}
			else if(OtherActor->GetName().Contains("_2")) { // 2 means the tower two
				if(bIsCarryingLog) {
					if(TowerTwoArray.Num() > 0) {
						if(CurrentPos > TowerTwoArray[TowerTwoArray.Num() - 1]->Pos) {
							GameMode->BiggerLogText = BiggerLogText;
							BiggerLogTimer = 3.f;
						}
						else {
							IsCarrying(TowerTwo->GetActorLocation());
							TowerTwoArray.Emplace(Log);
						}
					}
					else {
						IsCarrying(TowerTwo->GetActorLocation());
						TowerTwoArray.Emplace(Log);
					}
				}
				else {
					if(TowerTwoArray.Num() > 0) {
						IsNotCarrying(TowerTwoArray[TowerTwoArray.Num() - 1]);
						TowerTwoArray.SetNum(TowerTwoArray.Num() - 1);
					}
				}
			}
			else { // last is the tower three
				if(bIsCarryingLog) {
					if(TowerThreeArray.Num() > 0) {
						if(CurrentPos > TowerThreeArray[TowerThreeArray.Num() - 1]->Pos) {
							GameMode->BiggerLogText = BiggerLogText;
							BiggerLogTimer = 3.f;
						}
						else {
							IsCarrying(TowerThree->GetActorLocation());
							TowerThreeArray.Emplace(Log);

							// count the log that is correctly placed on the third tower (third yard)
							CurrentLogCount++;
						}
					}
					else {
						IsCarrying(TowerThree->GetActorLocation());
						TowerThreeArray.Emplace(Log);

						// count the log that is correctly placed on the third tower (third yard)
						CurrentLogCount++;
					}
				}
				else {
					if(TowerThreeArray.Num() > 0) {
						IsNotCarrying(TowerThreeArray[TowerThreeArray.Num() - 1]);
						// decrement the log count if the player gets a log in the third tower (third yard)
						CurrentLogCount--;
						TowerThreeArray.SetNum(TowerThreeArray.Num() - 1);
					}
				}

				// check if all the logs are correctly place in the third tower (third yard) and compare to the log count that the player has click in the instruction stage
				if(CurrentLogCount == GameMode->LogCount) {
					// get the player controller
					GameMode->bFinishGame = true;
					bGameWon = true;
					// pause the game if the player has completed the puzzle
				}
			}
		}
	}
}

void APlayerManager::IsNotCarrying(class ALogPickup* ALP) {
	// get the smallest log in the yard
	SmallestLog = ALP;
	CurrentPos = SmallestLog->Pos;
	LastActor = Cast<AActor>(SmallestLog);

	// spawn a new actor of log and set its scale and location
	CurrentLog = GetWorld()->SpawnActor<AActor>(LogToSpawn, GetActorTransform());
	CurrentLog->SetActorScale3D(LastActor->GetActorScale3D());
	CurrentLog->SetActorLocation(GetActorLocation() + FVector(0, 0, 400));

	// destroy the current log that the player got in the yard
	LastActor->Destroy();

	// set the carrying log to true if the player is helding a log
	bIsCarryingLog = true;

	// set the bigger log text to empty string
	GameMode->BiggerLogText = "";

	// set the timer of the bigger log text so that it will be removed if the timer reached to 0
	BiggerLogTimer = 0.f;
}

void APlayerManager::IsCarrying(FVector TowerLocation) {
	// spawn a new actor of log and set the scale and location of it
	NewLog = GetWorld()->SpawnActor<AActor>(LogPickupToSpawn, GetActorTransform());
	NewLog->SetActorScale3D(CurrentLog->GetActorScale3D());
	NewLog->SetActorLocation(TowerLocation);

	// cast the newly created log to a log pickup class
	Log = Cast<ALogPickup>(NewLog);
	Log->Pos = CurrentPos;

	// timer of portal on when the portal will be destroyed
	PortalTimer = 1.f;

	// create a portal niagara effect on where the log will spawn
	NC_Portal = UNiagaraFunctionLibrary::SpawnSystemAtLocation(GetWorld(), NS_Portal, TowerLocation);

	// destroy the current held log
	CurrentLog->Destroy();

	// set the carrying log to false if the player has placed the current log into a specific yard
	bIsCarryingLog = false;

	// set the bigger log text to empty string
	GameMode->BiggerLogText = "";

	// set the timer of the bigger log text so that it will be removed if the timer reached to 0
	BiggerLogTimer = 0.f;
	GameMode->MovesCount++;
}