// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Tetrimino.h"
#include "TetrisGrid.generated.h"


USTRUCT()
struct TETRIS_API FNestedArray
{
	GENERATED_USTRUCT_BODY()


		UPROPERTY(EditAnywhere)
		TArray<int32> A;

public:
	FNestedArray() 
	{

	}
};

UCLASS()
class TETRIS_API ATetrisGrid : public AActor
{
	GENERATED_BODY()
private:

	
	
public:	
	// Sets default values for this actor's properties
	ATetrisGrid();

	ATetrisGrid* instance;

	class AGameHUD* HUDinstance;

	UPROPERTY(EditAnywhere, Category = "DEBUG")
		TArray<FString> debugMessages;

	UPROPERTY(EditAnywhere, Category = "Tetriminos")
		TSubclassOf<AActor> blackBox;

	UPROPERTY(EditAnywhere, Category = "Tetriminos")
		TSubclassOf<AActor> ghostBlockPrefab;

	AActor* ghostBlock;
	TArray<AActor*> ghostBlockChildren;

	UPROPERTY(EditAnywhere, Category = "Tetriminos")
		TArray<TSubclassOf<AActor>> TetriminoList;

	UPROPERTY(EditDefaultsOnly)
		USceneComponent* scene;

	UPROPERTY(EditAnywhere)
		FVector gridStartPos;

	UPROPERTY(EditAnywhere)
		FRotator spawnRot;

	UPROPERTY(EditAnywhere)
		FVector tetriminoSpeed;

	float moveDistTracker;

	UPROPERTY(EditAnywhere)
		float tetriminoSpeedMultiplier;

	UPROPERTY(EditAnywhere)
		FVector currentTetriminoSpeed;

	bool isSpedUp = false;

	AActor* currentTetrimino;
	FVector startPos;
	FVector endPos;
	bool isMoving;
	float tTetriminoMoveTime;


	UPROPERTY(EditAnywhere)
		TArray<FNestedArray> grid;

	UPROPERTY(EditAnywhere)
		int rows;

	UPROPERTY(EditAnywhere)
		int columns;

	UPROPERTY(EditAnywhere)
		float extraMoveTIme;

	UPROPERTY(EditAnywhere)
		float timeBetweenTetriminos;

	UPROPERTY(EditAnywhere)
		float tetriminoSpeedIncrease;

	float tTetrimino = 0.f;
	float tExtraTime = 0.f;
	bool extraTime = false;

	bool gameOver = false;

	UPROPERTY(EditAnywhere, Category = "DEBUG")
	TArray<AActor*> placedTetriminos;

	UPROPERTY(EditAnywhere)
		float breakDelay;

	UPROPERTY(EditAnywhere)
		float breakLength;

	UPROPERTY(EditAnywhere)
		float spinSpeed;

	UPROPERTY(EditAnywhere)
		TArray<AActor*> minosToDestroy;

	TArray<float> minoT;

	UPROPERTY(EditAnywhere)
		int destroyedMinos;

	float timeOutT;
	float destroyTimeOut = 3.f;

	int topLine;

	TArray<int> completedRows;
	int maxX;

	UPROPERTY(EditAnywhere)
		int score = 0;

	UPROPERTY(EditAnywhere)
		int lineCounter = 0;

	UPROPERTY(EditAnywhere)
		int level = 0;

	UPROPERTY(EditAnywhere)
		int linesToIncreaseLevel = 10;

	UPROPERTY(EditAnywhere)
		int linesToIncreaseLevelIncrease = 3;

	TArray<int> availableIndexes;
	
	TArray<AActor*> looseTetriminos;

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	void ConstructGridBorder();

	void SpawnTetrimino();

	void MoveTetriminoDown(float t);

	void AssignEmptyGrid();

	void GetGridPositionFromWorldPos(FVector worldPos, int* x, int* y);

	bool CheckMinoRow(FVector worldPos, int x);

	int RoundToNearestHundred(int roundVal);

	bool CanMoveDown(AActor* mino);

	bool CanMoveDown(FVector checkPos);

	void FindAllMinoCoords();

	bool ExtraTimeChecker();

	void SnapTetriminoIntoPlace();

	void CheckGridForCompleteRow();

	bool CheckRow(int x);

	void DeleteRow(int x);

	void CleanUpPlacedTetriminos();

	void MoveArrayElementsDown();

	void RefreshGrid();

	void DestroyMino(AActor* mino);

	void DestroyMinoAnim(int minoIndex, float deltaTime);

	void SpawnGhostBlocks();

	void UpdateGhostBlockPositions();

	void IncreaseLevel();

	void IncreaseScore(int _completedRows);

	void ResetGame();

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	void MoveTetrimino(FVector dir);

	bool CanMoveLeft();

	bool CanMoveRight();

	bool CanRotateLeft();

	bool CanRotateRight();

	void RotateTetriminoLeft();

	void RotateTetriminoRight();

	void SpeedTetriminoUp();

	FVector VectorLerp(FVector a, FVector b, float t);
};
