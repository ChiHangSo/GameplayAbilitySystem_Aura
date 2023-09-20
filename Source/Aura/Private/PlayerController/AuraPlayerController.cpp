// Copyright ChiHangSo


#include "PlayerController/AuraPlayerController.h"
#include "EnhancedInputSubsystems.h"

AAuraPlayerController::AAuraPlayerController()
{
	bReplicates = true;


}

void AAuraPlayerController::BeginPlay()
{
	Super::BeginPlay();

	//This macro here will help tell the game if it's set if not the game will crash.
	check(AuraContext);

	// This is to access the input mapping locally for the player to move
	UEnhancedInputLocalPlayerSubsystem* Subsystem = ULocalPlayer::GetSubsystem<UEnhancedInputLocalPlayerSubsystem>(GetLocalPlayer());
	check(Subsystem);
	Subsystem->AddMappingContext(AuraContext, 0);

	// This is to show the mouse while playing
	bShowMouseCursor = true;
	DefaultMouseCursor = EMouseCursor::Default;

	// This sets the mode of how we want the mouse and widgets to interact.
	FInputModeGameAndUI InputModeData;
	InputModeData.SetLockMouseToViewportBehavior(EMouseLockMode::DoNotLock);
	InputModeData.SetHideCursorDuringCapture(false);
	SetInputMode(InputModeData);

}
