// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Pawn.h"
#include "TetrisGrid.h"
#include "TetrisMaster.generated.h"

UCLASS()
class TETRIS_API ATetrisMaster : public APawn
{
	GENERATED_BODY()

public:
	// Sets default values for this pawn's properties
	ATetrisMaster();

	UPROPERTY(EditAnywhere, Category = "Tetris")
		AActor* gridActor;

	USceneComponent* scene;



protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	ATetrisGrid* grid;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	void RotateLeft();

	void RotateRight();

	void MoveLeft();

	void MoveRight();

	void MoveTetrimino();

	bool movingLeft = false;
	bool movingRight = false;

	int moveDir = 0;
	
	float t;
	int counter;

	UPROPERTY(EditAnywhere, Category = "Controls")
		float timeBetweenMovements;

	void SpeedUp();

	void Pause();

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

};