// Copyright June Rhodes. All Rights Reserved.

#pragma once

#include "Blueprint/UserWidget.h"
#include "CoreMinimal.h"
#include "Delegates/Delegate.h"
#include "Delegates/DelegateCombinations.h"
#include "Subsystems/GameInstanceSubsystem.h"

#include "EOSSubsystem.generated.h"

/**
 * Callback when EOS needs an operation to be performed on a widget.
 */
DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FEOSWidgetDelegate, UUserWidget *, Widget);

/**
 * Callback when EOS has attempted to refresh credentials for a local user, indicating whether or not the refresh
 * operation succeeded.
 */
DECLARE_MULTICAST_DELEGATE_OneParam(FEOSCredentialRefreshComplete, bool /* bSucceeded */);

/**
 * Provides global callbacks for EOS plugin related operations.
 */
UCLASS(BlueprintType, DisplayName = "EOS Subsystem")
class ONLINESUBSYSTEMREDPOINTEOS_API UEOSSubsystem : public UGameInstanceSubsystem
{
    GENERATED_BODY()

public:
    /**
     * Called when an authentication widget needs to be added to the viewport. You can bind a handler to this event in
     * VR games so that you can display the widget in 3D space instead. If there are no handlers bound to this event,
     * the EOS plugin will handle adding the widget to the viewport.
     */
    UPROPERTY(BlueprintAssignable, Category = "EOS|User Interface")
    FEOSWidgetDelegate OnAddWidgetToViewport;

    /**
     * Called when an authentication widget needs to be removed the viewport. You can bind a handler to this event in
     * VR games so that you can remove the widget from 3D space instead. If there are no handlers bound to this event,
     * the EOS plugin will handle removing the widget to the viewport.
     */
    UPROPERTY(BlueprintAssignable, Category = "EOS|User Interface")
    FEOSWidgetDelegate OnRemoveWidgetFromViewport;

    /**
     * Called when EOS refreshed the credentials for the local user in the background, and reports whether the user's
     * credential could be refreshed. If it couldn't be refreshed, it's likely the local user is about to be signed out
     * of the EOS backend.
     */
    FEOSCredentialRefreshComplete OnCredentialRefreshComplete;

    /**
     * Gets this subsystem from only a world reference. Returns nullptr if the subsystem is not available.
     */
    static UEOSSubsystem *GetSubsystem(UWorld *InWorld);
};