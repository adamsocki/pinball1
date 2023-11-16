// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "MyStructs.h"



#include "GamePaddle.generated.h"

UCLASS()
class PINBALL1_API AGamePaddle : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AGamePaddle();

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "BallSetup")
	EPaddleSide paddleSide;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Mesh")
	UStaticMeshComponent* PaddleMesh;

	//UPROPERTY(VisibleAnywhere)
	//USphereComponent* TriggerSphere;

	void PaddleStart();
	


};
