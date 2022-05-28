// Copyright June Rhodes. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "Modules/ModuleManager.h"

class REDPOINTEOSUTILS_API FRedpointEOSUtilsModule : public IModuleInterface
{
public:
    virtual void StartupModule() override;
};