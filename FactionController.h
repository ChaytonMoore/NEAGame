#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "FactionController.generated.h"

UCLASS()
class NEAGAME_API AFactionController : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AFactionController();
	UPROPERTY()
		FText Name;
	UPROPERTY()
		FString Culture;
	UPROPERTY()
		FString GovernmentType = "Monarchy"; //Monarchy and republic are the only too I think I'll have but maybe tribal etc.
	UPROPERTY()
		FString ColourValue;
	UPROPERTY()
		float Money;
	UPROPERTY()
		bool bPlayerControlled;


protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

};
