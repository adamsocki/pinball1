// Fill out your copyright notice in the Description page of Project Settings.


#include "GameBall.h"
#include "Components/PrimitiveComponent.h"
#include "TheGround.h"
#include "GamePaddle.h"

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

  
    //TriggerSphere = CreateDefaultSubobject<USphereComponent>(TEXT("TriggerSphere"));
    //// Set the box component to trigger overlap events
    //TriggerSphere->SetGenerateOverlapEvents(true);
    //TriggerSphere->SetCollisionProfileName(TEXT("Trigger"));
    //UStaticMesh* meshSize = BallMesh->GetStaticMesh();
    ////meshSize->GetBounds().BoxExtent;
    //TriggerSphere->InitSphereRadius(meshSize->GetBounds().SphereRadius);
    //// Attach the TriggerBox to the ResidentMesh
    //TriggerSphere->SetupAttachment(BallMesh);
    // Bind the overlap event
    //TriggerSphere->OnComponentBeginOverlap.AddDynamic(this, &AResident::OnOverlapBegin);
    BallMesh->SetSimulatePhysics(true);
    BallMesh->WakeRigidBody();
    BallMesh->BodyInstance.SetCollisionProfileName(TEXT("PhysicsActor"));
    BallMesh->SetCollisionResponseToChannel(ECC_WorldStatic, ECR_Block);
    BallMesh->SetCollisionResponseToChannel(ECC_WorldDynamic, ECR_Block);
    BallMesh->SetCollisionEnabled(ECollisionEnabled::QueryAndPhysics);
    BallMesh->SetNotifyRigidBodyCollision(true);

}

// Called when the game starts or when spawned
void AGameBall::BeginPlay()
{
    Super::BeginPlay();
    RerunConstructionScripts();
    BallMesh->OnComponentHit.AddDynamic(this, &AGameBall::OnHit);


}

// Called every frame
void AGameBall::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
    FVector impulse = FVector(0.0f, 0.0f, -500.0f);
    BallMesh->AddImpulse(impulse, NAME_None, true);


}


void AGameBall::OnHit(UPrimitiveComponent* HitComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, FVector NormalImpulse, const FHitResult& Hit)
{

    if (HitComponent)
    {
        UE_LOG(LogTemp, Warning, TEXT("Hit Component: %s"), *HitComponent->GetName());
    }

    // Print the name of the other actor involved in the collision
    if (OtherActor)
    {
        UE_LOG(LogTemp, Warning, TEXT("Other Actor: %s"), *OtherActor->GetName());
    }

    // Print the normal of the hit surface
    UE_LOG(LogTemp, Warning, TEXT("Hit Surface Normal: %s"), *Hit.ImpactNormal.ToString());

    // Print the location of the hit
    UE_LOG(LogTemp, Warning, TEXT("Hit Location: %s"), *Hit.ImpactPoint.ToString());


    /*ATheGround *groundMesh = Cast<ATheGround>(OtherActor);
    if (groundMesh)
    {
        return;
    }

    AGamePaddle* gamePaddle = Cast<AGamePaddle>(OtherActor);
    if (gamePaddle)
    {
        return;
    }*/
    // Calculate a response impulse here
   // FVector ResponseImpulse = ...; // Calculate based on collision properties
    FVector HitNormal = Hit.ImpactNormal;

    // Reverse the normal vector to get the impulse direction
    FVector ReverseImpulse = -HitNormal;

    // You might want to multiply by a factor to control the strength of the impulse
    float ImpulseStrength = 200.0f; // Adjust this value as needed
    FVector FinalImpulse = ReverseImpulse * ImpulseStrength;

    // Apply the impulse to the ball
    //BallMesh->AddImpulse(FinalImpulse, NAME_None, true);


    // Apply the response impulse to the ball
    //BallMesh->AddImpulse(ResponseImpulse, NAME_None, true);
}
