// Fill out your copyright notice in the Description page of Project Settings.


#include "TetrisGrid.h"
#include "TetriminoComponent.h"
#include "SMainMenuWidget.h"
#include "GameHUD.h"
#include <Runtime\Engine\Classes\Kismet\GameplayStatics.h>

// Sets default values
ATetrisGrid::ATetrisGrid()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	scene = CreateDefaultSubobject<USceneComponent>(TEXT("SceneObject"));
	scene = RootComponent;

	instance = this;

}

// Called when the game starts or when spawned
void ATetrisGrid::BeginPlay()
{
	Super::BeginPlay();
	
	looseTetriminos.Init(nullptr, 0);

	availableIndexes.Init(0, 7);
	availableIndexes[1] = 1;
	availableIndexes[2] = 2;
	availableIndexes[3] = 3;
	availableIndexes[4] = 4;
	availableIndexes[5] = 5;
	availableIndexes[6] = 6;

	gridStartPos += FVector(100.f * (columns / 2), 0.f, 0.f);

	AssignEmptyGrid();

	ConstructGridBorder();

	//SpawnGhostBlocks();

	HUDinstance = Cast<AGameHUD>(UGameplayStatics::GetPlayerController(GetWorld(), 0)->GetHUD());


	//SpawnTetrimino();
	
}

void ATetrisGrid::ConstructGridBorder()
{
	FActorSpawnParameters spawnParams;
	FVector spawnPos = FVector::ZeroVector;
	spawnPos.Z = gridStartPos.Z + 600.f;
	spawnPos.Y = -1.f;
	for (int i = 0; i <= rows + 9; i++)
	{
		spawnPos.X = gridStartPos.X + 100.f;
		if (i <= 4 || i >= rows + 7) // bottom and top of grid
		{
			for (int j = 0; j <= columns + 1; j++)
			{
				GetWorld()->SpawnActor<AActor>(blackBox, spawnPos, spawnRot, spawnParams);
				spawnPos.X -= 100.f;
			}
		}
		else 
		{
			GetWorld()->SpawnActor<AActor>(blackBox, spawnPos, spawnRot, spawnParams);
			spawnPos.X -= 100.f * (columns + 1);
			GetWorld()->SpawnActor<AActor>(blackBox, spawnPos, spawnRot, spawnParams);
		}
		spawnPos.Z -= 100.f;
	}


}

void ATetrisGrid::SpawnTetrimino()
{
	FActorSpawnParameters spawnParams;

	if (availableIndexes.Num() == 0) 
	{
		availableIndexes.Add(0);
		availableIndexes.Add(1);
		availableIndexes.Add(2);
		availableIndexes.Add(3);
		availableIndexes.Add(4);
		availableIndexes.Add(5);
		availableIndexes.Add(6);
	}
	
	int randomIndex = FMath::RandRange(0, availableIndexes.Num() - 1);
	TSubclassOf<AActor> newTetrimino = TetriminoList[availableIndexes[randomIndex]];
	availableIndexes.RemoveAt(randomIndex);

	FVector spawnPos = gridStartPos + FVector(-100.f * (columns / 2), 0.f, 0.f);
	AActor* spawnedActor = GetWorld()->SpawnActor<AActor>(newTetrimino, spawnPos, spawnRot, spawnParams);
	looseTetriminos.Add(spawnedActor);
	TArray<AActor*> children;
	spawnedActor->GetAttachedActors(children, true);
	for (int i = 0; i < children.Num(); i++)
	{
		int x = 0;
		int y = columns / 2;
		GetGridPositionFromWorldPos(children[i]->GetActorLocation(), &x, &y);
		if (grid[x].A[y] == 1) 
		{
			gameOver = true;
			HUDinstance->ShowGameOverScreen();
			return;
		}
	}
	startPos = spawnedActor->GetActorLocation();
	endPos = startPos - FVector(0.f, 0.f, 100.f);
	currentTetrimino = spawnedActor;

	UpdateGhostBlockPositions();

}

