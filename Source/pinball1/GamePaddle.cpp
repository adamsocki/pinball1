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