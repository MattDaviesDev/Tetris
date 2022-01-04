// Fill out your copyright notice in the Description page of Project Settings.


#include "TetriminoComponent.h"

// Sets default values for this component's properties
UTetriminoComponent::UTetriminoComponent()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	// ...
}


// Called when the game starts
void UTetriminoComponent::BeginPlay()
{
	Super::BeginPlay();

	AssignOffset();

	// ...
	
}


// Called every frame
void UTetriminoComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	// ...
}

void UTetriminoComponent::AssignOffset()
{
	for (int i = 0; i < 4; i++)
	{
		localOffset.Add(FNestedVector());
	}
	switch (tetriminoType)
	{
#pragma region  Blue Tetrimino
	case TetriminoType::Blue:

		localOffset[0].A.Add(FVector(0.f, 0.f, 200.f));
		localOffset[0].A.Add(FVector(0.f, 0.f, 100.f));
		localOffset[0].A.Add(FVector(0.f, 0.f, 0.f));
		localOffset[0].A.Add(FVector(0.f, 0.f, -100.f));

		localOffset[1].A.Add(FVector(-200.f, 0.f, 0.f));
		localOffset[1].A.Add(FVector(-100.f, 0.f, 0.f));
		localOffset[1].A.Add(FVector(0.f, 0.f, 0.f));
		localOffset[1].A.Add(FVector(100.f, 0.f, 0.f));

		localOffset[2].A.Add(FVector(0.f, 0.f, -200.f));
		localOffset[2].A.Add(FVector(0.f, 0.f, -100.f));
		localOffset[2].A.Add(FVector(0.f, 0.f, 0.f));
		localOffset[2].A.Add(FVector(0.f, 0.f, 100.f));

		localOffset[3].A.Add(FVector(200.f, 0.f, 0.f));
		localOffset[3].A.Add(FVector(100.f, 0.f, 0.f));
		localOffset[3].A.Add(FVector(0.f, 0.f, 0.f));
		localOffset[3].A.Add(FVector(-100.f, 0.f, 0.f));
			break;
#pragma endregion
#pragma region DarkBlue Tetrimino
	case TetriminoType::DarkBlue:
		localOffset[0].A.Add(FVector(0.f, 0.f, 100.f));
		localOffset[0].A.Add(FVector(0.f, 0.f, 0.f));
		localOffset[0].A.Add(FVector(-100.f, 0.f, 0.f));
		localOffset[0].A.Add(FVector(-200.f, 0.f, 0.f));

		localOffset[1].A.Add(FVector(-100.f, 0.f, 0.f));
		localOffset[1].A.Add(FVector(0.f, 0.f, 0.f));
		localOffset[1].A.Add(FVector(0.f, 0.f, -100.f));
		localOffset[1].A.Add(FVector(0.f, 0.f, -200.f));

		localOffset[2].A.Add(FVector(0.f, 0.f, -100.f));
		localOffset[2].A.Add(FVector(0.f, 0.f, 0.f));
		localOffset[2].A.Add(FVector(100.f, 0.f, 0.f));
		localOffset[2].A.Add(FVector(200.f, 0.f, 0.f));

		localOffset[3].A.Add(FVector(100.f, 0.f, 0.f));
		localOffset[3].A.Add(FVector(0.f, 0.f, 0.f));
		localOffset[3].A.Add(FVector(0.f, 0.f, 100.f));
		localOffset[3].A.Add(FVector(0.f, 0.f, 200.f));
		break;
#pragma endregion
#pragma region Red Tetrimino
	case TetriminoType::Red:
		localOffset[0].A.Add(FVector(-100.f, 0.f, 0.f));
		localOffset[0].A.Add(FVector(0.f, 0.f, 0.f));
		localOffset[0].A.Add(FVector(0.f, 0.f, 100.f));
		localOffset[0].A.Add(FVector(100.f, 0.f, 100.f));

		localOffset[1].A.Add(FVector(0.f, 0.f, -100.f));
		localOffset[1].A.Add(FVector(0.f, 0.f, 0.f));
		localOffset[1].A.Add(FVector(-100.f, 0.f, 0.f));
		localOffset[1].A.Add(FVector(-100.f, 0.f, 100.f));

		localOffset[2].A.Add(FVector(100.f, 0.f, 0.f));
		localOffset[2].A.Add(FVector(0.f, 0.f, 0.f));
		localOffset[2].A.Add(FVector(0.f, 0.f, -100.f));
		localOffset[2].A.Add(FVector(-100.f, 0.f, -100.f));

		localOffset[3].A.Add(FVector(0.f, 0.f, 100.f));
		localOffset[3].A.Add(FVector(0.f, 0.f, 0.f));
		localOffset[3].A.Add(FVector(100.f, 0.f, 0.f));
		localOffset[3].A.Add(FVector(100.f, 0.f, -100.f));
		break;
#pragma endregion
#pragma region Yellow Tetrimino
	case TetriminoType::Yellow:
		localOffset[0].A.Add(FVector(0.f, 0.f, 0.f));
		localOffset[0].A.Add(FVector(0.f, 0.f, -100.f));
		localOffset[0].A.Add(FVector(-100.f, 0.f, 0.f));
		localOffset[0].A.Add(FVector(-100.f, 0.f, -100.f));

		localOffset[1].A.Add(FVector(0.f, 0.f, 0.f));
		localOffset[1].A.Add(FVector(100.f, 0.f, 0.f));
		localOffset[1].A.Add(FVector(0.f, 0.f, -100.f));
		localOffset[1].A.Add(FVector(100.f, 0.f, -100.f));

		localOffset[2].A.Add(FVector(0.f, 0.f, 0.f));
		localOffset[2].A.Add(FVector(0.f, 0.f, 100.f));
		localOffset[2].A.Add(FVector(100.f, 0.f, 0.f));
		localOffset[2].A.Add(FVector(100.f, 0.f, 100.f));

		localOffset[3].A.Add(FVector(0.f, 0.f, 0.f));
		localOffset[3].A.Add(FVector(-100.f, 0.f, 0.f));
		localOffset[3].A.Add(FVector(0.f, 0.f, 100.f));
		localOffset[3].A.Add(FVector(-100.f, 0.f, 100.f));
		break;
#pragma endregion
#pragma region Green Tetrimino
	case TetriminoType::Green:
		localOffset[0].A.Add(FVector(100.f, 0.f, -100.f));
		localOffset[0].A.Add(FVector(0.f, 0.f, -100.f));
		localOffset[0].A.Add(FVector(0.f, 0.f, 0.f));
		localOffset[0].A.Add(FVector(-100.f, 0.f, 0.f));

		localOffset[1].A.Add(FVector(100.f, 0.f, 100.f));
		localOffset[1].A.Add(FVector(100.f, 0.f, 0.f));
		localOffset[1].A.Add(FVector(0.f, 0.f, 0.f));
		localOffset[1].A.Add(FVector(0.f, 0.f, -100.f));

		localOffset[2].A.Add(FVector(-100.f, 0.f, 100.f));
		localOffset[2].A.Add(FVector(0.f, 0.f, 100.f));
		localOffset[2].A.Add(FVector(0.f, 0.f, 0.f));
		localOffset[2].A.Add(FVector(100.f, 0.f, 0.f));

		localOffset[3].A.Add(FVector(-100.f, 0.f, -100.f));
		localOffset[3].A.Add(FVector(-100.f, 0.f, 0.f));
		localOffset[3].A.Add(FVector(0.f, 0.f, 0.f));
		localOffset[3].A.Add(FVector(0.f, 0.f, 100.f));
		break;
#pragma endregion
#pragma region Orange Tetrimino
	case TetriminoType::Orange:
		localOffset[0].A.Add(FVector(200.f, 0.f, 0.f));
		localOffset[0].A.Add(FVector(100.f, 0.f, 0.f));
		localOffset[0].A.Add(FVector(0.f, 0.f, 0.f));
		localOffset[0].A.Add(FVector(0.f, 0.f, 100.f));

		localOffset[1].A.Add(FVector(0.f, 0.f, 200.f));
		localOffset[1].A.Add(FVector(0.f, 0.f, 100.f));
		localOffset[1].A.Add(FVector(0.f, 0.f, 0.f));
		localOffset[1].A.Add(FVector(-100.f, 0.f, 0.f));

		localOffset[2].A.Add(FVector(-200.f, 0.f, 0.f));
		localOffset[2].A.Add(FVector(-100.f, 0.f, 0.f));
		localOffset[2].A.Add(FVector(0.f, 0.f, 0.f));
		localOffset[2].A.Add(FVector(0.f, 0.f, -100.f));

		localOffset[3].A.Add(FVector(0.f, 0.f, -200.f));
		localOffset[3].A.Add(FVector(0.f, 0.f, -100.f));
		localOffset[3].A.Add(FVector(0.f, 0.f, 0.f));
		localOffset[3].A.Add(FVector(100.f, 0.f, 0.f));
		break;
#pragma endregion
#pragma region Purple Tetrimino
	case TetriminoType::Purple:
		localOffset[0].A.Add(FVector(0.f, 0.f, 100.f));
		localOffset[0].A.Add(FVector(0.f, 0.f, 0.f));
		localOffset[0].A.Add(FVector(-100.f, 0.f, 0.f));
		localOffset[0].A.Add(FVector(100.f, 0.f, 0.f));

		localOffset[1].A.Add(FVector(-100.f, 0.f, 0.f));
		localOffset[1].A.Add(FVector(0.f, 0.f, 0.f));
		localOffset[1].A.Add(FVector(0.f, 0.f, -100.f));
		localOffset[1].A.Add(FVector(0.f, 0.f, 100.f));

		localOffset[2].A.Add(FVector(0.f, 0.f, -100.f));
		localOffset[2].A.Add(FVector(0.f, 0.f, 0.f));
		localOffset[2].A.Add(FVector(-100.f, 0.f, 0.f));
		localOffset[2].A.Add(FVector(100.f, 0.f, 0.f));

		localOffset[3].A.Add(FVector(100.f, 0.f, 0.f));
		localOffset[3].A.Add(FVector(0.f, 0.f, 0.f));
		localOffset[3].A.Add(FVector(0.f, 0.f, -100.f));
		localOffset[3].A.Add(FVector(0.f, 0.f, 100.f));
		break;
#pragma endregion
	default:
		break;
	}

}

