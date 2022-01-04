// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Widgets/SCompoundWidget.h"

/**
 * 
 */
class TETRIS_API SPauseWidget : public SCompoundWidget
{
public:
	SLATE_BEGIN_ARGS(SPauseWidget)
	{}

	SLATE_ARGUMENT(TWeakObjectPtr<class AGameHUD>, owningHUD)

	SLATE_END_ARGS()

	TWeakObjectPtr<class AGameHUD> owningHUD;

	/** Constructs this widget with InArgs */
	void Construct(const FArguments& InArgs);

	FReply Resume();
	
	FReply Restart();

	FReply QuitToMenu();

	FReply QuitToDesktop(); 
};
