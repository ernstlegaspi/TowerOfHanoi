#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "PlayerManager.generated.h"

UCLASS()
class TOWEROFHANOI_API APlayerManager : public ACharacter {
	GENERATED_BODY()

public:
	APlayerManager();

protected:
	virtual void BeginPlay() override;

	UPROPERTY()
	class UCapsuleComponent* PlayerTrigger;

	UFUNCTION()
	void PlayerOverlap(UPrimitiveComponent* HitComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);

public:	
	virtual void Tick(float DeltaTime) override;

	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

};
