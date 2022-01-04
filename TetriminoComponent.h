// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "TetriminoComponent.generated.h"

USTRUCT()
struct TETRIS_API FNestedVector
{
	GENERATED_USTRUCT_BODY()

		UPROPERTY(EditAnywhere)
		TArray<FVector> A;

public:
	FNestedVector()
	{

	}
};

UENUM()
enum TetriminoType
{
	Blue UMETA(DisplayName = "Blue"),
	DarkBlue      UMETA(DisplayName = "Dark Blue"),
	Yellow   UMETA(DisplayName = "Yellow"),
	Red   UMETA(DisplayName = "Red"),
	Green   UMETA(DisplayName = "Green"),
	Orange   UMETA(DisplayName = "Orange"),
	Purple   UMETA(DisplayName = "Purple"),
};

UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class TETRIS_API UTetriminoComponent : public UActorComponent
{
	GENERATED_BODY()

public:	

	

	// Sets default values for this component's properties
	UTetriminoComponent();

	TArray<AActor*> minos;

	int minoIndexes[4][2];

	UPROPERTY(EditAnywhere)
		int currentRotationIndex = 0;

	UPROPERTY(EditAnywhere)
		TArray<FNestedVector> localOffset;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Status)
		TEnumAsByte<TetriminoType> tetriminoType;

protected:
	// Called when the game starts
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

	void AssignOffset();
		
};
