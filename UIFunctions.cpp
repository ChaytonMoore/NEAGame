// Fill out your copyright notice in the Description page of Project Settings.


#include "NEAGame/Public/UIFunctions.h"
#include "NEAGame/Pieces/ArmyPiece.h"
#include "NEAGame/Landscape/FactionController.h"
#include "NEAGame/Landscape/EntireTerrain.h"
#include "Runtime/Engine/Classes/Kismet/GameplayStatics.h"
#include "Engine/World.h"

bool UUIFunctions::CanLevyLightInfantry(int manpower, float PlayerMoney, bool HasMetal)
{
	bool Output = false;
	if (manpower >= 100 && PlayerMoney >= 300 && HasMetal)
	{
		Output = true;
	}
	return Output;
}

bool UUIFunctions::CanLevyHeavyInfantry(int manpower, int population, float PlayerMoney, bool TileIron, bool TileMithril)
{
	bool Output = false;
	if (manpower > 350 && manpower > population/8 && PlayerMoney >= 1000 && (TileIron || TileMithril))
	{
		Output = true;
	}

	return Output;
}

void UUIFunctions::LevyLightInfantry(UObject* Caller, FVector2D Tile, bool TileTextiles)
{
	AEntireTerrain* LandscapeRef;
	TArray<AActor*> TempActors;
	UGameplayStatics::GetAllActorsOfClass(Caller->GetWorld(), AEntireTerrain::StaticClass(), TempActors);
	LandscapeRef = (AEntireTerrain*)TempActors[0];
	int idxT = LandscapeRef->ValidXY.Find(Tile);
	LandscapeRef->Population[idxT] = LandscapeRef->Population[idxT] - 100;
	LandscapeRef->Manpower[idxT] = LandscapeRef->Manpower[idxT] - 100;


	UGameplayStatics::GetAllActorsOfClass(Caller->GetWorld(), AFactionController::StaticClass(), TempActors);
	AFactionController* FactionRef = nullptr;
	AFactionController* FactionRefTemp;
	//Finds the player controller
	for (size_t i = 0; i < TempActors.Num(); i++)
	{
		FactionRefTemp = (AFactionController*)TempActors[i];
		if (FactionRefTemp->bPlayerControlled == true)
		{
			FactionRef = FactionRefTemp;
		}
	}


	if (FactionRef)
	{
		FactionRef->Money -= 300;
	}

	if (LandscapeRef->HasArmy[idxT])
	{
		//If there is an army on that tile something will need to be added.
	}
	else
	{
		//When there is no army it will have to create something
		FActorSpawnParameters SpawnData;
		AArmyPiece* NewPiece= Caller->GetWorld()->SpawnActor<AArmyPiece>(AArmyPiece::StaticClass(), FVector((Tile.X)*128,(Tile.Y)*128,10), FRotator(0,0,0),SpawnData);
		if (TileTextiles)
		{
			NewPiece->WarbandTypes = { "lightT" };
		}
		else
		{
			NewPiece->WarbandTypes = { "light" };
		}
		NewPiece->WarbandNumbers = { 100 };
	}
}

void UUIFunctions::LevyHeavyInfantry(UObject * Caller, FVector2D Tile, bool TileMithril)
{
	AEntireTerrain* LandscapeRef;
	TArray<AActor*> TempActors;
	UGameplayStatics::GetAllActorsOfClass(Caller->GetWorld(), AEntireTerrain::StaticClass(), TempActors);
	LandscapeRef = (AEntireTerrain*)TempActors[0];
	int idxT = LandscapeRef->ValidXY.Find(Tile);
	LandscapeRef->Population[idxT] = LandscapeRef->Population[idxT] - 100;
	LandscapeRef->Manpower[idxT] = LandscapeRef->Manpower[idxT] - 100;


	UGameplayStatics::GetAllActorsOfClass(Caller->GetWorld(), AFactionController::StaticClass(), TempActors);
	AFactionController* FactionRef = nullptr;
	AFactionController* FactionRefTemp;
	//Finds the player controller
	for (size_t i = 0; i < TempActors.Num(); i++)
	{
		FactionRefTemp = (AFactionController*)TempActors[i];
		if (FactionRefTemp->bPlayerControlled == true)
		{
			FactionRef = FactionRefTemp;
		}
	}


	if (FactionRef)
	{
		FactionRef->Money -= 1000;
	}

	if (LandscapeRef->HasArmy[idxT])
	{
		//If there is an army on that tile something will need to be added.
	}
	else
	{
		//When there is no army it will have to create something
		FActorSpawnParameters SpawnData;
		AArmyPiece* NewPiece = Caller->GetWorld()->SpawnActor<AArmyPiece>(AArmyPiece::StaticClass(), FVector((Tile.X) * 128, (Tile.Y) * 128, 10), FRotator(0, 0, 0), SpawnData);
		if (TileMithril)
		{
			NewPiece->WarbandTypes = { "heavy" };
		}
		else
		{
			NewPiece->WarbandTypes = { "heavyM" };
		}
		NewPiece->WarbandNumbers = { 100 };
	}
	//Just to note it takes 0 time to levy a unit.
}

int UUIFunctions::FindTilePopulation(AEntireTerrain * Terrain, APlayerWidgetMediator * Mediator)
{
	int Output = Terrain->Population[Terrain->ValidXY.Find(Mediator->TilePosition)];
	return Output;
}

int UUIFunctions::FindTileManpower(AEntireTerrain * Terrain, APlayerWidgetMediator * Mediator)
{
	int Output = Terrain->Manpower[Terrain->ValidXY.Find(Mediator->TilePosition)];
	return Output;
}
