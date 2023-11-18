// Fill out your copyright notice in the Description page of Project Settings.


#include "GamePaddle.h"

// Sets default values
AGamePaddle::AGamePaddle()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	//PrimaryActorTick.bCanEverTick = true;

    PaddleMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("PaddleMesh"));
    RootComponent = PaddleMesh;

    static ConstructorHelpers::FObjectFinder<UStaticMesh> MeshAsset(TEXT("/Script/Engine.StaticMesh'/Game/ThirdPerson/Meshes/Paddle_001.Paddle_001'"));
    if (MeshAsset.Succeeded())
    {
        PaddleMesh->SetStaticMesh(MeshAsset.Object);

    }
    else
    {
        UE_LOG(LogTemp, Warning, TEXT("Failed to load mesh for resident!"));
    }

    PaddleMesh->SetCollisionEnabled(ECollisionEnabled::QueryAndPhysics);

}


void AGamePaddle::InitPaddle()
{
    AccumulatedRotation = 0.0f;
    paddleStartAction = false;
    paddleReleaseAction = false;
}


void AGamePaddle::UpdatePaddle()
{

    if (paddleReleaseAction)
    {
        ReleasePaddle();
    }

    if (paddleStartAction)
    {
        StartPaddle();
    }

}


void AGamePaddle::PaddleStartPlayerInput()
{
    paddleStartAction = true;
    paddleReleaseAction = false;

}

void AGamePaddle::PaddleReleasePlayerInput()
{
    paddleStartAction = false;
    paddleReleaseAction = true;

}



void AGamePaddle::StartPaddle()
{
    FRotator NewRotation = GetActorRotation();
    float RotationSpeed = 1200.0f; // Rotation speed in degrees per second
    float DeltaTime = GetWorld()->GetDeltaSeconds();
  //  UE_LOG(LogTemp, Warning, TEXT("Accum ST 1: %f"), AccumulatedRotation);

    if (paddleSide == EPaddleSide::PaddleSide_Left)
    {
        RotationSpeed = -RotationSpeed;
    }

    // Calculate the desired rotation
    float DesiredRotation = RotationSpeed * DeltaTime;
    //UE_LOG(LogTemp, Warning, TEXT("DesRot ST 1: %f"), DesiredRotation);

    // Check and adjust to ensure we don't exceed the maximum allowed rotation
    float MaxRotationDegrees = 85.0f; // set your max rotation limit here
    if (FMath::Abs(AccumulatedRotation + DesiredRotation) > MaxRotationDegrees)
    {
        // Adjust DesiredRotation so that AccumulatedRotation does not exceed MaxRotationDegrees
        DesiredRotation = MaxRotationDegrees - FMath::Abs(AccumulatedRotation);
        DesiredRotation *= FMath::Sign(RotationSpeed); // Ensure the rotation is in the correct direction
        paddleStartAction = false;
    }

    // Apply the rotation
    FQuat QuatRotation = FQuat(FRotator(0.f, DesiredRotation, 0.f));
    AddActorLocalRotation(QuatRotation);

    // Update accumulated rotation
    AccumulatedRotation += DesiredRotation;
   // UE_LOG(LogTemp, Warning, TEXT("Accum ST 2: %f"), AccumulatedRotation);

}


void AGamePaddle::ReleasePaddle()
{
    FRotator NewRotation = GetActorRotation();
    float RotationSpeed = 1200.0f; // Rotation speed in degrees per second
    float DeltaTime = GetWorld()->GetDeltaSeconds();    
   // UE_LOG(LogTemp, Warning, TEXT("Accum RE 1: %f"), AccumulatedRotation);


    if (paddleSide == EPaddleSide::PaddleSide_Right)
    {
        RotationSpeed = -RotationSpeed;
    }

    // Calculate the desired rotation
    float DesiredRotation = RotationSpeed * DeltaTime;
   // UE_LOG(LogTemp, Warning, TEXT("DesRot RE 1: %f"), DesiredRotation);

    // Check and adjust to ensure we don't exceed the maximum allowed rotation
    float MinRotationDegrees = 0.0f; // set your max rotation limit here
    float ifChecker = AccumulatedRotation + DesiredRotation;
  //  UE_LOG(LogTemp, Warning, TEXT("ifCheck 1: %f"), ifChecker);


    if (paddleSide == EPaddleSide::PaddleSide_Left)
    {
        if ((AccumulatedRotation + DesiredRotation) > MinRotationDegrees)
        {
            // Adjust DesiredRotation so that AccumulatedRotation does not exceed MaxRotationDegrees
            DesiredRotation = MinRotationDegrees + FMath::Abs(AccumulatedRotation);
        //    UE_LOG(LogTemp, Warning, TEXT("DesRot RE Inside: %f"), DesiredRotation);

            DesiredRotation *= FMath::Sign(RotationSpeed); // Ensure the rotation is in the correct direction
            paddleReleaseAction = false;

        }
    }
    else
    {
        if ((AccumulatedRotation + DesiredRotation) < MinRotationDegrees)
        {
            // Adjust DesiredRotation so that AccumulatedRotation does not exceed MaxRotationDegrees
            DesiredRotation = MinRotationDegrees + FMath::Abs(AccumulatedRotation);
           // UE_LOG(LogTemp, Warning, TEXT("DesRot RE Inside: %f"), DesiredRotation);

            DesiredRotation *= FMath::Sign(RotationSpeed); // Ensure the rotation is in the correct direction
            paddleReleaseAction = false;

        }
    }
    

    // Apply the rotation
    FQuat QuatRotation = FQuat(FRotator(0.f, DesiredRotation, 0.f));
    AddActorLocalRotation(QuatRotation);

    // Update accumulated rotation
    AccumulatedRotation += DesiredRotation;
    //UE_LOG(LogTemp, Warning, TEXT("Accum RE 2: %f"), AccumulatedRotation);

}
