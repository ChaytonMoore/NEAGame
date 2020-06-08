// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "FactionController.h"
#include "EntireTerrain.generated.h"

USTRUCT()
struct FFactions
{
	GENERATED_USTRUCT_BODY()
	UPROPERTY()
		FText FactionName;
	UPROPERTY()
		FString ColourValue;
	UPROPERTY()
		FString Culture;
	UPROPERTY()
		float Money;
};


UCLASS()
class NEAGAME_API AEntireTerrain : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AEntireTerrain();
	UPROPERTY(EditAnywhere)
		int XSize = 80;
	UPROPERTY(EditAnywhere)
		int YSize = 100;
	UPROPERTY(EditAnywhere)
		TArray<FVector2D> ValidXY;
	UPROPERTY()
		TArray<int> Population; 
	UPROPERTY()
		TArray<float> Wealth;
	UPROPERTY()
		TArray<FString> Resource;
	UPROPERTY(Editanywhere)
		bool ResetTerrain;
	UPROPERTY(Editanywhere)
		FString MapMode; //These are factions, resources, wealth and populations
	UPROPERTY(EditAnywhere)
		UTexture2D* MapImage;
	UPROPERTY(EditAnywhere)
		UTexture2D* FactionImage;
	UPROPERTY(EditAnywhere)
		TArray<AFactionController*> Factions;
	UPROPERTY(EditAnywhere)
		TArray<UDecalComponent*> Decals;
protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

private:
	UFUNCTION()
		void FactionsAssignData();

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

};
