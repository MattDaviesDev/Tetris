// Fill out your copyright notice in the Description page of Project Settings.


// code adapted from Ward, R (2020) Retrieved from: https://www.youtube.com/watch?v=jeK6DPB5weA&t=860s
// code adapted from antithing. (2018). Retrieved from https://answers.unrealengine.com/questions/834717/slate-ui-textblock-text-lambda-to-update-the-text.html.

#include "SGameWidget.h"
#include "GameHUD.h"
#include "SlateOptMacros.h"

BEGIN_SLATE_FUNCTION_BUILD_OPTIMIZATION
void SGameWidget::Construct(const FArguments& InArgs)
{
	owningHUD = InArgs._owningHUD;

	const FMargin ScorePadding = FMargin(0.f, 100.f);
	const FMargin LevelPadding = FMargin(0.f, 0.f);

	FSlateFontInfo scoreAndLevelTextStyle = FCoreStyle::Get().GetFontStyle("EmbossedText");
	scoreAndLevelTextStyle.Size = 80.f;

	ChildSlot
		[
			// Populate the widget
			SNew(SOverlay)
			+ SOverlay::Slot()
			.HAlign(HAlign_Fill)
			.VAlign(VAlign_Fill)
			.Padding(ScorePadding)
			[
				SNew(SHorizontalBox)
				+ SHorizontalBox::Slot()
				[
					SNew(STextBlock)
					.Font(scoreAndLevelTextStyle)
					.Text(owningHUD->GetScoreString())
					.Justification(ETextJustify::Center)
					.Text_Lambda([this]()->FText {return owningHUD->GetScoreString(); })
				]
				+ SHorizontalBox::Slot()
				.Padding(LevelPadding)
				[
					SNew(STextBlock)
					.Font(scoreAndLevelTextStyle)
					.Text(owningHUD->GetLevelString())
					.Justification(ETextJustify::Center)
					.Text_Lambda([this]()->FText {return owningHUD->GetLevelString(); })
				]
			]
		];

}
END_SLATE_FUNCTION_BUILD_OPTIMIZATION

// end of adapted code


// Slate Lambda reference 
// antithing. (2018). Slate UI TextBlock, Text_Lambda to update the Text? - UE4 AnswerHub. Answers.unrealengine.com. Retrieved 22 April 2021, from https://answers.unrealengine.com/questions/834717/slate-ui-textblock-text-lambda-to-update-the-text.html.
