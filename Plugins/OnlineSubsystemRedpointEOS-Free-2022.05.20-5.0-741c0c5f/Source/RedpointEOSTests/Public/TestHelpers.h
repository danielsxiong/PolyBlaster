// Copyright June Rhodes. All Rights Reserved.

#pragma once

#include "Engine/Engine.h"
#include "Engine/EngineBaseTypes.h"
#include "Misc/AutomationTest.h"
#include "OnlineSubsystem.h"
#include "OnlineSubsystemRedpointEOS/Shared/EOSConfig.h"
#include "OnlineSubsystemRedpointEOS/Shared/UniqueNetIdEOS.h"
#include "Templates/SharedPointer.h"
#include <functional>

DECLARE_LOG_CATEGORY_EXTERN(LogEOSTests, All, All);

typedef std::function<void(std::function<void()> OnDone)> FLambdaTest;

class FLambdaCommand : public IAutomationLatentCommand
{
public:
    FLambdaCommand() = delete;
    UE_NONCOPYABLE(FLambdaCommand);
    FLambdaCommand(class FAsyncHotReloadableAutomationTestBase *InTestBase, FLambdaTest InTestCode);
    virtual ~FLambdaCommand(){};
    virtual bool Update() override;

private:
    class FAsyncHotReloadableAutomationTestBase *TestBase;
    FLambdaTest TestCode;
    bool bIsStarted;
    bool bIsDone;
};

class FCleanupSubsystemsCommand : public IAutomationLatentCommand
{
public:
    FCleanupSubsystemsCommand() = delete;
    UE_NONCOPYABLE(FCleanupSubsystemsCommand);
    FCleanupSubsystemsCommand(class FAsyncHotReloadableAutomationTestBase *InTestBase);
    virtual ~FCleanupSubsystemsCommand(){};
    virtual bool Update() override;

private:
    FAsyncHotReloadableAutomationTestBase *TestBase;
};

class FHotReloadableAutomationTestBase : public FAutomationTestBase
{
public:
    FHotReloadableAutomationTestBase(const FString &InName, const bool bInComplexTask);
};

class REDPOINTEOSTESTS_API TestHelpers
{
public:
    static int16 WorkerNum;
    // Returns a port number offset by the worker num to avoid port collisions.
    static int Port(int BasePort);
};

typedef std::function<void()> FOnDone;

class FAsyncHotReloadableAutomationTestBase : public FHotReloadableAutomationTestBase
{
    friend class FLambdaCommand;

public:
    TArray<IOnlineSubsystemPtr> RegisteredSubsystems;
    TMap<FDelegateHandle, std::function<void()>> RegisteredDelegates;
    TMap<FDelegateHandle, bool> FireOnceFlags;
    TArray<TTuple<std::function<bool()>, std::function<void()>>> WaitingOnConditions;

    FAsyncHotReloadableAutomationTestBase(const FString &InName, const bool bInComplexTask)
        : FHotReloadableAutomationTestBase(InName, bInComplexTask){};
    void WhenCondition(std::function<bool()> Condition, std::function<void()> OnContinue);

protected:
    virtual void RunAsyncTest(const FOnDone &OnDone) = 0;
};

#define ADD_LATENT_AUTOMATION_COMMAND_PATCHED(ClassDeclaration)                                                        \
    FAutomationTestFramework::Get().SetRequestedTestFilter(EAutomationTestFlags::ProductFilter);                       \
    FAutomationTestFramework::Get().EnqueueLatentCommand(MakeShareable(new ClassDeclaration));

