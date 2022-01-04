// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

// code adapted from Ward, R (2020) Retrieved from: https://www.youtube.com/watch?v=jeK6DPB5weA&t=860s

#include "Widgets/SCompoundWidget.h"

/**
 * 
 */
class SGameWidget : public SCompoundWidget
{
public:
	SLATE_BEGIN_ARGS(SGameWidget) {}
	
	SLATE_ARGUMENT(TWeakObjectPtr<class AGameHUD>, owningHUD)

	SLATE_END_ARGS()

	/** Constructs this widget with InArgs */
	void Construct(const FArguments& InArgs);

	TWeakObjectPtr<class AGameHUD> owningHUD;

	virtual bool SupportsKeyboardFocus() const override { return true; };

};

// end of adapted code