// Fill out your copyright notice in the Description page of Project Settings.


#include "PlayerViewer.h"
#include "Camera/CameraComponent.h"
#include "Components/InputComponent.h"
#include "Engine/World.h"
#include "Engine/Engine.h"
#include "Kismet/GameplayStatics.h"
#include "GameFramework/PlayerController.h"
#include "Engine/EngineTypes.h"
#include "FactionController.h"
#include "UObject/ConstructorHelpers.h"
#include "Blueprint/UserWidget.h"
#include "NEAGame/Public/PlayerWidgetMediator.h"


// Sets default values
APlayerViewer::APlayerViewer()
{
 	// Set this pawn to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	UCameraComponent* PlayerCamera = CreateDefaultSubobject<UCameraComponent>(TEXT("Player Camera"));
	RootComponent = PlayerCamera;
	PlayerCamera->SetWorldRotation(FRotator(-45,0,0));


}
void APlayerViewer::Shift()
{
	bShiftDown = true;
}

void APlayerViewer::StopShift()
{
	bShiftDown = false;
}


void APlayerViewer::MoveRight()
{
	bRight = true;
}

void APlayerViewer::MoveLeft()
{
	bLeft= true;
}

void APlayerViewer::StopMoveRight()
{
	bRight = false;
}

void APlayerViewer::StopMoveLeft()
{
	bLeft = false;
}


void APlayerViewer::MoveDown()
{
	bDown = true;
}

void APlayerViewer::MoveUp()
{
	bUp = true;
}

void APlayerViewer::StopMoveDown()
{
	bDown = false;
}

void APlayerViewer::StopMoveUp()
{
	bUp = false;
}


void APlayerViewer::StopMouseWheelDown()
{
	bMouseWheelDown = false;
}

void APlayerViewer::MouseWheelDown()
{
	bMouseWheelDown = true;
}


void APlayerViewer::LeftMouse()
{
	FHitResult HitData;
	ECollisionChannel CollChan = ECC_Visibility;
	GetWorld()->GetFirstPlayerController()->GetHitResultUnderCursor(CollChan,false,HitData);
	FVector2D ClickedTile = FVector2D(trunc(HitData.Location.X / 128 + 0.5), trunc(HitData.Location.Y / 128 + 0.5));

	AEntireTerrain* TerrainActor;TArray<AActor*> TerrainActorTemp; //Put this in begin play. //Remove later
	UGameplayStatics::GetAllActorsOfClass(GetWorld(), AEntireTerrain::StaticClass(), TerrainActorTemp);
	TerrainActor = (AEntireTerrain*)TerrainActorTemp[0];

	if (TerrainActor->ValidXY.Contains(ClickedTile))
	{
		//This also needs to be in begin play.
		TArray<AActor*> Factions; //Make this code better when in correct place.
		UGameplayStatics::GetAllActorsOfClass(GetWorld(), AFactionController::StaticClass(), Factions);
		AFactionController* FactionRef;
		int idx = -1;
		for (size_t i = 0; int(i) < Factions.Num(); i++)
		{

			FactionRef = (AFactionController*)Factions[i];
			if (FactionRef->OwnedTiles.Contains(ClickedTile))
			{
				idx = int(i);
			}
		}
		FactionRef = (AFactionController*)Factions[idx];

		//Might as well reuse the TerrainActorTemp Variable
		UGameplayStatics::GetAllActorsOfClass(GetWorld(), APlayerWidgetMediator::StaticClass(), TerrainActorTemp);
		APlayerWidgetMediator* WidgetRef = (APlayerWidgetMediator*)TerrainActorTemp[0];
		if (FactionRef->bPlayerControlled)
		{
			if (WidgetRef->bTileViewOpen)
			{
				if (ClickedTile == WidgetRef->TilePosition)
				{
					WidgetRef->RemoveTileUI();
				}
				else
				{
					WidgetRef->SpawnTileUI();
					//WidgetRef->Population = EntireTerrainRef->Population[ClickedTile.X * EntireTerrainRef->XSize + ClickedTile.Y];
					int idxT = EntireTerrainRef->ValidXY.Find(ClickedTile);
					WidgetRef->Population = EntireTerrainRef->Population[idxT];
					WidgetRef->Manpower = EntireTerrainRef->Manpower[idxT];
					//GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Red, FString::Printf(TEXT("Some variable values: x: %i"), EntireTerrainRef->Population[idxT]));

					WidgetRef->TilePosition = ClickedTile;
				}
			}
			else
			{
				WidgetRef->SpawnTileUI();
				//WidgetRef->Population = EntireTerrainRef->Population[ClickedTile.X * EntireTerrainRef->XSize + ClickedTile.Y];
				int idxT = EntireTerrainRef->ValidXY.Find(ClickedTile);
				WidgetRef->Population = EntireTerrainRef->Population[idxT];
				WidgetRef->Manpower = EntireTerrainRef->Manpower[idxT];
				//GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Red, FString::Printf(TEXT("Some variable values: x: %i"), EntireTerrainRef->Population[idxT]));
			
				WidgetRef->TilePosition = ClickedTile;
			}
		}
		//A diplomacy screen should be spawned, early on this will just be for war and peace but later maybe trade, alliances and vassals.
	}
}


