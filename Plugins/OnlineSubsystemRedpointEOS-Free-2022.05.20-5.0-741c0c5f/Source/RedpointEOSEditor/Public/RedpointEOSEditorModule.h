// Copyright June Rhodes. All Rights Reserved.

#pragma once

#include "CoreGlobals.h"
#include "CoreMinimal.h"
#include "Input/Reply.h"
#include "Modules/ModuleManager.h"

DECLARE_LOG_CATEGORY_EXTERN(LogEOSEditor, All, All);

class FRedpointEOSEditorModule : public IModuleInterface
{
    virtual void StartupModule() override;
    virtual void ShutdownModule() override;

private:
    TSharedPtr<class FOnlineSubsystemEOSEditorConfig> SettingsInstance;

    void ViewDocumentation();
    void ViewWebsite();

#if defined(EOS_IS_FREE_EDITION)
    TSharedPtr<class SWindow> LicenseAgreementWindow;
    TSharedPtr<class SWindow> UpgradePromptWindow;
    bool LicenseAgreementLoaded;

    void ViewLicenseAgreementInBrowser();
    void ViewLicenseAgreementInEditor();
    FReply ViewLicenseTermsOnWebsite();
    FReply AcceptLicenseTerms();
    FReply RejectLicenseTerms();

    static bool HasAcceptedLicenseAgreement();

    void ShowUpgradePrompt();
    FReply FollowUpgradePrompt();
#else
    void AccessSupport();
#endif

    static TSharedRef<SWidget> GenerateOnlineSettingsMenu(TSharedRef<class FUICommandList> InCommandList);

    void RegisterMenus();

#if PLATFORM_WINDOWS || PLATFORM_MAC
    static void SetLoginsEnabled(bool bEnabled);
    static void ResyncLoginsIfEnabled();
#endif

    TSharedPtr<class FUICommandList> PluginCommands;
};