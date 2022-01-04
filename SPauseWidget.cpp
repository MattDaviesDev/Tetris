// Fill out your copyright notice in the Description page of Project Settings.


#include "SPauseWidget.h"
#include "GameHUD.h"
#include "GameFramework/PlayerController.h"
#include "SlateOptMacros.h"

BEGIN_SLATE_FUNCTION_BUILD_OPTIMIZATION
void SPauseWidget::Construct(const FArguments& InArgs)
{
	owningHUD = InArgs._owningHUD;

	const FMargin ContentPadding = FMargin(0, 50.f);

	FSlateFontInfo TitleTextStyle = FCoreStyle::Get().GetFontStyle("EmbossedText");
	TitleTextStyle.Size = 70.f;

	FSlateFontInfo ButtonTextTextStyle = FCoreStyle::Get().GetFontStyle("EmbossedText");
	ButtonTextTextStyle.Size = 40.f;

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
				.Text(FText::FromString("Paused"))
				.Justification(ETextJustify::Center)
				]
				+ SVerticalBox::Slot()
				.Padding(ContentPadding)
				[
					SNew(SButton)
					.OnClicked(this, &SPauseWidget::Resume)
					[
						SNew(STextBlock)
						.Font(ButtonTextTextStyle)
						.Text(FText::FromString("Resume"))
						.Justification(ETextJustify::Center)
					]
				]
				+ SVerticalBox::Slot()
					.Padding(ContentPadding)
					[
						SNew(SButton)
						.OnClicked(this, &SPauseWidget::Restart)
					[
						SNew(STextBlock)
						.Font(ButtonTextTextStyle)
					.Text(FText::FromString("Restart"))
					.Justification(ETextJustify::Center)
					]

					]
				+ SVerticalBox::Slot()
				.Padding(ContentPadding)
				[
					SNew(SButton)
					.OnClicked(this, &SPauseWidget::QuitToMenu)
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
					.OnClicked(this, &SPauseWidget::QuitToDesktop)
					[
						SNew(STextBlock)
						.Font(ButtonTextTextStyle)
						.Text(FText::FromString("Quit to Desktop"))
						.Justification(ETextJustify::Center)
					]
				]
			]
		];
}


FReply SPauseWidget::Resume()
{
	if (owningHUD.IsValid()) 
	{
		owningHUD->isPlaying = true;
		owningHUD->ShowGameScreen();
	}
	return FReply::Handled();
}

FReply SPauseWidget::Restart()
{
	if (owningHUD.IsValid())
	{
		owningHUD->requiresReset = true;
		owningHUD->ShowGameScreen();
	}
	return FReply::Handled();
}

FReply SPauseWidget::QuitToMenu()
{
	if (owningHUD.IsValid())
	{
		owningHUD->requiresReset = true;
		owningHUD->ShowMainMenu();
	}
	return FReply::Handled();
}

FReply SPauseWidget::QuitToDesktop()
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