// Called every frame
void ATetrisGrid::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	
	if (HUDinstance->requiresReset) 
	{
		ResetGame();
		HUDinstance->requiresReset = false;
	}


	if (!gameOver) 
	{
		if (!HUDinstance->isPlaying) 
		{
			return;
		}

		if (minosToDestroy.Num() > 0) 
		{
			timeOutT += DeltaTime;
			if (destroyedMinos >= minosToDestroy.Num()) 
			{
				MoveArrayElementsDown();
				CleanUpPlacedTetriminos();
				return;
			}

			for (int i = 0; i < minosToDestroy.Num(); i++)
			{
				minoT[i] += DeltaTime;
				if (minoT[i] >= breakDelay)
				{
					DestroyMinoAnim(i, DeltaTime);
				}
			}
			
		}
		else
		{
			if (currentTetrimino == nullptr) 
			{
				tTetrimino += DeltaTime;
				if (tTetrimino >= timeBetweenTetriminos - extraMoveTIme) 
				{
					SpawnTetrimino();
				}
			}
			else
			{
				tTetrimino = 0.f;
			}
		}


		if (!extraTime) 
		{
			tExtraTime = extraMoveTIme;
			if (currentTetrimino != nullptr) 
			{
				if (isSpedUp) 
				{
					tTetriminoMoveTime += (DeltaTime * tetriminoSpeed.Z) * tetriminoSpeedMultiplier;
				}
				else
				{
					tTetriminoMoveTime += DeltaTime * tetriminoSpeed.Z;
				}
				MoveTetriminoDown(tTetriminoMoveTime);
				if (tTetriminoMoveTime >= 1.f) 
				{
					tTetriminoMoveTime = 0.f;
					currentTetrimino->SetActorLocation(FVector(currentTetrimino->GetActorLocation().X, 0.f, endPos.Z));
					startPos = endPos;
					endPos -= FVector(0.f, 0.f, 100.f);
				}
			}
			FindAllMinoCoords();
		}
		else
		{
			if (!ExtraTimeChecker()) 
			{
				tExtraTime -= DeltaTime;
				if (tExtraTime <= 0.f || isSpedUp) 
				{
					placedTetriminos.Push(currentTetrimino);
					SnapTetriminoIntoPlace();
					CheckGridForCompleteRow();
					currentTetrimino = nullptr;
					extraTime = false;
				}
			}
			else
			{
				extraTime = false;
			}
		}
	}
}

void ATetrisGrid::MoveTetrimino(FVector dir)
{
	if (currentTetrimino != nullptr) 
	{
		currentTetrimino->SetActorLocation(currentTetrimino->GetActorLocation() - dir);
		UpdateGhostBlockPositions();
	}
}

void ATetrisGrid::MoveTetriminoDown(float t) 
{
	if (currentTetrimino != nullptr) 
	{
		if (t >= 1.f)
		{
			FVector start = FVector(currentTetrimino->GetActorLocation().X, currentTetrimino->GetActorLocation().Y, startPos.Z);
			FVector end = FVector(currentTetrimino->GetActorLocation().X, currentTetrimino->GetActorLocation().Y, endPos.Z);
			currentTetrimino->SetActorLocation(FMath::Lerp(start, end, t));
		}
	}
}

void ATetrisGrid::AssignEmptyGrid()
{
	grid.Init(FNestedArray(), rows);
	for (int i = 0; i < rows; i++)
	{
		for (int j = 0; j < columns; j++)
		{
			grid[i].A.Init(false, columns);
		}
	}
}

