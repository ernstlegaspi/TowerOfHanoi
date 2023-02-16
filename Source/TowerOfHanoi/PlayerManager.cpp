#include "PlayerManager.h"
#include "LevelSequence.h"
#include "LevelSequenceActor.h"
#include "LevelSequencePlayer.h"
#include "MovieScene.h"
#include "MovieSceneSequencePlayer.h"
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
	// ALS = Cast<ALevelSequenceActor>(MySequence);
	// ALS->SequencePlayer->Play();
}

void APlayerManager::Tick(float DeltaTime) {
	Super::Tick(DeltaTime);

	if(bIsCarryingLog) {
		CurrentLog->SetActorLocation(FVector(GetActorLocation().X, GetActorLocation().Y, CurrentLog->GetActorLocation().Z));
		CurrentLog->SetActorEnableCollision(false);
		RotateLog.X += DeltaTime * RotateSpeed;
		RotateLog.Y += DeltaTime * RotateSpeed;
		RotateLog.Z += DeltaTime * RotateSpeed;
		CurrentLog->SetActorRotation(FRotator(RotateLog.X, RotateLog.Y, RotateLog.Z));
	}

	if(GetCharacterMovement()->IsMovingOnGround()) {
		if(GetVelocity() != FVector(0, 0, 0)) {
			if(AnimInstance->Montage_IsPlaying(AM_Idle)) AnimInstance->Montage_Stop(.5f, AM_Idle);
			if(!AnimInstance->Montage_IsPlaying(AM_Run)) AnimInstance->Montage_Play(AM_Run);
		}
		else {
			if(AnimInstance->Montage_IsPlaying(AM_Run)) AnimInstance->Montage_Stop(.5f, AM_Run);
			if(!AnimInstance->Montage_IsPlaying(AM_Idle)) AnimInstance->Montage_Play(AM_Idle);
		}
	}

	if(GameMode->BiggerLogText != "") {
		BiggerLogTimer -= DeltaTime;

		if(BiggerLogTimer <= 0.1f) GameMode->BiggerLogText = "";
	}

	if(NC_Portal != nullptr) {
		PortalTimer -= DeltaTime;

		if(PortalTimer <= 0.f) {
			NC_Portal->DestroyInstance();
			NC_Portal = nullptr;
		}
	}
}

void APlayerManager::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent) {
	Super::SetupPlayerInputComponent(PlayerInputComponent);
}

void APlayerManager::PlayerOverlap(UPrimitiveComponent* HitComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult) {
	if(!bGameWon) {
		if(OtherActor->GetName().Contains("PickupLocation")) {
			if(OtherActor->GetName().Contains("_1")) {
				if(bIsCarryingLog) {
					if(TowerOneArray.Num() > 0) {
						if(CurrentPos > TowerOneArray[TowerOneArray.Num() - 1]->Pos) {
							GameMode->BiggerLogText = BiggerLogText;
							BiggerLogTimer = 3.f;
						}
						else {
							IsCarrying(TowerOne->GetActorLocation());
							TowerOneArray.Emplace(Log);
						}
					}
					else {
						IsCarrying(TowerOne->GetActorLocation());
						TowerOneArray.Emplace(Log);
					}
				}
				else {
					if(TowerOneArray.Num() > 0) {
						IsNotCarrying(TowerOneArray[TowerOneArray.Num() - 1]);
						TowerOneArray.SetNum(TowerOneArray.Num() - 1);
					}
				}
			}
			else if(OtherActor->GetName().Contains("_2")) {
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
			else {
				if(bIsCarryingLog) {
					if(TowerThreeArray.Num() > 0) {
						if(CurrentPos > TowerThreeArray[TowerThreeArray.Num() - 1]->Pos) {
							GameMode->BiggerLogText = BiggerLogText;
							BiggerLogTimer = 3.f;
						}
						else {
							IsCarrying(TowerThree->GetActorLocation());
							TowerThreeArray.Emplace(Log);
							CurrentLogCount++;
						}
					}
					else {
						IsCarrying(TowerThree->GetActorLocation());
						TowerThreeArray.Emplace(Log);
						CurrentLogCount++;
					}
				}
				else {
					if(TowerThreeArray.Num() > 0) {
						IsNotCarrying(TowerThreeArray[TowerThreeArray.Num() - 1]);
						CurrentLogCount--;
						TowerThreeArray.SetNum(TowerThreeArray.Num() - 1);
					}
				}

				if(CurrentLogCount == GameMode->LogCount) {
					APlayerController* PlayerController = Cast<APlayerController>(GEngine->GetFirstLocalPlayerController(GetWorld()));
					GameMode->bFinishGame = true;
					bGameWon = true;
					PlayerController->SetPause(true);
				}
			}
		}
	}
}

void APlayerManager::IsNotCarrying(class ALogPickup* ALP) {
	SmallestLog = ALP;
	CurrentPos = SmallestLog->Pos;
	LastActor = Cast<AActor>(SmallestLog);
	CurrentLog = GetWorld()->SpawnActor<AActor>(LogToSpawn, GetActorTransform());
	CurrentLog->SetActorScale3D(LastActor->GetActorScale3D());
	CurrentLog->SetActorLocation(GetActorLocation() + FVector(0, 0, 400));
	LastActor->Destroy();
	bIsCarryingLog = true;
	GameMode->BiggerLogText = "";
	BiggerLogTimer = 0.f;
}

void APlayerManager::IsCarrying(FVector TowerLocation) {
	NewLog = GetWorld()->SpawnActor<AActor>(LogPickupToSpawn, GetActorTransform());
	NewLog->SetActorScale3D(CurrentLog->GetActorScale3D());
	NewLog->SetActorLocation(TowerLocation);
	Log = Cast<ALogPickup>(NewLog);
	Log->Pos = CurrentPos;
	PortalTimer = 1.f;
	NC_Portal = UNiagaraFunctionLibrary::SpawnSystemAtLocation(GetWorld(), NS_Portal, TowerLocation);
	CurrentLog->Destroy();
	bIsCarryingLog = false;
	GameMode->BiggerLogText = "";
	BiggerLogTimer = 0.f;
}