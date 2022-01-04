// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Widgets/SCompoundWidget.h"

/**
 * 
 */
class TETRIS_API SGameOverWidget : public SCompoundWidget
{
public:
	SLATE_BEGIN_ARGS(SGameOverWidget)
	{}

	SLATE_ARGUMENT(TWeakObjectPtr<class AGameHUD>, owningHUD)

	SLATE_END_ARGS()

	/** Constructs this widget with InArgs */
	void Construct(const FArguments& InArgs);

	TWeakObjectPtr<class AGameHUD> owningHUD;

	FReply Replay();

	FReply QuitToMenu();

	FReply QuitToDesktop();
};
