// Fill out your copyright notice in the Description page of Project Settings.


#include "VRPawn.h"
#include "OculusXRHandComponent.h"


// Sets default values
AVRPawn::AVRPawn()
{
 	// Set this pawn to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

// Called when the game starts or when spawned
void AVRPawn::BeginPlay()
{
	Super::BeginPlay();

    TArray<UOculusXRHandComponent*> HandComponents;
    GetComponents<UOculusXRHandComponent>(HandComponents);

    for (UOculusXRHandComponent* Hand : HandComponents)
    {
        if (Hand->ComponentHasTag(TEXT("LeftHand")))
        {
            LeftHandPtr = Hand;
        }
        else if (Hand->ComponentHasTag(TEXT("RightHand")))
        {
            RightHandPtr = Hand;
        }
    }

    // Safety Check: Log a warning if they weren't found
    if (!LeftHandPtr || !RightHandPtr)
    {
        UE_LOG(LogTemp, Error, TEXT("VRPawn: Hand components not found! Check your Tags."));
    }
}

// Called every frame
void AVRPawn::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
    DetectRightHandGesture();
}

// Called to bind functionality to input
void AVRPawn::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

}

void AVRPawn::DetectRightHandGesture()
{
    if (!LeftHandPtr || !RightHandPtr)
        return;

    FTransform LeftPalm = LeftHandPtr->GetBoneTransformByName("palm", EBoneSpaces::WorldSpace);
    FTransform RightPalm = RightHandPtr->GetBoneTransformByName("palm", EBoneSpaces::WorldSpace);
    /*if (!OculusXRHandLeft || !OculusXRHandRight)
        return;

    FTransform LeftPalm =
        OculusXRHandLeft->GetBoneTransformByName("palm", EBoneSpaces::WorldSpace);

    FTransform RightPalm =
        OculusXRHandRight->GetBoneTransformByName("palm", EBoneSpaces::WorldSpace);*/

    bool bLeftValid = !LeftPalm.GetLocation().IsNearlyZero();
    bool bRightValid = !RightPalm.GetLocation().IsNearlyZero();

    if (!bLeftValid || !bRightValid)
    {
        bGestureActive = false;
    }
    else
    {
        FVector PalmUp = RightPalm.GetUnitAxis(EAxis::Z);
        float Dot = FVector::DotProduct(PalmUp, FVector::UpVector);

        bGestureActive = (Dot > 0.7f);
    }

    if (bGestureActive != bPrevGesture)
    {
        bPrevGesture = bGestureActive;

        if (bGestureActive)
        {
            UE_LOG(LogTemp, Warning, TEXT("RIGHT HAND OUT START"));
        }
        else
        {
            UE_LOG(LogTemp, Warning, TEXT("RIGHT HAND OUT END"));
        }
    }
}