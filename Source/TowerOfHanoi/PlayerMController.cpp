#include "PlayerMController.h"
#include "PlayerManager.h"
#include "DiscSpawnerPlatform.h"
#include "Blueprint/AIBlueprintHelperLibrary.h"
#include "Components/InputComponent.h"
#include "EnhancedInputComponent.h"
#include "EnhancedInputSubsystems.h"
#include "Kismet/GameplayStatics.h"

APlayerMController::APlayerMController() {
	PrimaryActorTick.bCanEverTick = true;

	bShowMouseCursor = true;
	DefaultMouseCursor = EMouseCursor::Default;
}

void APlayerMController::BeginPlay() {
	Super::BeginPlay();

	if(UEnhancedInputLocalPlayerSubsystem* Subsystem = ULocalPlayer::GetSubsystem<UEnhancedInputLocalPlayerSubsystem>(GetLocalPlayer())) {
		Subsystem->AddMappingContext(MappingContext, 0);
	}

	PlayerM = (APlayerManager*)UGameplayStatics::GetActorOfClass(GetWorld(), APlayerManager::StaticClass());
	DiscPlatform = (ADiscSpawnerPlatform*)UGameplayStatics::GetActorOfClass(GetWorld(), ADiscSpawnerPlatform::StaticClass());
	DiscCount = 0.f;
	PressTime = 0.f;
	DecreaseScale = FVector(0, 0, 0);
}

void APlayerMController::Tick(float DeltaTime) {
	Super::Tick(DeltaTime);

	if(PressTime > 0.f) PressTime -= DeltaTime;
}

void APlayerMController::AddDisc(const FInputActionValue& Value) {
	const bool Val = Value.Get<bool>();

	if(DiscPlatform->bInPlatform && (DiscCount >= 0.f && DiscCount <= 4.f) && PressTime <= 0.f) {
		bButtonPressed = true;
		PressTime = 1.f;
		DiscCount++;
		Disc = GetWorld()->SpawnActor<AActor>(DiscToSpawn, PlayerM->TowerOne->GetActorTransform());
		Disc->SetActorScale3D(FVector(2.4, 2.4, 1.f) - DecreaseScale);
		DecreaseScale += FVector(.2f, .2f, 0.f);
		DiscArray.Emplace(Disc);
	}
}

void APlayerMController::RemoveDisc(const FInputActionValue& Value) {
	const bool Val = Value.Get<bool>();

	if(DiscPlatform->bInPlatform && (DiscCount > 0.f && DiscCount <= 5.f) && PressTime <= 0.f) {
		bButtonPressed = true;
		PressTime = 1.f;
		DecreaseScale -= FVector(.2f, .2f, 0.f);
		DiscArray[--DiscCount]->Destroy();
	}
}

void APlayerMController::OnClickStart() {
	ClickTime = 0.f;
}

void APlayerMController::OnClickTriggered() {
	ClickTime += GetWorld()->GetDeltaSeconds();

	if(ClickTime <= 0.1f && GetHitResultUnderCursor(ECollisionChannel::ECC_Visibility, true, Hit)) UAIBlueprintHelperLibrary::SimpleMoveToLocation(this, Hit.Location);
}

void APlayerMController::SetupInputComponent() {
	Super::SetupInputComponent();

	if(UEnhancedInputComponent* EnhancedInputComponent = CastChecked<UEnhancedInputComponent>(InputComponent)) {
		EnhancedInputComponent->BindAction(MouseClickAction, ETriggerEvent::Started, this, &APlayerMController::OnClickStart);
		EnhancedInputComponent->BindAction(MouseClickAction, ETriggerEvent::Triggered, this, &APlayerMController::OnClickTriggered);
		EnhancedInputComponent->BindAction(AddDiscAction, ETriggerEvent::Triggered, this, &APlayerMController::AddDisc);
		EnhancedInputComponent->BindAction(RemoveDiscAction, ETriggerEvent::Triggered, this, &APlayerMController::RemoveDisc);
	}
}