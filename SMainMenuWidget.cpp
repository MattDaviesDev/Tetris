// Fill out your copyright notice in the Description page of Project Settings.


#include "SMainMenuWidget.h"
#include "SlateOptMacros.h"
#include "GameHUD.h"
#include "GameFramework/PlayerController.h"
#include "TetrisGrid.h"

BEGIN_SLATE_FUNCTION_BUILD_OPTIMIZATION
void SMainMenuWidget::Construct(const FArguments& InArgs)
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
				[
					SNew(STextBlock)
					.Font(TitleTextStyle)
					.Text(FText::FromString("Tetris"))
					.Justification(ETextJustify::Center)
				]
				+ SVerticalBox::Slot()
				.Padding(ContentPadding)
				[
					SNew(SButton)
					.OnClicked(this, &SMainMenuWidget::PlayGame)
					[
						SNew(STextBlock)
						.Font(ButtonTextTextStyle)
						.Text(FText::FromString("Play!"))
						.Justification(ETextJustify::Center)
					]
					]
					+ SVerticalBox::Slot()
					[
						SNew(SButton)
						.OnClicked(this, &SMainMenuWidget::QuitGame)
						[
							SNew(STextBlock)
							.Font(ButtonTextTextStyle)
							.Text(FText::FromString("Quit"))
							.Justification(ETextJustify::Center)
						]
					]
			]
		];

}

FReply SMainMenuWidget::PlayGame() const
{
	owningHUD->ShowGameScreen();

	return FReply::Handled();
}

FReply SMainMenuWidget::QuitGame() const
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
