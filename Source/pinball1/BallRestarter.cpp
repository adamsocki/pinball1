// Fill out your copyright notice in the Description page of Project Settings.


#include "BallRestarter.h"

// Sets default values
ABallRestarter::ABallRestarter()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	RestarterMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("RestarterMesh"));
	RootComponent = RestarterMesh;

}

// Called when the game starts or when spawned
void ABallRestarter::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void ABallRestarter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

