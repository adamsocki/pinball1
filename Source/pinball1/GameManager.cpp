// Fill out your copyright notice in the Description page of Project Settings.


#include "GameManager.h"
#include <Kismet/GameplayStatics.h>

// Sets default values
AGameManager::AGameManager()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;


	
}

// Called when the game starts or when spawned
void AGameManager::BeginPlay()
{
	Super::BeginPlay();
	

	TArray<AActor*> FoundPaddleActors;
	UGameplayStatics::GetAllActorsOfClass(GetWorld(), AGamePaddle::StaticClass(), FoundPaddleActors);

	for (int i = 0; i < FoundPaddleActors.Num(); i++)
	{
		// ADD ALL BUILDINGS IN LEVEL TO AN ARRAY
		AGamePaddle* GamePaddle = Cast<AGamePaddle>(FoundPaddleActors[i]);
		if (GamePaddle != nullptr)
		{
			if (GamePaddle->paddleSide == EPaddleSide::PaddleSide_Left)
			{
				paddleLeft = GamePaddle; 
				if (paddleLeft)
				{
					paddleLeft->InitPaddle();
				}
			}
			else if (GamePaddle->paddleSide == EPaddleSide::PaddleSide_Right)
			{
				paddleRight = GamePaddle;
				if (paddleRight)
				{
					paddleRight->InitPaddle();
				}
			}
		}
	}


	TArray<AActor*> FoundPlungerActors;
	UGameplayStatics::GetAllActorsOfClass(GetWorld(), AGamePlunger::StaticClass(), FoundPlungerActors);
	for (int i = 0; i < FoundPlungerActors.Num(); i++)
	{
		// ADD ALL BUILDINGS IN LEVEL TO AN ARRAY
		AGamePlunger* GamePlunger = Cast<AGamePlunger>(FoundPlungerActors[i]);
		if (GamePlunger != nullptr)
		{
			if (GamePlunger->plungerID == 1)
			{
				plunger01 = GamePlunger;
				if (plunger01)
				{
					plunger01->InitPlunger();
				}
			}
		}
	}
}



// Called every frame
void AGameManager::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	paddleLeft->UpdatePaddle();
	paddleRight->UpdatePaddle();

	plunger01->UpdatePlunger(DeltaTime);
}

