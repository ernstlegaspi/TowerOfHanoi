#include "PlayerMController.h"
#include "Blueprint/AIBlueprintHelperLibrary.h"
#include "Components/InputComponent.h"
#include "EnhancedInputComponent.h"
#include "EnhancedInputSubsystems.h"
#include "TowerOfHanoiGameModeBase.h"
#include "Kismet/GameplayStatics.h"
#include "Kismet/KismetSystemLibrary.h"

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

	PressTime = 0.f;
	GameMode = (ATowerOfHanoiGameModeBase*)UGameplayStatics::GetActorOfClass(GetWorld(), ATowerOfHanoiGameModeBase::StaticClass());
}

void APlayerMController::Tick(float DeltaTime) {
	Super::Tick(DeltaTime);

	if(PressTime > 0.f) PressTime -= DeltaTime;
}

void APlayerMController::OnClickStart() {
	// reset the click time if the click is started again
	ClickTime = 0.f;
}

void APlayerMController::OnClickTriggered() {
	// check if the click is short click or if the player is holding the left click
	ClickTime += GetWorld()->GetDeltaSeconds();

	// check if the player has clicked on anything
	if(ClickTime <= 0.1f && GetHitResultUnderCursor(ECollisionChannel::ECC_Visibility, true, Hit)) UAIBlueprintHelperLibrary::SimpleMoveToLocation(this, Hit.Location);
}

void APlayerMController::RestartGame(const FInputActionValue& Value) {
	UGameplayStatics::OpenLevel(GetWorld(), FName(UGameplayStatics::GetCurrentLevelName(GetWorld())));
}

void APlayerMController::QuitGame(const FInputActionValue& Value) {
	UKismetSystemLibrary::QuitGame(GetWorld(), this, EQuitPreference::Quit, true);
}

void APlayerMController::SetupInputComponent() {
	Super::SetupInputComponent();

	if(UEnhancedInputComponent* EnhancedInputComponent = CastChecked<UEnhancedInputComponent>(InputComponent)) {
		EnhancedInputComponent->BindAction(MouseClickAction, ETriggerEvent::Started, this, &APlayerMController::OnClickStart);
		EnhancedInputComponent->BindAction(MouseClickAction, ETriggerEvent::Triggered, this, &APlayerMController::OnClickTriggered);
		EnhancedInputComponent->BindAction(RestartGameAction, ETriggerEvent::Triggered, this, & APlayerMController::RestartGame);
		EnhancedInputComponent->BindAction(QuitGameAction, ETriggerEvent::Triggered, this, &APlayerMController::QuitGame);
	}
}