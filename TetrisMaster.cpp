// Fill out your copyright notice in the Description page of Project Settings.


#include "TetrisMaster.h"
#include "GameHUD.h"
#include "TetrisGrid.h"
#include <Runtime\Engine\Classes\Kismet\GameplayStatics.h>



// Sets default values
ATetrisMaster::ATetrisMaster()
{
 	// Set this pawn to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	
	scene = CreateDefaultSubobject<USceneComponent>(TEXT("SceneObject"));
}

// Called when the game starts or when spawned
void ATetrisMaster::BeginPlay()
{
	Super::BeginPlay();
	if (gridActor != nullptr) 
	{
		grid = (ATetrisGrid*)gridActor;
		FVector playerPos;
		playerPos.X = 40.f;
		playerPos.Y = -grid->gridStartPos.Z - 500.f;
		playerPos.Z = grid->gridStartPos.Z / 2;

		scene->GetOwner()->SetActorLocation(playerPos);
	}
}

// Called every frame
void ATetrisMaster::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	if (moveDir != 0) 
	{
		if (t > 0.f) 
		{
			t -= DeltaTime; // timer for movement
		}
		else
		{
			if (grid != nullptr)
			{
				if (grid->currentTetrimino != nullptr)
				{
					if ((moveDir == -1 && grid->CanMoveLeft()) // Trying to and can move left
						|| (moveDir == 1 && grid->CanMoveRight())) // Trying to and can move right
					{
						grid->MoveTetrimino(FVector(100.0f * moveDir, 0.0f, 0.f));
					}
				}
			}
			t = timeBetweenMovements * (counter);
			counter -= 0.1f;

			counter = counter < 0.5f ? 0.5f : counter; // clamping counter
		}
	}
	else
	{
		t = timeBetweenMovements;
		counter = 1.f;
	}
}

void ATetrisMaster::MoveLeft()
{
	movingLeft = !movingLeft;

	int moveIncrement = movingLeft ? -1 : 1;
	moveDir += moveIncrement;

	if (movingLeft && grid != nullptr) 
	{
		if (grid->currentTetrimino != nullptr) 
		{
			if (grid->CanMoveLeft()) 
			{
				grid->MoveTetrimino(FVector(-100.0f, 0.0f, 0.f));
			}
		}
	}
}

void ATetrisMaster::MoveRight()
{
	movingRight = !movingRight;

	int moveIncrement = movingRight ? 1 : -1;
	moveDir += moveIncrement;

	if (movingRight && grid != nullptr)
	{
		if (grid->currentTetrimino != nullptr) 
		{
			if (grid->CanMoveRight()) 
			{
				grid->MoveTetrimino(FVector(100.f, 0.0f, 0.f));
			}
		}
	}
}

void ATetrisMaster::SpeedUp()
{
	if (grid != nullptr) 
	{
		grid->SpeedTetriminoUp();
	}
}

void ATetrisMaster::RotateLeft() 
{
	if (grid->CanRotateLeft()) 
	{
		grid->RotateTetriminoLeft();
	}
}

void ATetrisMaster::RotateRight()
{
	if (grid->CanRotateRight())
	{
		grid->RotateTetriminoRight();
	}
}

void ATetrisMaster::Pause()
{
	if (AGameHUD* gameHUD = Cast<AGameHUD>(UGameplayStatics::GetPlayerController(GetWorld(), 0)->GetHUD()))
	{
		gameHUD->ShowPauseScreen();
	}
}

// Called to bind functionality to input
void ATetrisMaster::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

	PlayerInputComponent->BindAction("MoveLeft", IE_Pressed, this, &ATetrisMaster::MoveLeft);
	PlayerInputComponent->BindAction("MoveLeft", IE_Released, this, &ATetrisMaster::MoveLeft);

	PlayerInputComponent->BindAction("MoveRight", IE_Pressed, this, &ATetrisMaster::MoveRight);
	PlayerInputComponent->BindAction("MoveRight", IE_Released, this, &ATetrisMaster::MoveRight);

	PlayerInputComponent->BindAction("RotateLeft", IE_Pressed, this, &ATetrisMaster::RotateLeft);
	PlayerInputComponent->BindAction("RotateRight", IE_Pressed, this, &ATetrisMaster::RotateRight);

	PlayerInputComponent->BindAction("SpeedUp", IE_Pressed, this, &ATetrisMaster::SpeedUp);
	PlayerInputComponent->BindAction("SpeedUp", IE_Released, this, &ATetrisMaster::SpeedUp);
	PlayerInputComponent->BindAction("Pause", IE_Pressed, this, &ATetrisMaster::Pause);

}