void ATetrisGrid::GetGridPositionFromWorldPos(FVector worldPos, int* _x, int* _y)
{
	worldPos.Y = 0.f;
	worldPos.Z += 75.f;
	for (int x = 0; x < rows; x++)
	{
		for (int y = 0; y < columns; y++)
		{
			FVector xCheck = FVector(gridStartPos.X + (-100.f * y), 0.f, 0.f);
			FVector xWorld = FVector(worldPos.X, 0.f, 0.f);
			FVector zCheck = FVector(0.f, 0.f, gridStartPos.Z + (-100.f * x));
			FVector zWorld = FVector(0.f, 0.f, worldPos.Z);
			if (FVector::Distance(xCheck, xWorld) < 1.f && FVector::Distance(zCheck, zWorld) < 99.f)
			{
				*_y = y;
				*_x = x;
				return;
			}
		}
	}
}

bool ATetrisGrid::CheckMinoRow(FVector worldPos, int x)
{
	FVector zCheck = FVector(0.f, 0.f, gridStartPos.Z + (-100.f * (x + 1)));
	FVector zWorld = FVector(0.f, 0.f, worldPos.Z);

	if (FVector::Dist(zCheck, zWorld) < 10.f)
	{
		return true;
	}
	return false;
}

int ATetrisGrid::RoundToNearestHundred(int roundVal) 
{
	return FMath::RoundToInt((roundVal + 50) / 100) * 100;
	if (roundVal % 100 != 0)
		return roundVal - (roundVal % 100);

	return roundVal;
}

bool ATetrisGrid::CanMoveDown(AActor* mino)
{
	return CanMoveDown(mino->GetActorLocation());
}

bool ATetrisGrid::CanMoveDown(FVector checkPos)
{
	int x = 0;
	int y = columns / 2;
	GetGridPositionFromWorldPos(checkPos, &x, &y);
	if (x < rows - 1)
	{
		if (grid[x + 1].A[y] == 1) // grid space is occupied
		{
			return false;
		}
	}
	return true;
}

bool ATetrisGrid::CanMoveLeft()
{
	bool returnVal = true;
	int x = 0;
	int y = columns / 2;
	TArray<AActor*> children;
	currentTetrimino->GetAttachedActors(children, true);
	for (int i = 0; i < children.Num(); i++)
	{
		GetGridPositionFromWorldPos(children[i]->GetActorLocation(), &x, &y);

		float xCheck = gridStartPos.Z + (-100.f * x);

		if (y == 0) 
		{
			returnVal = false;
		}
		else if (y > 0) 
		{
			if (grid[x].A[y - 1] == 1) 
			{
				returnVal = false;
			}
		}
	}
	return returnVal;
}

bool ATetrisGrid::CanMoveRight()
{
	bool returnVal = true;
	int x = 0;
	int y = columns / 2;
	TArray<AActor*> children;
	currentTetrimino->GetAttachedActors(children, true);
	for (int i = 0; i < children.Num(); i++)
	{
		GetGridPositionFromWorldPos(children[i]->GetActorLocation(), &x, &y);

		float xCheck = gridStartPos.Z + (-100.f * x);

		if (y == columns - 1) // At the right side of grid
		{
			returnVal = false;
		}
		else if (y < columns - 1)
		{
			if (grid[x].A[y + 1] == 1) // Mino is blocked on right side
			{
				returnVal = false;
			}
		}
	}
	return returnVal;
}

bool ATetrisGrid::CanRotateLeft()
{
	if (currentTetrimino != nullptr) 
	{
		UTetriminoComponent* tetrimino = currentTetrimino->FindComponentByClass<UTetriminoComponent>();
		if (tetrimino != nullptr) 
		{
			int index = tetrimino->currentRotationIndex - 1;
			if (index == -1) 
			{
				index = 3;
			}
			TArray<FVector> leftRotLocalOffsets = tetrimino->localOffset[index].A;
			for (int i = 0; i < leftRotLocalOffsets.Num(); i++)
			{
				FVector checkLoc = currentTetrimino->GetActorLocation() + leftRotLocalOffsets[i];
				int x = 0;
				int y = 0;
				GetGridPositionFromWorldPos(checkLoc, &x, &y);

				if (checkLoc.X < gridStartPos.X - ((columns - 1) * 100.f)
					|| checkLoc.Z < gridStartPos.Z - ((rows - 1) * 100.f)
					|| checkLoc.X > gridStartPos.X) // out of bounds check
				{
					return false;
				}
				if (grid[x].A[y] != 0) // collision check
				{
					return false;
				}
			}
		}
	}
	return true;
}