// Called when the game starts or when spawned
void APlayerViewer::BeginPlay()
{
	Super::BeginPlay();
	GetWorld()->GetFirstPlayerController()->bShowMouseCursor = true;

	TArray<AActor*> TempActors; //Setting the reference to the EntireTerrainObject
	UGameplayStatics::GetAllActorsOfClass(GetWorld(), AEntireTerrain::StaticClass(),TempActors);
	EntireTerrainRef = (AEntireTerrain*)TempActors[0];


}

// Called every frame
void APlayerViewer::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	if (bRight)
	{
		AddActorWorldOffset(FVector(-450 * DeltaTime *((bShiftDown * 2) + 1),0,0));
	}

	if (bLeft)
	{
		AddActorWorldOffset(FVector(450 * DeltaTime * ((bShiftDown * 2) + 1), 0, 0));
	}

	if (bDown)
	{
		AddActorWorldOffset(FVector(0, 450 * DeltaTime *((bShiftDown * 4) + 1), 0));
	}

	if (bUp)
	{
		AddActorWorldOffset(FVector(0, -450 * DeltaTime * ((bShiftDown * 4) + 1), 0));
	}

	if (bMouseWheelDown)
	{
		AddActorWorldOffset(FVector(0,0,-100 * DeltaTime));
	}

}

// Called to bind functionality to input
void APlayerViewer::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);
	PlayerInputComponent->BindAction("Right",IE_Pressed, this, &APlayerViewer::MoveRight);
	PlayerInputComponent->BindAction("Left", IE_Pressed, this, &APlayerViewer::MoveLeft);

	PlayerInputComponent->BindAction("Right", IE_Released, this, &APlayerViewer::StopMoveRight);
	PlayerInputComponent->BindAction("Left", IE_Released, this, &APlayerViewer::StopMoveLeft);

	PlayerInputComponent->BindAction("Down", IE_Pressed, this, &APlayerViewer::MoveDown);
	PlayerInputComponent->BindAction("Up", IE_Pressed, this, &APlayerViewer::MoveUp);

	PlayerInputComponent->BindAction("Down", IE_Released, this, &APlayerViewer::StopMoveDown);
	PlayerInputComponent->BindAction("Up", IE_Released, this, &APlayerViewer::StopMoveUp);


	PlayerInputComponent->BindAction("Shift", IE_Pressed, this, &APlayerViewer::Shift);
	PlayerInputComponent->BindAction("Shift", IE_Released, this, &APlayerViewer::StopShift);

	PlayerInputComponent->BindAction("MouseWheelDown", IE_Pressed, this, &APlayerViewer::MouseWheelDown);
	PlayerInputComponent->BindAction("MouseWheelDown", IE_Released, this, &APlayerViewer::StopMouseWheelDown);

	PlayerInputComponent->BindAction("LeftMouse", IE_Pressed, this, &APlayerViewer::LeftMouse);
}
