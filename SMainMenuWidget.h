// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "SlateBasics.h"
#include "SlateExtras.h"
#include "Widgets/SCompoundWidget.h"

/**
 * 
 */
class TETRIS_API SMainMenuWidget : public SCompoundWidget
{
public:
	SLATE_BEGIN_ARGS(SMainMenuWidget)
	{}

	SLATE_ARGUMENT(TWeakObjectPtr<class AGameHUD>, owningHUD)

	SLATE_END_ARGS()

	/** Constructs this widget with InArgs */
	void Construct(const FArguments& InArgs);

	TWeakObjectPtr<class AGameHUD> owningHUD;

	virtual bool SupportsKeyboardFocus() const override { return true; };

	FReply PlayGame() const;

	FReply QuitGame() const;
};