bool ATetrisGrid::CanRotateRight()
{
	if (currentTetrimino != nullptr)
	{
		UTetriminoComponent* tetrimino = currentTetrimino->FindComponentByClass<UTetriminoComponent>();
		if (tetrimino != nullptr)
		{
			int index = tetrimino->currentRotationIndex + 1;
			if (index == 4)
			{
				index = 0;
			}
			TArray<FVector> rotLocalOffsets = tetrimino->localOffset[index].A;
			for (int i = 0; i < rotLocalOffsets.Num(); i++)
			{
				FVector checkLoc = currentTetrimino->GetActorLocation() + rotLocalOffsets[i];
				int x = 0;
				int y = 0;
				GetGridPositionFromWorldPos(checkLoc, &x, &y);
				if (checkLoc.X < gridStartPos.X - ((columns - 1) * 100.f)
					|| checkLoc.Z < gridStartPos.Z - ((rows - 1) * 100.f)
					|| checkLoc.X > gridStartPos.X) // out of bounds check
				{
					return false;
				}
				if (grid[x].A[y] != 0) // collision check
				{
					return false;
				}
			}
		}
	}
	return true;
}

void ATetrisGrid::RotateTetriminoLeft()
{
	if (currentTetrimino != nullptr) 
	{
		UTetriminoComponent* tetrimino = currentTetrimino->FindComponentByClass<UTetriminoComponent>();
		TArray<AActor*> children;
		currentTetrimino->GetAttachedActors(children, true);

		int index = tetrimino->currentRotationIndex - 1;
		if (index == -1)
		{
			index = 3;
		}
		for (int i = 0; i < children.Num(); i++)
		{
			FVector minoPos = currentTetrimino->GetActorLocation() + tetrimino->localOffset[index].A[i];
			minoPos.Y = 0.f;
			children[i]->SetActorLocation(minoPos);
		}
		tetrimino->currentRotationIndex = index;
		UpdateGhostBlockPositions();
	}
}

void ATetrisGrid::RotateTetriminoRight()
{
	if (currentTetrimino != nullptr)
	{
		UTetriminoComponent* tetrimino = currentTetrimino->FindComponentByClass<UTetriminoComponent>();
		TArray<AActor*> children;
		currentTetrimino->GetAttachedActors(children, true);

		int index = tetrimino->currentRotationIndex + 1;
		if (index == 4)
		{
			index = 0;
		}
		for (int i = 0; i < children.Num(); i++)
		{
			FVector minoPos = currentTetrimino->GetActorLocation() + tetrimino->localOffset[index].A[i];
			minoPos.Y = 0.f;
			children[i]->SetActorLocation(minoPos);
		}
		tetrimino->currentRotationIndex = index;
		UpdateGhostBlockPositions();
	}
}

void ATetrisGrid::SpeedTetriminoUp()
{
	isSpedUp = !isSpedUp;
}

void ATetrisGrid::FindAllMinoCoords()
{
	if (currentTetrimino != nullptr) 
	{
		TArray<AActor*> children;
		currentTetrimino->GetAttachedActors(children, true);

		for (int i = 0; i < children.Num(); i++)
		{
			int x = 0;
			int y = 0;
			GetGridPositionFromWorldPos(children[i]->GetActorLocation(), &x, &y);
			if (x == rows - 1 || !CanMoveDown(children[i])) // at the bottom or something is below
			{
				extraTime = true;
			}
		}
		
	}
}

