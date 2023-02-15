#include "PlayerMController.h"
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

	PressTime = 0.f;
}

void APlayerMController::Tick(float DeltaTime) {
	Super::Tick(DeltaTime);

	if(PressTime > 0.f) PressTime -= DeltaTime;
}

void APlayerMController::AddDisc(const FInputActionValue& Value) {
	const bool Val = Value.Get<bool>();
}

void APlayerMController::RemoveDisc(const FInputActionValue& Value) {
	const bool Val = Value.Get<bool>();
}

void APlayerMController::Pickup(const FInputActionValue& Value) {
	

	if(const bool Val = Value.Get<bool>()) {

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