#define IMPLEMENT_ASYNC_AUTOMATION_TEST(TClass, PrettyName, TFlags)                                                    \
    IMPLEMENT_SIMPLE_AUTOMATION_TEST_PRIVATE(                                                                          \
        TClass##_Base,                                                                                                 \
        FAsyncHotReloadableAutomationTestBase,                                                                         \
        PrettyName,                                                                                                    \
        TFlags,                                                                                                        \
        __FILE__,                                                                                                      \
        __LINE__)                                                                                                      \
    bool TClass##_Base::RunTest(const FString &Parameters)                                                             \
    {                                                                                                                  \
        ADD_LATENT_AUTOMATION_COMMAND_PATCHED(FLambdaCommand(this, [this](const FOnDone &OnDone) {                     \
            this->RunAsyncTest(OnDone);                                                                                \
        }));                                                                                                           \
        ADD_LATENT_AUTOMATION_COMMAND_PATCHED(FCleanupSubsystemsCommand(this));                                        \
        return true;                                                                                                   \
    }                                                                                                                  \
    class TClass : TClass##_Base                                                                                       \
    {                                                                                                                  \
    public:                                                                                                            \
        TClass(const FString &InName)                                                                                  \
            : TClass##_Base(InName){};                                                                                 \
                                                                                                                       \
    protected:                                                                                                         \
        virtual void RunAsyncTest(const FOnDone &OnDone) override;                                                     \
    };                                                                                                                 \
    namespace                                                                                                          \
    {                                                                                                                  \
    TClass TClass##AutomationTestInstance(TEXT(#TClass));                                                              \
    }

#define IMPLEMENT_MANAGED_ASYNC_AUTOMATION_TEST(TClass, PrettyName, TFlags, TManagingClass)                            \
    IMPLEMENT_SIMPLE_AUTOMATION_TEST_PRIVATE(                                                                          \
        TClass##_Base,                                                                                                 \
        FAsyncHotReloadableAutomationTestBase,                                                                         \
        PrettyName,                                                                                                    \
        TFlags,                                                                                                        \
        __FILE__,                                                                                                      \
        __LINE__)                                                                                                      \
    bool TClass##_Base::RunTest(const FString &Parameters)                                                             \
    {                                                                                                                  \
        ADD_LATENT_AUTOMATION_COMMAND_PATCHED(FLambdaCommand(this, [this](const FOnDone &OnDone) {                     \
            this->RunAsyncTest(OnDone);                                                                                \
        }));                                                                                                           \
        ADD_LATENT_AUTOMATION_COMMAND_PATCHED(FCleanupSubsystemsCommand(this));                                        \
        return true;                                                                                                   \
    }                                                                                                                  \
    class TClass : TClass##_Base                                                                                       \
    {                                                                                                                  \
        friend class TManagingClass;                                                                                   \
                                                                                                                       \
    private:                                                                                                           \
        TSharedPtr<class TManagingClass> ManagingInstance;                                                             \
                                                                                                                       \
    public:                                                                                                            \
        TClass(const FString &InName)                                                                                  \
            : TClass##_Base(InName){};                                                                                 \
                                                                                                                       \
    protected:                                                                                                         \
        void CreateManagingInstance(                                                                                   \
            const FOnDone &OnDone,                                                                                     \
            const std::function<void(const TSharedRef<class TManagingClass> &)> &OnInstanceCreated);                   \
        virtual void RunAsyncTest(const FOnDone &OnDone) override                                                      \
        {                                                                                                              \
            FOnDone OnCleanup = [this, OnDone]() {                                                                     \
                this->ManagingInstance = nullptr;                                                                      \
                OnDone();                                                                                              \
            };                                                                                                         \
            this->CreateManagingInstance(OnCleanup, [this](const TSharedRef<class TManagingClass> &Inst) {             \
                this->ManagingInstance = Inst;                                                                         \
            });                                                                                                        \
        }                                                                                                              \
    };                                                                                                                 \
    namespace                                                                                                          \
    {                                                                                                                  \
    TClass TClass##AutomationTestInstance(TEXT(#TClass));                                                              \
    }

