#include "PlayerMController.h"
#include "Blueprint/AIBlueprintHelperLibrary.h"
#include "Components/InputComponent.h"
#include "EnhancedInputComponent.h"
#include "EnhancedInputSubsystems.h"
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
}

void APlayerMController::Tick(float DeltaTime) {
	Super::Tick(DeltaTime);

	if(PressTime > 0.f) PressTime -= DeltaTime;
}

void APlayerMController::OnClickStart() {
	ClickTime = 0.f;
}

void APlayerMController::OnClickTriggered() {
	ClickTime += GetWorld()->GetDeltaSeconds();

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