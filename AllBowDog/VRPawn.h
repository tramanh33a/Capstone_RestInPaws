// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Pawn.h"
#include "VRPawn.generated.h"

class UOculusXRHandComponent;

UCLASS()
class ALLBOWDOG_API AVRPawn : public APawn
{
	GENERATED_BODY()

public:
	// Sets default values for this pawn's properties
	AVRPawn();


protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	UPROPERTY(BlueprintReadOnly, Category = "VR")
	UOculusXRHandComponent* LeftHandPtr;

	UPROPERTY(BlueprintReadOnly, Category = "VR")
	UOculusXRHandComponent* RightHandPtr;
	/*UPROPERTY(EditAnywhere, BlueprintReadWrite)
	UOculusXRHandComponent* OculusXRHandLeft;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	UOculusXRHandComponent* OculusXRHandRight;*/

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

private:
	void DetectRightHandGesture();

	bool bGestureActive = false;
	bool bPrevGesture = false;

};

