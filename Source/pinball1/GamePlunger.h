// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "GamePlunger.generated.h"

UCLASS()
class PINBALL1_API AGamePlunger : public AActor
{
	GENERATED_BODY()
	
public:	

	// Sets default values for this actor's properties
	AGamePlunger();

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Mesh")
	UStaticMeshComponent* PlungerMesh;

	void InitPlunger();
	void UpdatePlunger(float DeltaTime);

	void PlungerStartPlayerInput();
	void PlungerReleasePlayerInput();

	void PlungerStart();
	void PlungerRelease();

	bool plungerStartAction;
	bool plungerReleaseAction;

	float accumulatedMovement;
	float accumulatedActionTimer;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "PlungerID")
	int32 plungerID;

};
