// Copyright June Rhodes. All Rights Reserved.

#pragma once

#include "Containers/Map.h"
#include "CoreMinimal.h"
#include "Modules/ModuleManager.h"
#include "OnlineSubsystem.h"

EOS_ENABLE_STRICT_WARNINGS

class ONLINESUBSYSTEMREDPOINTEOS_API FOnlineSubsystemRedpointEOSModule : public IModuleInterface, public IOnlineFactory
{
    friend class FOnlineSubsystemEOS;
    friend class FOnlineSubsystemRedpointEASFactory;
    friend class FCleanShutdown;

private:
    bool IsRegisteredAsSubsystem;
    TMap<FName, class FOnlineSubsystemEOS *> SubsystemInstances;
    TSharedPtr<class IEOSRuntimePlatform> RuntimePlatform;
    TSharedPtr<class FEOSConfig> EOSConfigInstance;
    TSharedRef<class FOnlineSubsystemRedpointEASFactory> EASSubsystemFactory;

public:
#if WITH_EDITOR
    TSharedPtr<class FEOSConfig> AutomationTestingConfigOverride;
#endif

    FOnlineSubsystemRedpointEOSModule();
    UE_NONCOPYABLE(FOnlineSubsystemRedpointEOSModule);

    /** IModuleInterface implementation */
    virtual void StartupModule() override;
    virtual void ShutdownModule() override;

    virtual void SetRuntimePlatform(const TSharedRef<class IEOSRuntimePlatform> &InRuntimePlatform);

#if !UE_BUILD_SHIPPING
    virtual FString GetPathToEASAutomatedTestingCredentials();
#endif

    bool IsFreeEdition();
    bool HasInstance(FName InstanceName);

    virtual IOnlineSubsystemPtr CreateSubsystem(FName InstanceName) override;
    IOnlineSubsystemPtr CreateSubsystem(FName InstanceName, const TSharedRef<class FEOSConfig> &ConfigOverride);
};

EOS_DISABLE_STRICT_WARNINGS