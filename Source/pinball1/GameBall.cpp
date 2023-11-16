// Fill out your copyright notice in the Description page of Project Settings.


#include "GameBall.h"

// Sets default values
AGameBall::AGameBall()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;


    //ResidentMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("ResidentMesh"));
    BallMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("BallMesh"));
    RootComponent = BallMesh;
    
    static ConstructorHelpers::FObjectFinder<UStaticMesh> MeshAsset(TEXT("/Script/Engine.StaticMesh'/Game/StarterContent/Props/MaterialSphere.MaterialSphere'"));
    if (MeshAsset.Succeeded())
    {
        BallMesh->SetStaticMesh(MeshAsset.Object);
        
    }
    else
    {
        UE_LOG(LogTemp, Warning, TEXT("Failed to load mesh for resident!"));
    }

  
    TriggerSphere = CreateDefaultSubobject<USphereComponent>(TEXT("TriggerSphere"));
    // Set the box component to trigger overlap events
    TriggerSphere->SetGenerateOverlapEvents(true);
    TriggerSphere->SetCollisionProfileName(TEXT("Trigger"));
    UStaticMesh* meshSize = BallMesh->GetStaticMesh();
    //meshSize->GetBounds().BoxExtent;
    TriggerSphere->InitSphereRadius(meshSize->GetBounds().SphereRadius);
    // Attach the TriggerBox to the ResidentMesh
    TriggerSphere->SetupAttachment(BallMesh);
    // Bind the overlap event
    //TriggerSphere->OnComponentBeginOverlap.AddDynamic(this, &AResident::OnOverlapBegin);
    BallMesh->SetSimulatePhysics(true);
    BallMesh->WakeRigidBody();
}

// Called when the game starts or when spawned
void AGameBall::BeginPlay()
{
	Super::BeginPlay();
    RerunConstructionScripts();
}

// Called every frame
void AGameBall::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

