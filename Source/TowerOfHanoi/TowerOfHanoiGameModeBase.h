#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameModeBase.h"
#include "TowerOfHanoiGameModeBase.generated.h"


UCLASS()
class TOWEROFHANOI_API ATowerOfHanoiGameModeBase : public AGameModeBase {
	GENERATED_BODY()

public:
	float LogCount;
	FString BiggerLogText;

protected:
	ATowerOfHanoiGameModeBase();

	virtual void BeginPlay() override;
	virtual void Tick(float DeltaTime) override;

	UPROPERTY(EditAnywhere)
	TSubclassOf<UUserWidget> StartMenuBPWidget;

	UPROPERTY(EditAnywhere)
	TSubclassOf<UUserWidget> HelpMenuBPWidget;

	UPROPERTY(EditAnywhere)
	TSubclassOf<UUserWidget> InputMenuBPWidget;

	UPROPERTY(EditAnywhere)
	TSubclassOf<UUserWidget> BiggerLogBPWidget;

	UPROPERTY()
	class UStartMenuWidget* StartMenuClass;

	UPROPERTY()
	class UHelpMenuWidget* HelpMenuClass;

	UPROPERTY()
	class UInputMenuWidget* InputMenuClass;

	UPROPERTY()
	class UBiggerLogWidget* BiggerLogClass;
	
};
