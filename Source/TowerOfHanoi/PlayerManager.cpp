#include "PlayerManager.h"
#include "Components/CapsuleComponent.h"
#include "Kismet/GameplayStatics.h"
#include "LevelSequence.h"
#include "LevelSequenceActor.h"
#include "MovieScene.h"
#include "MovieSceneSequencePlayer.h"
#include "LevelSequencePlayer.h"

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

	RotateLog = FVector();
	LastActor = nullptr;
	RotateSpeed = 100.f;

	ALS = Cast<ALevelSequenceActor>(MySequence);
	ALS->SequencePlayer->Play();
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
}

void APlayerManager::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent) {
	Super::SetupPlayerInputComponent(PlayerInputComponent);
}

void APlayerManager::PlayerOverlap(UPrimitiveComponent* HitComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult) {
	if(OtherActor->GetName().Contains("PickupLocation")) {
		if(OtherActor->GetName().Contains("_1")) {
			if(bIsCarryingLog) {
				if(TowerOneArray.Num() > 0) {
					if(CurrentPos > TowerOneArray[TowerOneArray.Num() - 1]->Pos) {
						UE_LOG(LogTemp, Warning, TEXT("Biggerrr 1111 %f %f"), CurrentPos, Log->Pos);
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
		else if(OtherActor->GetName().Contains("_4")) {
			if(bIsCarryingLog) {
				if(TowerTwoArray.Num() > 0) {
					if(CurrentPos > TowerTwoArray[TowerTwoArray.Num() - 1]->Pos) {
						UE_LOG(LogTemp, Warning, TEXT("Biggerrr 22222 %f %f"), CurrentPos, Log->Pos);
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
						UE_LOG(LogTemp, Warning, TEXT("Biggerrr 3333 %f %f"), CurrentPos, Log->Pos);
					}
					else {
						IsCarrying(TowerThree->GetActorLocation());
						TowerThreeArray.Emplace(Log);
						CurrentLogCount++;
						UE_LOG(LogTemp, Warning, TEXT("count: %f"), CurrentLogCount);
					}
				}
				else {
					IsCarrying(TowerThree->GetActorLocation());
					TowerThreeArray.Emplace(Log);
					CurrentLogCount++;
					UE_LOG(LogTemp, Warning, TEXT("count: %f"), CurrentLogCount);
				}
			}
			else {
				if(TowerThreeArray.Num() > 0) {
					IsNotCarrying(TowerThreeArray[TowerThreeArray.Num() - 1]);
					CurrentLogCount--;
					UE_LOG(LogTemp, Warning, TEXT("count: %f"), CurrentLogCount);
					TowerThreeArray.SetNum(TowerThreeArray.Num() - 1);
				}
			}

			if(CurrentLogCount == 3) UE_LOG(LogTemp, Warning, TEXT("YOU WON!"));
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
}

void APlayerManager::IsCarrying(FVector TowerLocation) {
	NewLog = GetWorld()->SpawnActor<AActor>(LogPickupToSpawn, GetActorTransform());
	NewLog->SetActorScale3D(CurrentLog->GetActorScale3D());
	NewLog->SetActorLocation(TowerLocation);
	Log = Cast<ALogPickup>(NewLog);
	Log->Pos = CurrentPos;
	CurrentLog->Destroy();
	bIsCarryingLog = false;
}