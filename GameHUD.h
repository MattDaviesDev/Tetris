// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

// code adapted from Ward, R (2020) Retrieved from: https://www.youtube.com/watch?v=jeK6DPB5weA&t=860s


#include "CoreMinimal.h"
#include "GameFramework/HUD.h"
#include "GameHUD.generated.h"

/**
 * 
 */
UCLASS()
class TETRIS_API AGameHUD : public AHUD
{
	GENERATED_BODY()

private:

	
protected:
	virtual void BeginPlay() override;

	TSharedPtr<class SGameWidget> gameWidget;
	TSharedPtr<class SWidget> gameWidgetContainer;

	TSharedPtr<class SMainMenuWidget> menuWidget;
	TSharedPtr<class SWidget> menuWidgetContainer;

	TSharedPtr<class SPauseWidget> pauseWidget;
	TSharedPtr<class SWidget> pauseWidgetContainer;

	TSharedPtr<class SGameOverWidget> gameOverWidget;
	TSharedPtr<class SWidget> gameOverWidgetContainer;

public:
	
	FText GetScoreString() const { return FText::FromString("Score\n" + FString::FromInt(score)); }

	FText GetLevelString() const { return FText::FromString("Level\n" + FString::FromInt(level)); }

	void SetLevel(int _level) { level = _level; }

	void SetScore(int _score) { score = _score; }

	void ShowMainMenu();
	void RemoveMainMenu();

	void ShowPauseScreen();
	void RemovePauseScreen();
	
	void ShowGameScreen();
	void RemoveGameScreen();

	void ShowGameOverScreen();
	void RemoveGameOverScreen();

	bool isPlaying;

	int score = 0;
	int level = 0;

	bool requiresReset = false;
};

// end of adapted code