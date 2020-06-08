//This is for a class which will mediate between different 

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Blueprint/UserWidget.h"
#include "PlayerWidgetMediator.generated.h"

UCLASS()
class NEAGAME_API APlayerWidgetMediator : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	APlayerWidgetMediator();
	UPROPERTY()
		FString Culture;
	
	//Since we can't use constructors to reference widgets I'll have to spawn this class to generate widgets based on references placed in the editor.
	UPROPERTY(EditAnywhere, Category = "Default")
		TSubclassOf<UUserWidget> TileUIClass;

	UPROPERTY()
		bool bTileViewOpen;

	UPROPERTY()
		UUserWidget* TileUI;

	UFUNCTION()
		void SpawnTileUI();

	UFUNCTION()
		void RemoveTileUI();


protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

};
