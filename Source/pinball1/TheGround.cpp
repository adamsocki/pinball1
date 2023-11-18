// Fill out your copyright notice in the Description page of Project Settings.


#include "TheGround.h"

// Sets default values
ATheGround::ATheGround()
{

	GroundMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("GroundMesh"));
	RootComponent = GroundMesh;


}

