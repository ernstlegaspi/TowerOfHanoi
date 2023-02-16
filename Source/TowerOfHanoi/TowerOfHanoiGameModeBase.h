#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameModeBase.h"
#include "TowerOfHanoiGameModeBase.generated.h"


UCLASS()
class TOWEROFHANOI_API ATowerOfHanoiGameModeBase : public AGameModeBase {
	GENERATED_BODY()

protected:
	ATowerOfHanoiGameModeBase();

	virtual void BeginPlay() override;
	virtual void Tick(float DeltaTime) override;

	UPROPERTY(EditAnywhere)
	TSubclassOf<UUserWidget> StartMenuBPWidget;

	UPROPERTY(EditAnywhere)
	TSubclassOf<UUserWidget> HelpMenuBPWidget;

	UPROPERTY()
	class UStartMenuWidget* StartMenuClass;

	UPROPERTY()
	class UHelpMenuWidget* HelpMenuClass;
	
};