template <typename TService, typename TDelegate, typename... TArgs>
std::function<void()> RegisterOSSCallback(
    FAsyncHotReloadableAutomationTestBase *TestBase,
    TSharedPtr<TService, ESPMode::ThreadSafe> ServicePtr,
    int32 LocalUserNum,
    FDelegateHandle (TService::*AddFn)(int32 LocalUserNum, const TDelegate &Delegate),
    void (TService::*ClearFn)(int32 LocalUserNum, FDelegateHandle &Handle),
    std::function<void(int32 LocalUserNum, TArgs... Args)> Callback)
{
    TService *Service = ServicePtr.Get();
    TSharedPtr<FDelegateHandle> DelegateHandle = MakeShared<FDelegateHandle>();
    *DelegateHandle = (Service->*AddFn)(
        LocalUserNum,
        TDelegate::CreateLambda(
            [TestBase, LocalUserNum, Callback, DelegateHandle](int32 LocalUserNumCb, TArgs... Args) {
                if (LocalUserNum != LocalUserNumCb)
                {
                    return;
                }
                if (TestBase->FireOnceFlags.Contains(*DelegateHandle))
                {
                    if (TestBase->FireOnceFlags[*DelegateHandle])
                    {
                        return;
                    }
                    TestBase->FireOnceFlags.Add(*DelegateHandle, true);
                }
                Callback(LocalUserNumCb, Args...);
                TestBase->FireOnceFlags.Remove(*DelegateHandle);
                TestBase->RegisteredDelegates[*DelegateHandle]();
            }));
    FDelegateHandle DelegateHandleNonPtr = *DelegateHandle;
    TestBase->FireOnceFlags.Add(DelegateHandleNonPtr, false);
    TestBase->RegisteredDelegates.Add(
        DelegateHandleNonPtr,
        // NOLINTNEXTLINE(unreal-unsafe-storage-of-oss-pointer)
        [TestBase, LocalUserNum, DelegateHandleNonPtr, ClearFn, ServicePtr]() {
            FDelegateHandle DelegateHandleNonPtrCopy = DelegateHandleNonPtr;
            TService *ServiceLcl = ServicePtr.Get();
            (ServiceLcl->*ClearFn)(LocalUserNum, DelegateHandleNonPtrCopy);
            TestBase->RegisteredDelegates.Remove(DelegateHandleNonPtr);
        });
    return [TestBase, DelegateHandleNonPtr]() {
        TestBase->RegisteredDelegates[DelegateHandleNonPtr]();
    };
}

template <typename TService, typename TDelegate, typename... TArgs>
std::function<void()> RegisterOSSCallback(
    FAsyncHotReloadableAutomationTestBase *TestBase,
    TSharedPtr<TService, ESPMode::ThreadSafe> ServicePtr,
    FDelegateHandle (TService::*AddFn)(const TDelegate &Delegate),
    void (TService::*ClearFn)(FDelegateHandle &Handle),
    std::function<void(TArgs... Args)> Callback)
{
    TService *Service = ServicePtr.Get();
    TSharedPtr<FDelegateHandle> DelegateHandle = MakeShared<FDelegateHandle>();
    *DelegateHandle = (Service->*AddFn)(
        // NOLINTNEXTLINE(unreal-unsafe-storage-of-oss-pointer)
        TDelegate::CreateLambda([TestBase, ServicePtr, ClearFn, Callback, DelegateHandle](TArgs... Args) {
            if (TestBase->FireOnceFlags.Contains(*DelegateHandle))
            {
                if (TestBase->FireOnceFlags[*DelegateHandle])
                {
                    return;
                }
                TestBase->FireOnceFlags.Add(*DelegateHandle, true);
            }
            Callback(Args...);
            TestBase->FireOnceFlags.Remove(*DelegateHandle);
            TestBase->RegisteredDelegates[*DelegateHandle]();
        }));
    FDelegateHandle DelegateHandleNonPtr = *DelegateHandle;
    // NOLINTNEXTLINE(unreal-unsafe-storage-of-oss-pointer)
    TestBase->RegisteredDelegates.Add(DelegateHandleNonPtr, [TestBase, DelegateHandleNonPtr, ClearFn, ServicePtr]() {
        FDelegateHandle DelegateHandleNonPtrCopy = DelegateHandleNonPtr;
        TService *ServiceLcl = ServicePtr.Get();
        (ServiceLcl->*ClearFn)(DelegateHandleNonPtrCopy);
        TestBase->RegisteredDelegates.Remove(DelegateHandleNonPtr);
    });
    return [TestBase, DelegateHandleNonPtr]() {
        TestBase->RegisteredDelegates[DelegateHandleNonPtr]();
    };
}

struct FMultiplayerScenarioInstance
{
public:
    TWeakPtr<IOnlineSubsystem, ESPMode::ThreadSafe> Subsystem;
    TSharedPtr<const FUniqueNetIdEOS> UserId;
};

/**
 * Creates the desired number of EOS subsystems, using "create-on-demand" users. Create-on-demand users are
 * authenticated via a simple OpenID implementation in the License Manager; they're suitable for testing behaviour that
 * does not require Epic Games accounts, and allow tests to run in parallel.
 */
