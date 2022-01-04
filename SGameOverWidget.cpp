// Fill out your copyright notice in the Description page of Project Settings.


#include "SGameOverWidget.h"
#include "GameHUD.h"
#include "GameFramework/PlayerController.h"
#include "SlateOptMacros.h"

BEGIN_SLATE_FUNCTION_BUILD_OPTIMIZATION
void SGameOverWidget::Construct(const FArguments& InArgs)
{
	owningHUD = InArgs._owningHUD;

	const FMargin ContentPadding = FMargin(0, 50.f);

	FSlateFontInfo TitleTextStyle = FCoreStyle::Get().GetFontStyle("EmbossedText");
	TitleTextStyle.Size = 70.f;

	FSlateFontInfo ButtonTextTextStyle = FCoreStyle::Get().GetFontStyle("EmbossedText");
	ButtonTextTextStyle.Size = 40.f;

	FSlateFontInfo scoreAndLevelTextStyle = FCoreStyle::Get().GetFontStyle("EmbossedText");
	scoreAndLevelTextStyle.Size = 80.f;

	FText scoreText = FText::FromString("Score = " + FString::FromInt(owningHUD->score) + "        " + "Level = " + FString::FromInt(owningHUD->level));;

	ChildSlot
		[
			// Populate the widget
			SNew(SOverlay)
			+ SOverlay::Slot()
			.HAlign(HAlign_Center)
			.VAlign(VAlign_Center)
			[
				SNew(SVerticalBox)
				+ SVerticalBox::Slot()
				.Padding(ContentPadding)
				[
					SNew(STextBlock)
					.Font(TitleTextStyle)
					.Text(FText::FromString("Game Over"))
					.Justification(ETextJustify::Center)
				]
				+ SVerticalBox::Slot()
				.Padding(ContentPadding)
				[
					SNew(STextBlock)
					.Font(TitleTextStyle)
					.Text(scoreText)
					.Justification(ETextJustify::Center)
				]
				+ SVerticalBox::Slot()
				.Padding(ContentPadding)
				[
					SNew(SButton)
					.OnClicked(this, &SGameOverWidget::Replay)
				[	
					SNew(STextBlock)
					.Font(ButtonTextTextStyle)
					.Text(FText::FromString("Replay"))
					.Justification(ETextJustify::Center)
				]
			]
			+ SVerticalBox::Slot()
			.Padding(ContentPadding)
			[
				SNew(SButton)
				.OnClicked(this, &SGameOverWidget::QuitToMenu)
				[
				SNew(STextBlock)
				.Font(ButtonTextTextStyle)
				.Text(FText::FromString("Quit to Menu"))
				.Justification(ETextJustify::Center)
				]
			]
			+ SVerticalBox::Slot()
			.Padding(ContentPadding)
			[
				SNew(SButton)
				.OnClicked(this, &SGameOverWidget::QuitToDesktop)
				[
				SNew(STextBlock)
				.Font(ButtonTextTextStyle)
				.Text(FText::FromString("Quit To Desktop"))
				.Justification(ETextJustify::Center)
				]
			]
		]
	];
}
FReply SGameOverWidget::Replay()
{
	if (owningHUD.IsValid())
	{
		owningHUD->requiresReset = true;
		owningHUD->ShowGameScreen();
	}
	return FReply::Handled();
}
FReply SGameOverWidget::QuitToMenu()
{
	if (owningHUD.IsValid())
	{
		owningHUD->RemoveGameOverScreen();
		owningHUD->ShowMainMenu();
		owningHUD->requiresReset = true;
	}
	return FReply::Handled();
}
FReply SGameOverWidget::QuitToDesktop()
{
	if (owningHUD.IsValid())
	{
		if (APlayerController* PC = owningHUD->PlayerOwner)
		{
			PC->ConsoleCommand("quit");
		}
	}

	return FReply::Handled();
}
END_SLATE_FUNCTION_BUILD_OPTIMIZATION
