// Fill out your copyright notice in the Description page of Project Settings.


#include "GamePlunger.h"

// Sets default values
AGamePlunger::AGamePlunger()
{
    PlungerMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("PlungerMesh"));
    RootComponent = PlungerMesh;

    static ConstructorHelpers::FObjectFinder<UStaticMesh> MeshAsset(TEXT("/Script/Engine.StaticMesh'/Game/ThirdPerson/Meshes/Plunger_001.Plunger_001'"));
    if (MeshAsset.Succeeded())
    {
        PlungerMesh->SetStaticMesh(MeshAsset.Object);

    }
    else
    {
        UE_LOG(LogTemp, Warning, TEXT("Failed to load mesh for resident!"));
    }

    PlungerMesh->SetCollisionEnabled(ECollisionEnabled::QueryAndPhysics);


}

void AGamePlunger::InitPlunger()
{
    accumulatedMovement = 0.0f;
}

void AGamePlunger::UpdatePlunger(float DeltaTime)
{
	if (plungerStartAction)
	{
        PlungerStart();
	}

	if (plungerStartAction)
	{
        PlungerRelease();
	}
}



void AGamePlunger::PlungerStartPlayerInput()
{
    plungerStartAction = true;
    plungerReleaseAction = false;
}

void AGamePlunger::PlungerReleasePlayerInput()
{
    plungerStartAction = false;
    plungerReleaseAction = true;
}




void AGamePlunger::PlungerStart()
{
    FVector CurrentLocation = GetActorLocation();
    float movementSpeed = -100.0f; 
    float DeltaTime = GetWorld()->GetDeltaSeconds();
    //  UE_LOG(LogTemp, Warning, TEXT("Accum ST 1: %f"), AccumulatedRotation);

    float DesiredPositionOffset = movementSpeed * DeltaTime;
    float MaxMovement = 385.0f; // set your max rotation limit here
    
    if (FMath::Abs(accumulatedMovement + DesiredPositionOffset) > MaxMovement)
    {
        DesiredPositionOffset = MaxMovement - FMath::Abs(accumulatedMovement);
        DesiredPositionOffset *= FMath::Sign(movementSpeed);
        plungerStartAction = false;
    }

    FVector MovementOffset = FVector(0.0f, 0.0f, DesiredPositionOffset);
    AddActorLocalOffset(MovementOffset);

    accumulatedMovement += DesiredPositionOffset;
    // UE_LOG(LogTemp, Warning, TEXT("Accum ST 2: %f"), AccumulatedRotation);
}
void AGamePlunger::PlungerRelease()
{
}