bool ATetrisGrid::ExtraTimeChecker() 
{
	if (currentTetrimino != nullptr)
	{
		int minoCanMoveDownCount = 0;

		TArray<AActor*> children;
		currentTetrimino->GetAttachedActors(children, true);

		for (int i = 0; i < children.Num(); i++) // loop over all the minos
		{
			int x = 0;
			int y = 0;
			GetGridPositionFromWorldPos(children[i]->GetActorLocation(), &x, &y);
			if (x != rows - 1 && CanMoveDown(children[i])) // at the bottom or something is below
			{
				minoCanMoveDownCount++;
			}
		}
		if (minoCanMoveDownCount == children.Num()) // all the minos are able to move down
		{
			return true;
		}
	}
	return false;
}

void ATetrisGrid::SnapTetriminoIntoPlace()
{
	if (currentTetrimino != nullptr) 
	{
		int x = 0;
		int y = 0;
		TArray<AActor*> children;
		currentTetrimino->GetAttachedActors(children, true);
		for (int i = 0; i < children.Num(); i++)
		{
			GetGridPositionFromWorldPos(children[i]->GetActorLocation(), &x, &y);
			grid[x].A[y] = 1;
		}
	}
}

void ATetrisGrid::CheckGridForCompleteRow()
{
	int rowCounter = 0;
	int _maxX = 0;
	for (int x = 0; x < rows; x++)
	{
		if (CheckRow(x)) 
		{
			completedRows.Add(x);
			rowCounter++;
			_maxX = x;
			DeleteRow(x);
		}
	}
	maxX = _maxX;
}

bool ATetrisGrid::CheckRow(int x)
{
	for (int y = 0; y < columns; y++)
	{
		if (grid[x].A[y] == 0) // Nothing on grid space
		{
			return false; // row is not full
		}
	}
	return true; // false case not met, row is full
}

void ATetrisGrid::DeleteRow(int _x)
{
	TArray<AActor*> destroyees;
	for (int i = 0; i < placedTetriminos.Num(); i++)
	{
		if (placedTetriminos[i] != nullptr) 
		{
			if (!placedTetriminos[i]->IsPendingKill()) 
			{
				TArray<AActor*> children;
				placedTetriminos[i]->GetAttachedActors(children, true);

				if (children.Num() != 0)
				{
					int x = 0;
					int y = 0;

					for (int j = 0; j < children.Num(); j++)
					{
						FVector childPos = placedTetriminos[i]->GetActorLocation() - children[j]->GetActorLocation();
						if (CheckMinoRow(children[j]->GetActorLocation(), _x))
						{
							destroyees.Add(children[j]);
							grid[x].A[y] = 0; // returning to empty slot
						}
					}
				}
			}
		}
	}

	for (auto i = 0; i < destroyees.Num(); i++)
	{
		DestroyMino(destroyees[i]);
	}
}

void ATetrisGrid::CleanUpPlacedTetriminos() 
{
	for (int i = 0; i < placedTetriminos.Num(); i++)
	{
		if (placedTetriminos[i] != nullptr)
		{
			if (!placedTetriminos[i]->IsPendingKill())
			{
				TArray<AActor*> children;
				placedTetriminos[i]->GetAttachedActors(children, true);

				if (children.Num() == 0)
				{
					AActor* temp = placedTetriminos[i];
					placedTetriminos.RemoveAt(i);
					temp->Destroy();
				}
			}
		}
	}
}

