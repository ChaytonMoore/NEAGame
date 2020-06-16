// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Kismet/BlueprintFunctionLibrary.h"
#include "NEAGame/Landscape/EntireTerrain.h"
#include "NEAGame/Public/PlayerWidgetMediator.h"
#include "UIFunctions.generated.h"

/**
 * 
 */
UCLASS()
class NEAGAME_API UUIFunctions : public UBlueprintFunctionLibrary
{
	GENERATED_BODY()

public:
		UFUNCTION(BlueprintCallable,BlueprintPure,Category = "Check")
			static bool CanLevyLightInfantry(int manpower, float PlayerMoney, bool HasMetal);
		UFUNCTION(BlueprintCallable, BlueprintPure, Category = "Check")
			static bool CanLevyHeavyInfantry(int manpower, int population, float PlayerMoney, bool TileIron, bool TileMithril);
		
		
		UFUNCTION(BlueprintCallable, Category = "Spawn")
			static void LevyLightInfantry(UObject* Caller, FVector2D Tile, bool TileTextiles);
		UFUNCTION(BlueprintCallable, Category = "Spawn")
			static void LevyHeavyInfantry(UObject* Caller, FVector2D Tile, bool TileMithril);
		
		
		UFUNCTION(BlueprintCallable, BlueprintPure, Category = "Find")
			static int FindTilePopulation(AEntireTerrain* Terrain, APlayerWidgetMediator* Mediator);
		UFUNCTION(BlueprintCallable,BlueprintPure, Category = "Find")
			static int FindTileManpower(AEntireTerrain* Terrain, APlayerWidgetMediator* Mediator);

};
