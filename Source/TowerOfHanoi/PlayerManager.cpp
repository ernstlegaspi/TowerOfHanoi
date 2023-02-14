#include "PlayerManager.h"
#include "Components/CapsuleComponent.h"

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
}

void APlayerManager::Tick(float DeltaTime) {
	Super::Tick(DeltaTime);
}

void APlayerManager::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent) {
	Super::SetupPlayerInputComponent(PlayerInputComponent);
}

void APlayerManager::PlayerOverlap(UPrimitiveComponent* HitComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult) {
	UE_LOG(LogTemp, Warning, TEXT("Player"));
}