// Fill out your copyright notice in the Description page of Project Settings.

// code adapted from Ward, R (2020) Retrieved from: https://www.youtube.com/watch?v=jeK6DPB5weA&t=860s

#include "GameHUD.h"
#include "SGameWidget.h"
#include "SGameOverWidget.h"
#include "SPauseWidget.h"
#include "SMainMenuWidget.h"
#include "GameFramework/PlayerController.h"
#include "Widgets/SWeakWidget.h"
#include "Engine/Engine.h"


void AGameHUD::BeginPlay() 
{
	Super::BeginPlay();

	if (PlayerOwner)
	{
		PlayerOwner->bShowMouseCursor = false;
		PlayerOwner->SetInputMode(FInputModeGameOnly());
	}

	ShowMainMenu();
}

void AGameHUD::ShowMainMenu()
{
	if (GEngine && GEngine->GameViewport)
	{
		RemoveGameScreen();
		RemovePauseScreen();

		menuWidget = SNew(SMainMenuWidget).owningHUD(this);
		GEngine->GameViewport->AddViewportWidgetContent(SAssignNew(menuWidgetContainer, SWeakWidget).PossiblyNullContent(menuWidget.ToSharedRef()));
		
		PlayerOwner->bShowMouseCursor = true	;
		PlayerOwner->SetInputMode(FInputModeUIOnly());
	}
}

void AGameHUD::RemoveMainMenu()
{
	if (GEngine && GEngine->GameViewport && menuWidgetContainer.IsValid()) 
	{
		GEngine->GameViewport->RemoveViewportWidgetContent(menuWidgetContainer.ToSharedRef());
	}
}

void AGameHUD::ShowPauseScreen()
{
	if (GEngine && GEngine->GameViewport)
	{
		RemoveGameScreen();

		pauseWidget = SNew(SPauseWidget).owningHUD(this);
		GEngine->GameViewport->AddViewportWidgetContent(SAssignNew(pauseWidgetContainer, SWeakWidget).PossiblyNullContent(pauseWidget.ToSharedRef()));
	}
}

void AGameHUD::RemovePauseScreen()
{
	if (GEngine && GEngine->GameViewport && pauseWidgetContainer.IsValid())
	{
		GEngine->GameViewport->RemoveViewportWidgetContent(pauseWidgetContainer.ToSharedRef());
	}
}

void AGameHUD::ShowGameScreen()
{
	if (GEngine && GEngine->GameViewport) 
	{
		RemoveMainMenu();
		RemovePauseScreen();
		RemoveGameOverScreen();
		
		isPlaying = true;

		gameWidget = SNew(SGameWidget).owningHUD(this);
		GEngine->GameViewport->AddViewportWidgetContent(SAssignNew(gameWidgetContainer, SWeakWidget).PossiblyNullContent(gameWidget.ToSharedRef()));

		if (PlayerOwner)
		{
			PlayerOwner->bShowMouseCursor = false;
			PlayerOwner->SetInputMode(FInputModeGameOnly());
		}
	}
}

void AGameHUD::RemoveGameScreen()
{
	if (GEngine && GEngine->GameViewport && gameWidgetContainer.IsValid())
	{
		GEngine->GameViewport->RemoveViewportWidgetContent(gameWidgetContainer.ToSharedRef());

		isPlaying = false;

		if (PlayerOwner)
		{
			PlayerOwner->bShowMouseCursor = true;
			PlayerOwner->SetInputMode(FInputModeUIOnly());
		}
	}
}

void AGameHUD::ShowGameOverScreen()
{
	if (GEngine && GEngine->GameViewport)
	{
		RemoveGameScreen();

		isPlaying = false;

		gameOverWidget = SNew(SGameOverWidget).owningHUD(this);
		GEngine->GameViewport->AddViewportWidgetContent(SAssignNew(gameOverWidgetContainer, SWeakWidget).PossiblyNullContent(gameOverWidget.ToSharedRef()));

		if (PlayerOwner)
		{
			PlayerOwner->bShowMouseCursor = true;
			PlayerOwner->SetInputMode(FInputModeUIOnly());
		}
	}
}

void AGameHUD::RemoveGameOverScreen()
{
	if (GEngine && GEngine->GameViewport && gameOverWidgetContainer.IsValid())
	{
		GEngine->GameViewport->RemoveViewportWidgetContent(gameOverWidgetContainer.ToSharedRef());
	}
}


// end of adapted code