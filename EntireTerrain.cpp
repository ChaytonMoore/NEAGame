#include "EntireTerrain.h"
#include "UObject/ConstructorHelpers.h"
#include "Materials/Material.h"
#include "Engine/Texture2D.h"
#include "Components/DecalComponent.h"
#include "Materials/Material.h"
#include "Engine/World.h"
#include "Kismet/GameplayStatics.h"
#include "Engine/Engine.h"




AEntireTerrain::AEntireTerrain()
{
	//Setting faction data up
	//FactionCreationData(Factions);

 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	//Right so I'm going to make it so that probably around 100 materials are created.
	//What I'm going to try now is decals, they atleast somewhat work for blueprints.
	//UDecalComponent* FirstDecal;
	//FirstDecal = CreateAbstractDefaultSubobject<UDecalComponent>("Decal1");
	//FirstDecal->SetWorldRotation(FRotator(90,0,0));
	ConstructorHelpers::FObjectFinder<UMaterial> MaterialRef(TEXT("Material'/Game/Data/RedDecalMat.RedDecalMat'")); //The map is what the terrain is based on.
	ConstructorHelpers::FObjectFinder<UTexture2D> MapImageRef(TEXT("Texture2D'/Game/Data/map3.map3'")); //The map is what the terrain is based on.
	ConstructorHelpers::FObjectFinder<UTexture2D> FactionImageRef(TEXT("Texture2D'/Game/Data/FactionsMap.FactionsMap'")); //The map is what the terrain is based on.
	MapImage = MapImageRef.Object;
	FactionImage = FactionImageRef.Object;
	const FColor* FormatedImageData = static_cast<const FColor*>(MapImage->PlatformData->Mips[0].BulkData.LockReadOnly());
	const FColor* FormatedImageDataFac = static_cast<const FColor*>(FactionImage->PlatformData->Mips[0].BulkData.LockReadOnly());

	//TArray<UDecalComponent*> Decals;

	FString NameSet;
	int NameSetTemp;
	FName NameLast;
	FString NameSet2;
	int NameSetTemp2;
	FName NameLast2;
	//GEngine->AddOnScreenDebugMessage(-1, 15.0f, FColor::Yellow, FString::Printf(TEXT("length %i"), Factions.Num()));
	for (size_t i = 0; i < MapImage->GetSizeX(); i++)
	{
		for (size_t j = 0; j < MapImage->GetSizeY(); j++)
		{
			FColor PixelColour = FormatedImageData[j * MapImage->GetSizeX() + i];
			//"000000FF" != PixelColour.ToHex() && "0026FFFF" != PixelColour.ToHex() &&

			if ("000000FF" != PixelColour.ToHex() && "0026FFFF" != PixelColour.ToHex()) //If the map is black then it is a mountain so no tile should be generated.
			{	
				NameSetTemp = static_cast<int>(i); //yay conversions
				NameSet = FString::FromInt(NameSetTemp);

				NameSetTemp2 = static_cast<int>(j); //yay conversions
				NameSet2 = FString::FromInt(NameSetTemp2);

				NameSet += "and";
				NameSet += NameSet2;
				NameLast = FName(*NameSet);


				Decals.Add(CreateDefaultSubobject<UDecalComponent>(NameLast));
				Decals[Decals.Num() - 1]->SetWorldScale3D(FVector(1.15, 0.25, 0.25));
				Decals[Decals.Num() - 1]->SetWorldRotation(FRotator(90, 0, 0));
				Decals[Decals.Num() - 1]->SetWorldLocation(FVector(128 * i, 128 * j, 0));
				Decals[Decals.Num() - 1]->SetDecalMaterial(MaterialRef.Object);
			}
			//It might be more efficient to continously spawn the decals based on what the player can see.
		}
	}
	MapImage->PlatformData->Mips[0].BulkData.Unlock();
	FactionImage->PlatformData->Mips[0].BulkData.Unlock();


}

// Called when the game starts or when spawned
void AEntireTerrain::BeginPlay()
{
	Super::BeginPlay();
	//Must first spawn the factions
	FActorSpawnParameters SpawnParams;
	Factions.Add(GetWorld()->SpawnActor<AFactionController>(FVector(0,0,0),FRotator(0,0,0)));
	FactionsAssignData();


	TArray<FString> ValidColours;
	for (size_t i = 0; i < Factions.Num(); i++)
	{
		ValidColours.Add(Factions[i]->ColourValue);
	}

	const FColor* FormatedImageDataFac = static_cast<const FColor*>(FactionImage->PlatformData->Mips[0].BulkData.LockReadOnly());



	for (size_t i = 0; i < FactionImage->GetSizeX(); i++)
	{
		for (size_t j = 0; j < FactionImage->GetSizeY(); j++)
		{
			FColor PixelColour = FormatedImageDataFac[j * MapImage->GetSizeX() + i];
			if (PixelColour.ToHex() != "FF0000FF")
			{
				Decals[j * MapImage->GetSizeX() + i]->SetHiddenInGame(true);
			}
		}
	}

	FactionImage->PlatformData->Mips[0].BulkData.Unlock();
}


void AEntireTerrain::FactionsAssignData()
{
	//This will be used to setup all the factions
	Factions[0]->Name = FText::FromString(ANSI_TO_TCHAR("Eragrim"));
	Factions[0]->Culture = "Aes Raega";
	Factions[0]->ColourValue = "FF0000FF";
	Factions[0]->Money = 15000;


}

// Called every frame
void AEntireTerrain::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	//Right now this only exists for the editor only function of resetting size but more will be added later.
	if (ResetTerrain)
	{
		ResetTerrain = false;

	}

}
