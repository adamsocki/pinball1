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
}


void AGamePaddle::UpdatePaddle()
{



}


void AGamePaddle::PaddleStart()
{
    FRotator NewRotation = GetActorRotation();
    float RotationSpeed = 600.10f; // Rotation speed in degrees per second
    float DeltaTime = GetWorld()->GetDeltaSeconds();
    UE_LOG(LogTemp, Warning, TEXT("Rotation: %f"), NewRotation.Yaw);

    if (paddleSide == EPaddleSide::PaddleSide_Left)
    {
        RotationSpeed = -RotationSpeed;
    }

    // Calculate the desired rotation
    float DesiredRotation = RotationSpeed * DeltaTime;

    // Check and adjust to ensure we don't exceed the maximum allowed rotation
    float MaxRotationDegrees = 85.0f; // set your max rotation limit here
    if (FMath::Abs(AccumulatedRotation + DesiredRotation) > MaxRotationDegrees)
    {
        // Adjust DesiredRotation so that AccumulatedRotation does not exceed MaxRotationDegrees
        DesiredRotation = MaxRotationDegrees - FMath::Abs(AccumulatedRotation);
        DesiredRotation *= FMath::Sign(RotationSpeed); // Ensure the rotation is in the correct direction
    }

    // Apply the rotation
    FQuat QuatRotation = FQuat(FRotator(0.f, DesiredRotation, 0.f));
    AddActorLocalRotation(QuatRotation);

    // Update accumulated rotation
    AccumulatedRotation += DesiredRotation;
}





void AGamePaddle::PaddleRelease()
{
    FRotator NewRotation = GetActorRotation();


    if (paddleSide == EPaddleSide::PaddleSide_Left && deltaYaw > -75.0f)
    {

        NewRotation.Yaw -= 444.0f * GetWorld()->GetDeltaSeconds();
        deltaYaw -= 444.0f * GetWorld()->GetDeltaSeconds();
        UE_LOG(LogTemp, Warning, TEXT("Failed to load mesh for resident %f!"), deltaYaw);

    }
    else if (paddleSide == EPaddleSide::PaddleSide_Right)
    {
        NewRotation.Yaw += 444.0f * GetWorld()->GetDeltaSeconds();

    }
    FQuat QuatRotation = FQuat(NewRotation);

    SetActorRotation(QuatRotation);

}