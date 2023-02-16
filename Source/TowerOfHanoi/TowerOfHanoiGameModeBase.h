#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameModeBase.h"
#include "TowerOfHanoiGameModeBase.generated.h"


UCLASS()
class TOWEROFHANOI_API ATowerOfHanoiGameModeBase : public AGameModeBase {
	GENERATED_BODY()

public:
	FString BiggerLogText;
	float LogCount;
	bool bFinishGame;

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

	UPROPERTY(EditAnywhere)
	TSubclassOf<UUserWidget> FinishGameBPWidget;

	UPROPERTY()
	class UStartMenuWidget* StartMenuClass;

	UPROPERTY()
	class UHelpMenuWidget* HelpMenuClass;

	UPROPERTY()
	class UInputMenuWidget* InputMenuClass;

	UPROPERTY()
	class UBiggerLogWidget* BiggerLogClass;

	UPROPERTY()
	class UFinishGameWidget* FinishGameClass;
	
};