void CreateSubsystemsForTest_CreateOnDemand(
    FAsyncHotReloadableAutomationTestBase *Test,
    int SubsystemCount,
    const FOnDone &OnDoneFinal,
    const std::function<void(const TArray<FMultiplayerScenarioInstance> &Instances, const FOnDone &OnDone)> &Callback);

/**
 * Same as CreateSubsystemsForTest_CreateOnDemand, except it returns a single subsystem with multiple local users
 * (instead of a subsystem per local user). This is used for tests which need multiple local users in the same subsystem
 * (i.e. local multiplayer).
 */
void CreateUsersForTest_CreateOnDemand(
    FAsyncHotReloadableAutomationTestBase *Test,
    int UserCount,
    const FOnDone &OnDoneFinal,
    const std::function<void(
        const IOnlineSubsystemPtr &Subsystem,
        const TArray<TSharedPtr<const FUniqueNetIdEOS>> &UserIds,
        const FOnDone &OnDone)> &Callback);

/**
 * Deprecated helper that calls CreateSubsystemsForTest_CreateOnDemand with 1 subsystem.
 */
void CreateSingleSubsystemForTest_CreateOnDemand(
    FAsyncHotReloadableAutomationTestBase *Test,
    const FOnDone &OnDone,
    const std::function<void(
        const IOnlineSubsystemPtr &Subsystem,
        const TSharedPtr<const FUniqueNetIdEOS> &UserId,
        const FOnDone &OnDone)> &Callback);

struct FEpicGamesAutomatedTestingCredential
{
    FString Username;
    FString Password;
};

/**
 * Loads the Epic Games testing credentials, if they're available.
 */
REDPOINTEOSTESTS_API bool LoadEpicGamesAutomatedTestingCredentials(
    TArray<FEpicGamesAutomatedTestingCredential> &OutEpicGamesAutomatedTestingCredentials);

enum class EEpicGamesAccountCount
{
    One,
    Two,
};

/**
 * Creates the desired number of EOS subsystems, using Epic Games accounts. This is limited to a maximum of 2 Epic Games
 * accounts, and you must be careful not to write tests that can not handle the account being logged into two places at
 * once, or tests that rely on "set-and-get" functionality (since tests may be running concurrently). Avoid using Epic
 * Games accounts in automated testing where possible, and prefer CreateSubsystemsForTest_CreateOnDemand instead.
 */
void CreateSubsystemsForTest_EpicGames(
    FAsyncHotReloadableAutomationTestBase *Test,
    EEpicGamesAccountCount SubsystemCount,
    const FOnDone &OnDoneFinal,
    const std::function<void(const TArray<FMultiplayerScenarioInstance> &Instances, const FOnDone &OnDone)> &Callback);

class REDPOINTEOSTESTS_API FEOSConfigEASLogin : public FEOSConfig
{
protected:
    virtual FString GetDelegatedSubsystemsString() const override
    {
        return TEXT("");
    }

public:
    FEOSConfigEASLogin(){};
    UE_NONCOPYABLE(FEOSConfigEASLogin);
    virtual ~FEOSConfigEASLogin(){};

