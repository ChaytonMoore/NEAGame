// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Pawn.h"
#include "EntireTerrain.h"
#include "Blueprint/UserWidget.h"
#include "Components/WidgetComponent.h"
#include "PlayerViewer.generated.h"

UCLASS()
class NEAGAME_API APlayerViewer : public APawn
{
	GENERATED_BODY()

public:
	// Sets default values for this pawn's properties
	APlayerViewer();
	UFUNCTION()
		void MoveRight();
	UFUNCTION()
		void MoveLeft();

	UFUNCTION()
		void StopMoveRight();
	UFUNCTION()
		void StopMoveLeft();

	UFUNCTION()
		void MoveDown();
	UFUNCTION()
		void MoveUp();

	UFUNCTION()
		void StopMoveDown();
	UFUNCTION()
		void StopMoveUp();

	UFUNCTION()
		void Shift();

	UFUNCTION()
		void StopShift();


	UFUNCTION()
		void MouseWheelDown();

	UFUNCTION()
		void StopMouseWheelDown();

	UFUNCTION()
		void LeftMouse();

	UPROPERTY()
		TSubclassOf<UUserWidget> TileUIClass;

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

private:
	UPROPERTY()
		bool bRight = false;
	UPROPERTY()
		bool bLeft = false;
	UPROPERTY()
		bool bUp = false;
	UPROPERTY()
		bool bDown = false;
	UPROPERTY()
		bool bShiftDown = false;
	UPROPERTY()
		bool bMouseWheelDown = false;

	UPROPERTY()
		FVector2D CurrentTile;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

};
