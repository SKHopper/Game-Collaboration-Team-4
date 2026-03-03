// Copyright Epic Games, Inc. All Rights Reserved.


#include "Unit_2b_Team_4PlayerController.h"
#include "EnhancedInputSubsystems.h"
#include "Engine/LocalPlayer.h"
#include "InputMappingContext.h"
#include "Unit_2b_Team_4CameraManager.h"
#include "Blueprint/UserWidget.h"
#include "Unit_2b_Team_4.h"
#include "Widgets/Input/SVirtualJoystick.h"

AUnit_2b_Team_4PlayerController::AUnit_2b_Team_4PlayerController()
{
	// set the player camera manager class
	PlayerCameraManagerClass = AUnit_2b_Team_4CameraManager::StaticClass();
}

void AUnit_2b_Team_4PlayerController::BeginPlay()
{
	Super::BeginPlay();

	
	// only spawn touch controls on local player controllers
	if (SVirtualJoystick::ShouldDisplayTouchInterface() && IsLocalPlayerController())
	{
		// spawn the mobile controls widget
		MobileControlsWidget = CreateWidget<UUserWidget>(this, MobileControlsWidgetClass);

		if (MobileControlsWidget)
		{
			// add the controls to the player screen
			MobileControlsWidget->AddToPlayerScreen(0);

		} else {

			UE_LOG(LogUnit_2b_Team_4, Error, TEXT("Could not spawn mobile controls widget."));

		}

	}
}

void AUnit_2b_Team_4PlayerController::SetupInputComponent()
{
	Super::SetupInputComponent();

	// only add IMCs for local player controllers
	if (IsLocalPlayerController())
	{
		// Add Input Mapping Context
		if (UEnhancedInputLocalPlayerSubsystem* Subsystem = ULocalPlayer::GetSubsystem<UEnhancedInputLocalPlayerSubsystem>(GetLocalPlayer()))
		{
			for (UInputMappingContext* CurrentContext : DefaultMappingContexts)
			{
				Subsystem->AddMappingContext(CurrentContext, 0);
			}

			// only add these IMCs if we're not using mobile touch input
			if (!SVirtualJoystick::ShouldDisplayTouchInterface())
			{
				for (UInputMappingContext* CurrentContext : MobileExcludedMappingContexts)
				{
					Subsystem->AddMappingContext(CurrentContext, 0);
				}
			}
		}
	}
	
}