    virtual FString GetFreeEditionLicenseKey() const override
    {
        // Get this from the environment so that we're not embedding a valid license key
        // in the test binary (this will only be used on CI/CD anyway).
        return FPlatformMisc::GetEnvironmentVariable(TEXT("ONLINE_SUBSYSTEM_EOS_FREE_EDITION_LICENSE_KEY"));
    }
    virtual FString GetEncryptionKey() const override
    {
        return TEXT("4dc4ad8a46823586f4044225d6cf1b1e7ee32b3d7dff1c63b6ad5807671c4a3f");
    }
    virtual FString GetProductName() const override
    {
        return TEXT("Online Subsystem EOS Automated Tests");
    }
    virtual FString GetProductVersion() const override
    {
        return TEXT("0.0.0");
    }
    virtual FString GetProductId() const override
    {
        return TEXT("620b983080ae4bedbe11b2c49154b55d");
    }
    virtual FString GetSandboxId() const override
    {
        return TEXT("d03930678c1a43148620f9d891750763");
    }
    virtual FString GetDeploymentId() const override
    {
        return TEXT("c7055aea5c644e7d8f5898464b7a5305");
    }
    virtual FString GetClientId() const override
    {
        return TEXT("xyza7891af30Orhot3aht6Zb22EBIHsg");
    }
    virtual FString GetClientSecret() const override
    {
        return TEXT("3whfGHQUpg7P6Sy6hupm2DK2PqK1Sn2UFixzW6xbkiY");
    }
    virtual FString GetDedicatedServerClientId() const override
    {
        return TEXT("");
    }
    virtual FString GetDedicatedServerClientSecret() const override
    {
        return TEXT("");
    }
    virtual FString GetDeveloperToolAddress() const override
    {
        return TEXT("localhost:6300");
    }
    virtual FString GetDeveloperToolDefaultCredentialName() const override
    {
        return TEXT("AutomatedTests");
    }
    virtual FString GetWidgetClass(FString WidgetName, FString DefaultValue) const override
    {
        return DefaultValue;
    }
    virtual EEOSApiVersion GetApiVersion() const override
    {
        return (EEOSApiVersion)0;
    }
    virtual FName GetAuthenticationGraph() const override
    {
        return FName(TEXT("AutomatedTesting"));
    }
    virtual FName GetEditorAuthenticationGraph() const override
    {
        return FName(TEXT("AutomatedTesting"));
    }
    virtual FName GetCrossPlatformAccountProvider() const override
    {
        return FName(TEXT("EpicGames"));
    }
    virtual bool GetRequireCrossPlatformAccount() const override
    {
        return true;
    }
    virtual EPresenceAdvertisementType GetPresenceAdvertisementType() const override
    {
        return EPresenceAdvertisementType::None;
    }
    virtual bool GetPersistentLoginEnabled() const override
    {
        return false;
    }
    virtual bool IsAutomatedTesting() const override
    {
        return true;
    }
    virtual bool GetRequireEpicGamesLauncher() const override
    {
        return false;
    }
    virtual FString GetSimpleFirstPartyLoginUrl() const override
    {
        return TEXT("");
    }
    virtual EPartyJoinabilityConstraint GetPartyJoinabilityConstraint() const override
    {
        return EPartyJoinabilityConstraint::AllowPlayersInMultipleParties;
    }
    virtual FString GetDedicatedServerPublicKey() const override
    {
        return TEXT("");
    }
    virtual FString GetDedicatedServerPrivateKey() const override
    {
        return TEXT("");
    }
    virtual bool GetEnableSanctionChecks() const override
    {
        return false;
    }
    virtual bool GetEnableIdentityChecksOnListenServers() const override
    {
        return false;
    }
    virtual bool GetEnableTrustedDedicatedServers() const override
    {
        return false;
    }
    virtual bool GetEnableAutomaticEncryptionOnTrustedDedicatedServers() const override
    {
        return false;
    }
    virtual EDedicatedServersDistributionMode GetDedicatedServerDistributionMode() const override
    {
        return EDedicatedServersDistributionMode::PlayersOnly;
    }
    virtual bool GetEnableAntiCheat() const override
    {
        return false;
    }
    virtual FString GetTrustedClientPublicKey() const override
    {
        return TEXT("");
    }
    virtual FString GetTrustedClientPrivateKey() const override
    {
        return TEXT("");
    }
    virtual bool GetEnableVoiceChatEchoInParties() const override
    {
        return false;
    }
    virtual bool GetEnableVoiceChatPlatformAECByDefault() const override
    {
        return false;
    }
    virtual TArray<TTuple<FString, EStatTypingRule>> GetStatTypingRules() const override
    {
        // Rules for the stat tests.
        return TArray<TTuple<FString, EStatTypingRule>>{
            TTuple<FString, EStatTypingRule>(TEXT("TestFloatTrunc"), EStatTypingRule::FloatTruncated),
            TTuple<FString, EStatTypingRule>(TEXT("TestFloatEnc"), EStatTypingRule::FloatEncoded),
            TTuple<FString, EStatTypingRule>(TEXT("Te*Double*"), EStatTypingRule::DoubleEncoded)};
    }
    virtual bool GetAcceptStatWriteRequestsFromServers() const override
    {
        return true;
    }
};