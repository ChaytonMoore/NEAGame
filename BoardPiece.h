// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Engine/StaticMesh.h"
#include "Components/StaticMeshComponent.h"
#include "BoardPiece.generated.h"

UCLASS()
class NEAGAME_API ABoardPiece : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ABoardPiece();
	UPROPERTY()
		int iTileIndex;
	UPROPERTY()
		FVector2D TilePosition;
	UPROPERTY()
		UStaticMeshComponent* MainMesh;

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

};
