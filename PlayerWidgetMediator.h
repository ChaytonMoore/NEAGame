// Fill out your copyright notice in the Description page of Project Settings.


#include "NEAGame//Public/PlayerWidgetMediator.h"

// Sets default values
APlayerWidgetMediator::APlayerWidgetMediator()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

void APlayerWidgetMediator::SpawnTileUI()
{
	if (! bTileViewOpen)
	{
		TileUI = CreateWidget(GetWorld(), TileUIClass);
		if (TileUI)
		{
			TileUI->AddToViewport();
			bTileViewOpen = true;
		}
	}

}

void APlayerWidgetMediator::RemoveTileUI()
{
	TileUI->RemoveFromParent();
	TileUI->Destruct();
	bTileViewOpen = false;
}



// Called when the game starts or when spawned
void APlayerWidgetMediator::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void APlayerWidgetMediator::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

