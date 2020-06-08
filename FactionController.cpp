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
}

//Something to do with manual tick or turn based.
void AFactionController::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}
