// Fill out your copyright notice in the Description page of Project Settings.


#include "Score.h"

// Sets default values
AScore::AScore()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	// Create and attach the text render component
	TextComponent = CreateDefaultSubobject<UTextRenderComponent>(TEXT("TextComponent"));
	RootComponent = TextComponent;

	// Set default text if desired
	TextComponent->SetText(FText::FromString("Hello, World!"));

}

// Called when the game starts or when spawned
void AScore::BeginPlay()
{
	Super::BeginPlay();

	FString FormattedText = FString::Printf(TEXT("Score: %f"), 9.01f);
	TextComponent->SetText(FText::FromString(FormattedText));

	
}

// Called every frame
void AScore::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void AScore::SetScore(float addScore)
{

	FString FormattedText = FString::Printf(TEXT("Score: %f"), addScore);
	TextComponent->SetText(FText::FromString(FormattedText));

}

