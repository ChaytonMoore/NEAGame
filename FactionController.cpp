// Fill out your copyright notice in the Description page of Project Settings.


#include "FactionController.h"

// Sets default values
AFactionController::AFactionController()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

// Called when the game starts or when spawned
void AFactionController::BeginPlay()
{
	Super::BeginPlay();
	//Right now this will just be for testing
	for (size_t i = 0; i < OwnedTiles.Num(); i++)
	{
		//This will be something that finds out if the factions actually has a metal in one of its provinces.
	}
	//Right now it will say all factions have a metal
	HasMetal = true;
}

//Something to do with manual tick or turn based.
void AFactionController::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}


float RecaclulateIncome(TArray<int> Population,TArray<float> Wealth, float TaxRate)
{
	float Output = 0;
	for (size_t i = 0; i < Population.Num(); i++)
	{
		//For each province
		Output += Population[i] * Wealth[i] * TaxRate;

	}

	return Output;
}
