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
}

void AGamePlunger::UpdatePlunger(float DeltaTime)
{
	if (plungerStartAction)
	{

	}

	if (plungerStartAction)
	{

	}
}