void ATetrisGrid::MoveArrayElementsDown() 
{
	destroyedMinos = 0;
	timeOutT = 0.f;
	minosToDestroy.Empty();
	minoT.Empty();		

	for (auto i = 0; i < completedRows.Num(); i++)
	{
		for (auto j = 0; j < placedTetriminos.Num(); j++)
		{
			if (placedTetriminos[j] != nullptr && !placedTetriminos[j]->IsPendingKill()) 
			{
				TArray<AActor*> children;
				int _x = 0;
				int _y = 0;
				placedTetriminos[j]->GetAttachedActors(children, true);
				for (int k = 0; k < children.Num(); k++)
				{
					GetGridPositionFromWorldPos(children[k]->GetActorLocation(), &_x, &_y);
					if (_x < completedRows[i])
					{
						children[k]->SetActorLocation(children[k]->GetActorLocation() - FVector(0.f, 0.f, 100.f));
					}
				}
			}
		}
	}

	for (auto i = 0; i < completedRows.Num(); i++)
	{
		for (auto j = rows - 1; j >= 0; j--)
		{
			if (j < completedRows[i]) 
			{
				for (auto k = 0; k < columns; k++)
				{
					if (j < completedRows[i])
					{
						grid[j + 1].A[k] = grid[j].A[k];
						grid[j].A[k] = 0;
					}
				}
			}
		}
	}

	int lineIncrease = completedRows.Num() == 4 ? 8 : completedRows.Num();

	lineCounter += lineIncrease;
	IncreaseScore(completedRows.Num());
	if (lineCounter >= linesToIncreaseLevel) 
	{
		lineCounter = lineCounter - linesToIncreaseLevel;
		IncreaseLevel();
	}

	completedRows.Empty();

}

void ATetrisGrid::RefreshGrid()
{
	for (int i = 0; i < rows; i++)
	{
		for (int j = 0; j < columns; j++)
		{
			grid[i].A[j] = 0;
		}
	}
	for (int i = 0; i < placedTetriminos.Num(); i++)
	{
		TArray<AActor*> children;
		placedTetriminos[i]->GetAttachedActors(children, true);
		
		int x = 0;
		int y = 0;

		for (int j  = 0; j < children.Num(); j++)
		{
			GetGridPositionFromWorldPos(children[j]->GetActorLocation(), &x, &y);
			grid[x].A[y] = 1;
		}
	}
}

void ATetrisGrid::DestroyMino(AActor* mino)
{
	int index = 0;
	int temp = 0;
	GetGridPositionFromWorldPos(mino->GetActorLocation(), &temp, &index);
	minoT.Add(breakDelay - (breakDelay * index));
	minosToDestroy.Add(mino);
}

void ATetrisGrid::DestroyMinoAnim(int index, float deltaTime)
{
	float t = minoT[index] - breakDelay;
	AActor* mino = minosToDestroy[index];
	if (mino == nullptr) 
	{
		return;
	}
	FRotator currentRot = mino->GetActorRotation();
	FRotator rotChange = FRotator(0.f, spinSpeed * deltaTime, 0.f);
	FVector startScale = FVector(1.f, 1.f, 1.f);
	FVector endScale = FVector(0.f, 0.f, 0.f);
	if (t <= 0.3f) 
	{
		// start spin 
		mino->SetActorRotation(currentRot + (rotChange * t));
	}
	else if (t <= breakLength)
	{
		// spin and reduce scale to 0
		mino->SetActorRotation(currentRot + (rotChange * (t + t)));
		float lerpT = (t - 0.3f) / breakLength;
		FVector scaleLerp = FMath::Lerp(startScale, FVector::ZeroVector, lerpT);
		mino->SetActorScale3D(scaleLerp);
	}
	else if (t > breakLength) 
	{
		// Remove from arrays
		minosToDestroy[index] = nullptr;
		minoT[index] = -100;
		// Destroy mino
		mino->Destroy();
		destroyedMinos++;
	}


}

void ATetrisGrid::SpawnGhostBlocks()
{
	if (ghostBlockPrefab != nullptr) 
	{
		FActorSpawnParameters spawnParams;
		FVector spawnPos = FVector(0.f, -10000.f, 0.f);
		AActor* tempGhostBlock = GetWorld()->SpawnActor<AActor>(ghostBlockPrefab, spawnPos, spawnRot, spawnParams);
		ghostBlock = tempGhostBlock;
		tempGhostBlock->GetAttachedActors(ghostBlockChildren, true);
	}
}

