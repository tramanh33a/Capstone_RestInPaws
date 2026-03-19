// Fill out your copyright notice in the Description page of Project Settings.


#include "BowDogChar.h"
#include "GameFramework/CharacterMovementComponent.h"
#include <Kismet/GameplayStatics.h>
#include "Camera/CameraComponent.h"
#include "AIController.h"
#include "Navigation/PathFollowingComponent.h"

// Sets default values
ABowDogChar::ABowDogChar()
{
    // Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
    PrimaryActorTick.bCanEverTick = true;
    // Movement defaults
    GetCharacterMovement()->MaxWalkSpeed = 50.f;
}

// Called when the game starts or when spawned
void ABowDogChar::BeginPlay()
{
    Super::BeginPlay();

}

// Called every frame
void ABowDogChar::Tick(float DeltaTime)
{
    Super::Tick(DeltaTime);

    ACharacter* Player = UGameplayStatics::GetPlayerCharacter(GetWorld(), 0);
    /*if (!Player)
    {
        UE_LOG(LogTemp, Error, TEXT("Player is NULL"));
    }
    else
    {
        UE_LOG(LogTemp, Warning, TEXT("Player Name: %s"), *Player->GetName());
    }*/

    APawn* PlayerPawn = UGameplayStatics::GetPlayerPawn(GetWorld(), 0);

    if (!PlayerPawn)
    {
        UE_LOG(LogTemp, Error, TEXT("PlayerPawn is NULL"));
    }
    else
    {
        //UE_LOG(LogTemp, Warning, TEXT("PlayerPawn Name: %s"), *PlayerPawn->GetName());
        UCameraComponent* PlayerCamera = PlayerPawn->FindComponentByClass<UCameraComponent>();

        // 2. Get Dog's location (Point A)
        FVector DogLocation = GetActorLocation();

        // 3. Get Player's location (Point B)
        FVector PlayerLocation = PlayerPawn->GetActorLocation();
        FVector ActualHeadLocation = PlayerCamera->GetComponentLocation();

        // 4. Calculate the gap between them
        float Distance = FVector::Dist(DogLocation, PlayerLocation);

        /*UE_LOG(LogTemp, Warning, TEXT("Dog: "), DogLocation);
        UE_LOG(LogTemp, Warning, TEXT("Player: "), PlayerLocation);*/


        // 5. Update the variable for the ABP
        //CheckReachedPlayer(PlayerLocation, 100.f);
        CheckReachedPlayer(ActualHeadLocation, 20.f);
    }

}

// Called to bind functionality to input
void ABowDogChar::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
    Super::SetupPlayerInputComponent(PlayerInputComponent);

}


void ABowDogChar::CheckReachedPlayer(FVector TargetLocation, float AcceptanceRadius)
{
    float Distance = FVector::Dist2D(GetActorLocation(), TargetLocation);
    //float StartMovingThreshold = AcceptanceRadius + 200.0f;

    if (Distance <= AcceptanceRadius)
    {
        if (!bReachedPlayer)
        {
            bReachedPlayer = true;
            /*AAIController* AIController = Cast<AAIController>(GetController());
            if (AIController) {
                AIController->ClearFocus(EAIFocusPriority::Gameplay);
            }*/
        }
    }
    // Only trigger the "Move" logic if we are significantly far away
    else {
        bReachedPlayer = false;
        AAIController* AIController = Cast<AAIController>(GetController());
        if (AIController)
        {
            // Check if the AI is already moving to avoid "re-triggering" every 0.5s
            if (AIController->GetMoveStatus() != EPathFollowingStatus::Moving)
            {
                AIController->MoveToLocation(TargetLocation, AcceptanceRadius);
                //AIController->SetFocus(UGameplayStatics::GetPlayerPawn(GetWorld(), 0));
            }
        }
    }
}
