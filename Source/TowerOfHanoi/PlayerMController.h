#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerController.h"
#include "InputActionValue.h"
#include "PlayerMController.generated.h"

UCLASS()
class TOWEROFHANOI_API APlayerMController : public APlayerController {
	GENERATED_BODY()

public:
	bool bButtonPressed;

protected:
	APlayerMController();

	uint32 bMoveToCursor : 1;

	virtual void BeginPlay() override;
	virtual void Tick(float DeltaTime) override;
	virtual void SetupInputComponent() override;

	UPROPERTY(EditAnywhere)
	class UInputMappingContext* MappingContext;

	UPROPERTY(EditAnywhere)
	class UInputAction* AddDiscAction;

	UPROPERTY(EditAnywhere)
	class UInputAction* RemoveDiscAction;

	UPROPERTY(EditAnywhere)
	class UInputAction* MouseClickAction;

	UPROPERTY(EditAnywhere)
	TSubclassOf<AActor> DiscToSpawn;

	UPROPERTY(EditAnywhere)
	AActor* TowerOne;

	UPROPERTY()
	class ADiscSpawnerPlatform* DiscPlatform;

	UPROPERTY()
	TArray<AActor*> DiscArray;

	UPROPERTY()
	AActor* Disc;

	UPROPERTY()
	FVector DecreaseScale;

	UPROPERTY()
	class APlayerManager* PlayerM;

	void AddDisc(const FInputActionValue& Value);
	void RemoveDisc(const FInputActionValue& Value);
	void OnClickStart();
	void OnClickTriggered();

	FHitResult Hit;
	float ClickTime, DiscCount, PressTime;
};
