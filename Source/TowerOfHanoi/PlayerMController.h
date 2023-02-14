#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerController.h"
#include "PlayerMController.generated.h"

UCLASS()
class TOWEROFHANOI_API APlayerMController : public APlayerController {
	GENERATED_BODY()
	
protected:
	APlayerMController();

	uint32 bMoveToCursor : 1;

	virtual void BeginPlay() override;
	virtual void Tick(float DeltaTime) override;
	virtual void SetupInputComponent() override;

	UPROPERTY(EditAnywhere)
	class UInputMappingContext* MappingContext;

	UPROPERTY(EditAnywhere)
	class UInputAction* MouseClickAction;

	void OnClickStart();
	void OnClickTriggered();

	FHitResult Hit;
	float ClickTime;
};
