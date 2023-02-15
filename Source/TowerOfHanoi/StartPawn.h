#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Pawn.h"
#include "StartPawn.generated.h"

UCLASS()
class TOWEROFHANOI_API AStartPawn : public APawn {
	GENERATED_BODY()

public:
	AStartPawn();

protected:
	virtual void BeginPlay() override;

public:	
	virtual void Tick(float DeltaTime) override;

	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

};