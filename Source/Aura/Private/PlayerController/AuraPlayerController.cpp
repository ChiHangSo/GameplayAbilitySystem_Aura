// Copyright ChiHangSo


#include "PlayerController/AuraPlayerController.h"
#include "EnhancedInputSubsystems.h"
#include "EnhancedInputComponent.h"

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
	// This adds the mapping context
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

void AAuraPlayerController::SetupInputComponent()
{
	Super::SetupInputComponent();

	// This will help us check if this cast will crash
	// This helps keep track of our pointer of the input
	UEnhancedInputComponent* EnhancedInputComponent = CastChecked<UEnhancedInputComponent>(InputComponent);

	// We want to bind the action everytime the key is triggered and we want to tell to use the move action to actually move the player
	EnhancedInputComponent->BindAction(MoveAction, ETriggerEvent::Triggered, this, &AAuraPlayerController::Move);
}

void AAuraPlayerController::Move(const FInputActionValue& InputActionValue)
{
	// This helps us get the vector in 2d (We use the .Get)
	const FVector2D InputAxisVector = InputActionValue.Get<FVector2D>();

	// These are rotations that we can use to get our foward vector
	const FRotator Rotation = GetControlRotation();
	const FRotator YawRotation(0.f, Rotation.Yaw, 0.f);

	const FVector FowardDirection = FRotationMatrix(YawRotation).GetUnitAxis(EAxis::X);
	const FVector RightDirection = FRotationMatrix(YawRotation).GetUnitAxis(EAxis::Y);

	// We wrap this in an if statement to track the pointer
	if (APawn* ControlledPawn = GetPawn<APawn>())
	{
		// We get the controlled movement with addmovement input and to make sure we are going north or south we scale it by the number in the InputAxisVector
		ControlledPawn->AddMovementInput(FowardDirection, InputAxisVector.Y);
		// Same goes with this one
		ControlledPawn->AddMovementInput(RightDirection, InputAxisVector.X);
	}


}