void ATetrisGrid::UpdateGhostBlockPositions()
{
	if (currentTetrimino != nullptr && ghostBlock != nullptr) 
	{
		UTetriminoComponent* tetrimino = currentTetrimino->FindComponentByClass<UTetriminoComponent>();

		TArray<AActor*> tetriminoChildren;
		currentTetrimino->GetAttachedActors(tetriminoChildren, true);

		FVector ghostBlockParentVector = FVector(currentTetrimino->GetActorLocation().X, 0.f, gridStartPos.Z);

		bool masterBreakCase = false;

		for (int i = 0; i < rows; i++)
		{
			for (int j = 0; j < tetriminoChildren.Num(); j++)
			{
				FVector checkPos = ghostBlockParentVector + (currentTetrimino->GetActorLocation() - tetriminoChildren[j]->GetActorLocation());
				int x = 0;
				int y = 0;
				GetGridPositionFromWorldPos(checkPos, &x, &y);
				if (x == rows || !CanMoveDown(checkPos)) // at the bottom or something is below
				{
					masterBreakCase = true;
					break;
				}
			}
			if (masterBreakCase) 
			{
				break;
			}
			ghostBlockParentVector -= FVector(0.f, 0.f, 100.f);
		}

		ghostBlock->SetActorLocation(ghostBlockParentVector);

		for (int i = 0; i < tetriminoChildren.Num(); i++)
		{
			FVector minoPos = ghostBlockParentVector + (tetriminoChildren[i]->GetActorLocation() - currentTetrimino->GetActorLocation());
			minoPos = FVector(minoPos.X, 0.f, minoPos.Z);
			ghostBlockChildren[i]->SetActorLocation(minoPos);
		}
	}

}

void ATetrisGrid::IncreaseLevel()
{
	level++;
	linesToIncreaseLevel += linesToIncreaseLevelIncrease;
	tetriminoSpeed.Z += tetriminoSpeedIncrease;
	if (AGameHUD* gameHUD = Cast<AGameHUD>(UGameplayStatics::GetPlayerController(GetWorld(), 0)->GetHUD()))
	{
		gameHUD->SetLevel(level);
	}
}

void ATetrisGrid::IncreaseScore(int _completedRows)
{
	int increase = 40;
	if (_completedRows == 2)
	{
		increase = 100;
	}
	else if (_completedRows == 3)
	{
		increase = 400;
	}
	else if (_completedRows == 4)
	{
		increase = 1200;
	}
	score += increase * (level + 1);

	if (HUDinstance) 
	{
		HUDinstance->SetScore(score);
	}
	
}

void ATetrisGrid::ResetGame()
{
	if (currentTetrimino != nullptr) 
	{
		currentTetrimino->Destroy();
		currentTetrimino = nullptr;
	}

	gameOver = false;

	availableIndexes.Empty();
	availableIndexes.Add(0);
	availableIndexes.Add(1);
	availableIndexes.Add(2);
	availableIndexes.Add(3);
	availableIndexes.Add(4);
	availableIndexes.Add(5);
	availableIndexes.Add(6);

	for (int i = 0; i < placedTetriminos.Num(); i++) 
	{
		if (placedTetriminos[i] != nullptr) 
		{
			if (!placedTetriminos[i]->IsPendingKill()) 
			{
				placedTetriminos[i]->Destroy();
			}
		}
	}
	placedTetriminos.Empty();

	for (int i = 0; i < looseTetriminos.Num(); i++)
	{
		if (looseTetriminos[i] != nullptr) 
		{
			if (looseTetriminos[i]->IsValidLowLevel()) 
			{
				if (!looseTetriminos[i]->IsPendingKill()) 
				{
					looseTetriminos[i]->Destroy();
				}
			}
		}
	}
	looseTetriminos.Empty();


	score = 0;
	level = 0;
	linesToIncreaseLevel = 10;
	if (HUDinstance)
	{
		HUDinstance->SetScore(score);
		HUDinstance->SetLevel(level);
	}
	RefreshGrid();
}

FVector ATetrisGrid::VectorLerp(FVector a, FVector b, float t) 
{
	if (t > 1.f) { t = 1.f; }
	if (t > 0.f) { t = 0.f; }

	return a + (b - a) * t;
}


