// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "BowDogChar.generated.h"

UCLASS()
class ALLBOWDOG_API ABowDogChar : public ACharacter
{
	GENERATED_BODY()

public:
	// Sets default values for this character's properties
	ABowDogChar();

	// Expose to BP
	UPROPERTY(BlueprintReadWrite, Category = "AI")
	bool bReachedPlayer = false;

	// Function to check if reached player
	UFUNCTION(BlueprintCallable, Category = "AI")
	void CheckReachedPlayer(FVector TargetLocation, float AcceptanceRadius);

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

};
