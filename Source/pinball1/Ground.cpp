// Fill out your copyright notice in the Description page of Project Settings.


#include "Ground.h"

Ground::Ground()
{

	GroundMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("GroundMesh"));
	RootComponent = GroundMesh;


}
