// Fill out your copyright notice in the Description page of Project Settings.


#include "GameBall.h"
#include "Components/PrimitiveComponent.h"
#include "TheGround.h"
#include "GamePaddle.h"
#include "GamePlunger.h"
#include "BallRestarter.h"

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
    //BallMesh->SetSimulatePhysics(true);
    //BallMesh->WakeRigidBody();
    //BallMesh->BodyInstance.SetCollisionProfileName(TEXT("PhysicsActor"));
    //BallMesh->SetCollisionResponseToChannel(ECC_WorldStatic, ECR_Block);
    //BallMesh->SetCollisionResponseToChannel(ECC_WorldDynamic, ECR_Block);
    //BallMesh->SetCollisionEnabled(ECollisionEnabled::QueryAndPhysics);
    //BallMesh->SetNotifyRigidBodyCollision(true);
    //FBodyInstance* BodyInst = BallMesh->GetBodyInstance();
    //BodyInst->MassScale = 1000.0f;
    //BodyInst->UpdateMassProperties();

}
void AGameBall::LaunchBall(float LaunchStrength)
{
    FVector LaunchImpulse = FVector(LaunchStrength, 0.0f, 0.0f); // Adjust direction and strength
    BallMesh->AddImpulse(LaunchImpulse, NAME_None, true);
    inPlay = true;
}

// Called when the game starts or when spawned
void AGameBall::InitBall()
{
   /* BallMesh->SetSimulatePhysics(true);
    BallMesh->WakeRigidBody();
    BallMesh->BodyInstance.SetCollisionProfileName(TEXT("PhysicsActor"));
    BallMesh->SetCollisionResponseToChannel(ECC_WorldStatic, ECR_Block);
    BallMesh->SetCollisionResponseToChannel(ECC_WorldDynamic, ECR_Block);
    BallMesh->SetCollisionEnabled(ECollisionEnabled::QueryAndPhysics);
    BallMesh->SetNotifyRigidBodyCollision(true);
    BallMesh->OnComponentHit.AddDynamic(this, &AGameBall::OnHit);
    BallMesh->SetEnableGravity(true);
    FBodyInstance* BodyInst = BallMesh->GetBodyInstance();
    BodyInst->MassScale = 1000.0f;
    BodyInst->UpdateMassProperties();*/

    inPlay = false;

}

void AGameBall::UpdateBall(float DeltaTime)
{
    UE_LOG(LogTemp, Warning, TEXT("Applying Gravity Force: %s"), *GravityImpulse.ToString());

    if (inPlay)
    {
        //FVector GravityImpulse = FVector( -GravityStrength * DeltaTime, 0.0f, 0.0f);
        UE_LOG(LogTemp, Warning, TEXT("Applying Gravity Force Pre: %s"), *GravityImpulse.ToString());

        //GravityImpulse *= DeltaTime;
        BallMesh->AddForce(GravityImpulse * GravityMult);
        UE_LOG(LogTemp, Warning, TEXT("DeltaTime: %f"), DeltaTime);

        UE_LOG(LogTemp, Warning, TEXT("Applying Gravity Force Post: %s"), *GravityImpulse.ToString());


    }
}


void AGameBall::OnHit(UPrimitiveComponent* HitComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, FVector NormalImpulse, const FHitResult& Hit)
{

    //if (HitComponent)
    //{
    //    UE_LOG(LogTemp, Warning, TEXT("Hit Component: %s"), *HitComponent->GetName());
    //}

    //// Print the name of the other actor involved in the collision
    //if (OtherActor)
    //{
    //    UE_LOG(LogTemp, Warning, TEXT("Other Actor: %s"), *OtherActor->GetName());
    //}

    //// Print the normal of the hit surface
    //UE_LOG(LogTemp, Warning, TEXT("Hit Surface Normal: %s"), *Hit.ImpactNormal.ToString());

    //// Print the location of the hit
    //UE_LOG(LogTemp, Warning, TEXT("Hit Location: %s"), *Hit.ImpactPoint.ToString());
    AGamePlunger *gamePlunger = Cast<AGamePlunger>(OtherActor);
    if (gamePlunger)
    {
        return;
    }

    ATheGround *groundMesh = Cast<ATheGround>(OtherActor);
    if (groundMesh)
    {
        return;
    }

    ABallRestarter* ballRestarter = Cast<ABallRestarter>(OtherActor);
    if (ballRestarter)
    {
        RestartBall();
        return;
    }
    /*
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
//   /FVector FinalImpulse = ReverseImpulse * ImpulseStrength;

    // Apply the impulse to the ball
    //BallMesh->AddImpulse(FinalImpulse, NAME_None, true);


    // Apply the response impulse to the ball
    //BallMesh->AddImpulse(ResponseImpulse, NAME_None, true);
}

void AGameBall::RestartBall()
{

    SetActorLocation(FVector(9902.739287, 4222.935824, 749.418236));
    //BallMesh->SetPhysicsLinearVelocity(FVector(0.0f, 0.0f, 0.0f));
    //BallMesh->SetLinearDamping(0.0f);
    //BallMesh->SetF

    // Stop all angular movement
    //BallMesh->SetPhysicsAngularVelocityInDegrees(FVector(0.0f, 0.0f, 0.0f));

    // Clear any forces that might be applied
    //BallMesh->ClearAllPhysicsForces();
    //BallMesh->Forces
    //BallMesh->ClearAccumulatedForces();
    inPlay = false;
}