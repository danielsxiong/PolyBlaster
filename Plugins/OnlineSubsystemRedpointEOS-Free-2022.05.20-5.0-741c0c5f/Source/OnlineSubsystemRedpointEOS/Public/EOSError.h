// Copyright June Rhodes. All Rights Reserved.

#pragma once

#include "OnlineError.h"
#if defined(UE_5_0_OR_LATER)
#include "Online/CoreOnline.h"
#else
#include "UObject/CoreOnline.h"
#endif

namespace OnlineRedpointEOS
{
namespace Errors
{
const FOnlineError &Success();
const FOnlineError &UnexpectedError();
const FOnlineError UnexpectedError(const TCHAR *InCall, const FString &InContextMsg);
const FOnlineError UnexpectedError(const TCHAR *InCall, const TCHAR *InContextMsg);
const FOnlineError UnexpectedError(const FUniqueNetId &InActorId, const TCHAR *InCall, const FString &InContextMsg);
const FOnlineError UnexpectedError(const FUniqueNetId &InActorId);
const FOnlineError UnexpectedError(
    const FUniqueNetId &InActorId,
    const FString &InObjectId,
    const TCHAR *InCall,
    const FString &InContextMsg);
const FOnlineError &NoConnection();
const FOnlineError NoConnection(const TCHAR *InCall, const FString &InContextMsg);
const FOnlineError NoConnection(const TCHAR *InCall, const TCHAR *InContextMsg);
const FOnlineError NoConnection(const FUniqueNetId &InActorId, const TCHAR *InCall, const FString &InContextMsg);
const FOnlineError NoConnection(const FUniqueNetId &InActorId);
const FOnlineError NoConnection(
    const FUniqueNetId &InActorId,
    const FString &InObjectId,
    const TCHAR *InCall,
    const FString &InContextMsg);
const FOnlineError &InvalidParameters();
const FOnlineError InvalidParameters(const TCHAR *InCall, const FString &InContextMsg);
const FOnlineError InvalidParameters(const TCHAR *InCall, const TCHAR *InContextMsg);
const FOnlineError InvalidParameters(const FUniqueNetId &InActorId, const TCHAR *InCall, const FString &InContextMsg);
const FOnlineError InvalidParameters(const FUniqueNetId &InActorId);
const FOnlineError InvalidParameters(
    const FUniqueNetId &InActorId,
    const FString &InObjectId,
    const TCHAR *InCall,
    const FString &InContextMsg);
const FOnlineError &InvalidRequest();
const FOnlineError InvalidRequest(const TCHAR *InCall, const FString &InContextMsg);
const FOnlineError InvalidRequest(const TCHAR *InCall, const TCHAR *InContextMsg);
const FOnlineError InvalidRequest(const FUniqueNetId &InActorId, const TCHAR *InCall, const FString &InContextMsg);
const FOnlineError InvalidRequest(const FUniqueNetId &InActorId);
const FOnlineError InvalidRequest(
    const FUniqueNetId &InActorId,
    const FString &InObjectId,
    const TCHAR *InCall,
    const FString &InContextMsg);
const FOnlineError &UnrecognizedResponse();
const FOnlineError UnrecognizedResponse(const TCHAR *InCall, const FString &InContextMsg);
const FOnlineError UnrecognizedResponse(const TCHAR *InCall, const TCHAR *InContextMsg);
const FOnlineError UnrecognizedResponse(
    const FUniqueNetId &InActorId,
    const TCHAR *InCall,
    const FString &InContextMsg);
const FOnlineError UnrecognizedResponse(const FUniqueNetId &InActorId);
const FOnlineError UnrecognizedResponse(
    const FUniqueNetId &InActorId,
    const FString &InObjectId,
    const TCHAR *InCall,
    const FString &InContextMsg);
const FOnlineError &IncompatibleVersion();
const FOnlineError IncompatibleVersion(const TCHAR *InCall, const FString &InContextMsg);
const FOnlineError IncompatibleVersion(const TCHAR *InCall, const TCHAR *InContextMsg);
const FOnlineError IncompatibleVersion(const FUniqueNetId &InActorId, const TCHAR *InCall, const FString &InContextMsg);
const FOnlineError IncompatibleVersion(const FUniqueNetId &InActorId);
const FOnlineError IncompatibleVersion(
    const FUniqueNetId &InActorId,
    const FString &InObjectId,
    const TCHAR *InCall,
    const FString &InContextMsg);
const FOnlineError &NotConfigured();
const FOnlineError NotConfigured(const TCHAR *InCall, const FString &InContextMsg);
const FOnlineError NotConfigured(const TCHAR *InCall, const TCHAR *InContextMsg);
const FOnlineError NotConfigured(const FUniqueNetId &InActorId, const TCHAR *InCall, const FString &InContextMsg);
const FOnlineError NotConfigured(const FUniqueNetId &InActorId);
const FOnlineError NotConfigured(
    const FUniqueNetId &InActorId,
    const FString &InObjectId,
    const TCHAR *InCall,
    const FString &InContextMsg);
const FOnlineError &AlreadyConfigured();
const FOnlineError AlreadyConfigured(const TCHAR *InCall, const FString &InContextMsg);
const FOnlineError AlreadyConfigured(const TCHAR *InCall, const TCHAR *InContextMsg);
const FOnlineError AlreadyConfigured(const FUniqueNetId &InActorId, const TCHAR *InCall, const FString &InContextMsg);
const FOnlineError AlreadyConfigured(const FUniqueNetId &InActorId);
const FOnlineError AlreadyConfigured(
    const FUniqueNetId &InActorId,
    const FString &InObjectId,
    const TCHAR *InCall,
    const FString &InContextMsg);
const FOnlineError &NotImplemented();
const FOnlineError NotImplemented(const TCHAR *InCall, const FString &InContextMsg);
const FOnlineError NotImplemented(const TCHAR *InCall, const TCHAR *InContextMsg);
const FOnlineError NotImplemented(const FUniqueNetId &InActorId, const TCHAR *InCall, const FString &InContextMsg);
const FOnlineError NotImplemented(const FUniqueNetId &InActorId);
const FOnlineError NotImplemented(
    const FUniqueNetId &InActorId,
    const FString &InObjectId,
    const TCHAR *InCall,
    const FString &InContextMsg);
const FOnlineError &Canceled();
const FOnlineError Canceled(const TCHAR *InCall, const FString &InContextMsg);
const FOnlineError Canceled(const TCHAR *InCall, const TCHAR *InContextMsg);
const FOnlineError Canceled(const FUniqueNetId &InActorId, const TCHAR *InCall, const FString &InContextMsg);
const FOnlineError Canceled(const FUniqueNetId &InActorId);
const FOnlineError Canceled(
    const FUniqueNetId &InActorId,
    const FString &InObjectId,
    const TCHAR *InCall,
    const FString &InContextMsg);
const FOnlineError &NotFound();
const FOnlineError NotFound(const TCHAR *InCall, const FString &InContextMsg);
const FOnlineError NotFound(const TCHAR *InCall, const TCHAR *InContextMsg);
const FOnlineError NotFound(const FUniqueNetId &InActorId, const TCHAR *InCall, const FString &InContextMsg);
const FOnlineError NotFound(const FUniqueNetId &InActorId);
const FOnlineError NotFound(
    const FUniqueNetId &InActorId,
    const FString &InObjectId,
    const TCHAR *InCall,
    const FString &InContextMsg);
const FOnlineError &OperationWillRetry();
const FOnlineError OperationWillRetry(const TCHAR *InCall, const FString &InContextMsg);
const FOnlineError OperationWillRetry(const TCHAR *InCall, const TCHAR *InContextMsg);
const FOnlineError OperationWillRetry(const FUniqueNetId &InActorId, const TCHAR *InCall, const FString &InContextMsg);
const FOnlineError OperationWillRetry(const FUniqueNetId &InActorId);
const FOnlineError OperationWillRetry(
    const FUniqueNetId &InActorId,
    const FString &InObjectId,
    const TCHAR *InCall,
    const FString &InContextMsg);
const FOnlineError &InvalidCredentials();
const FOnlineError InvalidCredentials(const TCHAR *InCall, const FString &InContextMsg);
const FOnlineError InvalidCredentials(const TCHAR *InCall, const TCHAR *InContextMsg);
const FOnlineError InvalidCredentials(const FUniqueNetId &InActorId, const TCHAR *InCall, const FString &InContextMsg);
const FOnlineError InvalidCredentials(const FUniqueNetId &InActorId);
const FOnlineError InvalidCredentials(
    const FUniqueNetId &InActorId,
    const FString &InObjectId,
    const TCHAR *InCall,
    const FString &InContextMsg);
const FOnlineError &NoChange();
const FOnlineError NoChange(const TCHAR *InCall, const FString &InContextMsg);
const FOnlineError NoChange(const TCHAR *InCall, const TCHAR *InContextMsg);
const FOnlineError NoChange(const FUniqueNetId &InActorId, const TCHAR *InCall, const FString &InContextMsg);
const FOnlineError NoChange(const FUniqueNetId &InActorId);
const FOnlineError NoChange(
    const FUniqueNetId &InActorId,
    const FString &InObjectId,
    const TCHAR *InCall,
    const FString &InContextMsg);
const FOnlineError &VersionMismatch();
const FOnlineError VersionMismatch(const TCHAR *InCall, const FString &InContextMsg);
const FOnlineError VersionMismatch(const TCHAR *InCall, const TCHAR *InContextMsg);
const FOnlineError VersionMismatch(const FUniqueNetId &InActorId, const TCHAR *InCall, const FString &InContextMsg);
const FOnlineError VersionMismatch(const FUniqueNetId &InActorId);
const FOnlineError VersionMismatch(
    const FUniqueNetId &InActorId,
    const FString &InObjectId,
    const TCHAR *InCall,
    const FString &InContextMsg);
const FOnlineError &LimitExceeded();
const FOnlineError LimitExceeded(const TCHAR *InCall, const FString &InContextMsg);
const FOnlineError LimitExceeded(const TCHAR *InCall, const TCHAR *InContextMsg);
const FOnlineError LimitExceeded(const FUniqueNetId &InActorId, const TCHAR *InCall, const FString &InContextMsg);
const FOnlineError LimitExceeded(const FUniqueNetId &InActorId);
const FOnlineError LimitExceeded(
    const FUniqueNetId &InActorId,
    const FString &InObjectId,
    const TCHAR *InCall,
    const FString &InContextMsg);
const FOnlineError &Disabled();
const FOnlineError Disabled(const TCHAR *InCall, const FString &InContextMsg);
const FOnlineError Disabled(const TCHAR *InCall, const TCHAR *InContextMsg);
const FOnlineError Disabled(const FUniqueNetId &InActorId, const TCHAR *InCall, const FString &InContextMsg);
const FOnlineError Disabled(const FUniqueNetId &InActorId);
const FOnlineError Disabled(
    const FUniqueNetId &InActorId,
    const FString &InObjectId,
    const TCHAR *InCall,
    const FString &InContextMsg);
const FOnlineError &DuplicateNotAllowed();
const FOnlineError DuplicateNotAllowed(const TCHAR *InCall, const FString &InContextMsg);
const FOnlineError DuplicateNotAllowed(const TCHAR *InCall, const TCHAR *InContextMsg);
const FOnlineError DuplicateNotAllowed(const FUniqueNetId &InActorId, const TCHAR *InCall, const FString &InContextMsg);
const FOnlineError DuplicateNotAllowed(const FUniqueNetId &InActorId);
const FOnlineError DuplicateNotAllowed(
    const FUniqueNetId &InActorId,
    const FString &InObjectId,
    const TCHAR *InCall,
    const FString &InContextMsg);
const FOnlineError &MissingParameters();
const FOnlineError MissingParameters(const TCHAR *InCall, const FString &InContextMsg);
const FOnlineError MissingParameters(const TCHAR *InCall, const TCHAR *InContextMsg);
const FOnlineError MissingParameters(const FUniqueNetId &InActorId, const TCHAR *InCall, const FString &InContextMsg);
const FOnlineError MissingParameters(const FUniqueNetId &InActorId);
const FOnlineError MissingParameters(
    const FUniqueNetId &InActorId,
    const FString &InObjectId,
    const TCHAR *InCall,
    const FString &InContextMsg);
const FOnlineError &InvalidSandboxId();
const FOnlineError InvalidSandboxId(const TCHAR *InCall, const FString &InContextMsg);
const FOnlineError InvalidSandboxId(const TCHAR *InCall, const TCHAR *InContextMsg);
const FOnlineError InvalidSandboxId(const FUniqueNetId &InActorId, const TCHAR *InCall, const FString &InContextMsg);
const FOnlineError InvalidSandboxId(const FUniqueNetId &InActorId);
const FOnlineError InvalidSandboxId(
    const FUniqueNetId &InActorId,
    const FString &InObjectId,
    const TCHAR *InCall,
    const FString &InContextMsg);
const FOnlineError &TimedOut();
const FOnlineError TimedOut(const TCHAR *InCall, const FString &InContextMsg);
const FOnlineError TimedOut(const TCHAR *InCall, const TCHAR *InContextMsg);
const FOnlineError TimedOut(const FUniqueNetId &InActorId, const TCHAR *InCall, const FString &InContextMsg);
const FOnlineError TimedOut(const FUniqueNetId &InActorId);
const FOnlineError TimedOut(
    const FUniqueNetId &InActorId,
    const FString &InObjectId,
    const TCHAR *InCall,
    const FString &InContextMsg);
const FOnlineError &PartialResult();
const FOnlineError PartialResult(const TCHAR *InCall, const FString &InContextMsg);
const FOnlineError PartialResult(const TCHAR *InCall, const TCHAR *InContextMsg);
const FOnlineError PartialResult(const FUniqueNetId &InActorId, const TCHAR *InCall, const FString &InContextMsg);
const FOnlineError PartialResult(const FUniqueNetId &InActorId);
const FOnlineError PartialResult(
    const FUniqueNetId &InActorId,
    const FString &InObjectId,
    const TCHAR *InCall,
    const FString &InContextMsg);
const FOnlineError &Missing_Role();
const FOnlineError Missing_Role(const TCHAR *InCall, const FString &InContextMsg);
const FOnlineError Missing_Role(const TCHAR *InCall, const TCHAR *InContextMsg);
const FOnlineError Missing_Role(const FUniqueNetId &InActorId, const TCHAR *InCall, const FString &InContextMsg);
const FOnlineError Missing_Role(const FUniqueNetId &InActorId);
const FOnlineError Missing_Role(
    const FUniqueNetId &InActorId,
    const FString &InObjectId,
    const TCHAR *InCall,
    const FString &InContextMsg);
const FOnlineError &InvalidUser();
const FOnlineError InvalidUser(const TCHAR *InCall, const FString &InContextMsg);
const FOnlineError InvalidUser(const TCHAR *InCall, const TCHAR *InContextMsg);
const FOnlineError InvalidUser(const FUniqueNetId &InActorId, const TCHAR *InCall, const FString &InContextMsg);
const FOnlineError InvalidUser(const FUniqueNetId &InActorId);
const FOnlineError InvalidUser(
    const FUniqueNetId &InActorId,
    const FString &InObjectId,
    const TCHAR *InCall,
    const FString &InContextMsg);
const FOnlineError &Missing_Feature();
const FOnlineError Missing_Feature(const TCHAR *InCall, const FString &InContextMsg);
const FOnlineError Missing_Feature(const TCHAR *InCall, const TCHAR *InContextMsg);
const FOnlineError Missing_Feature(const FUniqueNetId &InActorId, const TCHAR *InCall, const FString &InContextMsg);
const FOnlineError Missing_Feature(const FUniqueNetId &InActorId);
const FOnlineError Missing_Feature(
    const FUniqueNetId &InActorId,
    const FString &InObjectId,
    const TCHAR *InCall,
    const FString &InContextMsg);
const FOnlineError &Invalid_Sandbox();
const FOnlineError Invalid_Sandbox(const TCHAR *InCall, const FString &InContextMsg);
const FOnlineError Invalid_Sandbox(const TCHAR *InCall, const TCHAR *InContextMsg);
const FOnlineError Invalid_Sandbox(const FUniqueNetId &InActorId, const TCHAR *InCall, const FString &InContextMsg);
const FOnlineError Invalid_Sandbox(const FUniqueNetId &InActorId);
const FOnlineError Invalid_Sandbox(
    const FUniqueNetId &InActorId,
    const FString &InObjectId,
    const TCHAR *InCall,
    const FString &InContextMsg);
const FOnlineError &Invalid_Deployment();
const FOnlineError Invalid_Deployment(const TCHAR *InCall, const FString &InContextMsg);
const FOnlineError Invalid_Deployment(const TCHAR *InCall, const TCHAR *InContextMsg);
const FOnlineError Invalid_Deployment(const FUniqueNetId &InActorId, const TCHAR *InCall, const FString &InContextMsg);
const FOnlineError Invalid_Deployment(const FUniqueNetId &InActorId);
const FOnlineError Invalid_Deployment(
    const FUniqueNetId &InActorId,
    const FString &InObjectId,
    const TCHAR *InCall,
    const FString &InContextMsg);
const FOnlineError &Invalid_Product();
const FOnlineError Invalid_Product(const TCHAR *InCall, const FString &InContextMsg);
const FOnlineError Invalid_Product(const TCHAR *InCall, const TCHAR *InContextMsg);
const FOnlineError Invalid_Product(const FUniqueNetId &InActorId, const TCHAR *InCall, const FString &InContextMsg);
const FOnlineError Invalid_Product(const FUniqueNetId &InActorId);
const FOnlineError Invalid_Product(
    const FUniqueNetId &InActorId,
    const FString &InObjectId,
    const TCHAR *InCall,
    const FString &InContextMsg);
const FOnlineError &Invalid_ProductUserID();
const FOnlineError Invalid_ProductUserID(const TCHAR *InCall, const FString &InContextMsg);
const FOnlineError Invalid_ProductUserID(const TCHAR *InCall, const TCHAR *InContextMsg);
const FOnlineError Invalid_ProductUserID(
    const FUniqueNetId &InActorId,
    const TCHAR *InCall,
    const FString &InContextMsg);
const FOnlineError Invalid_ProductUserID(const FUniqueNetId &InActorId);
const FOnlineError Invalid_ProductUserID(
    const FUniqueNetId &InActorId,
    const FString &InObjectId,
    const TCHAR *InCall,
    const FString &InContextMsg);
const FOnlineError &ServiceFailure();
const FOnlineError ServiceFailure(const TCHAR *InCall, const FString &InContextMsg);
const FOnlineError ServiceFailure(const TCHAR *InCall, const TCHAR *InContextMsg);
const FOnlineError ServiceFailure(const FUniqueNetId &InActorId, const TCHAR *InCall, const FString &InContextMsg);
const FOnlineError ServiceFailure(const FUniqueNetId &InActorId);
const FOnlineError ServiceFailure(
    const FUniqueNetId &InActorId,
    const FString &InObjectId,
    const TCHAR *InCall,
    const FString &InContextMsg);
const FOnlineError &CacheDirectoryMissing();
const FOnlineError CacheDirectoryMissing(const TCHAR *InCall, const FString &InContextMsg);
const FOnlineError CacheDirectoryMissing(const TCHAR *InCall, const TCHAR *InContextMsg);
const FOnlineError CacheDirectoryMissing(
    const FUniqueNetId &InActorId,
    const TCHAR *InCall,
    const FString &InContextMsg);
const FOnlineError CacheDirectoryMissing(const FUniqueNetId &InActorId);
const FOnlineError CacheDirectoryMissing(
    const FUniqueNetId &InActorId,
    const FString &InObjectId,
    const TCHAR *InCall,
    const FString &InContextMsg);
const FOnlineError &CacheDirectoryInvalid();
const FOnlineError CacheDirectoryInvalid(const TCHAR *InCall, const FString &InContextMsg);
const FOnlineError CacheDirectoryInvalid(const TCHAR *InCall, const TCHAR *InContextMsg);
const FOnlineError CacheDirectoryInvalid(
    const FUniqueNetId &InActorId,
    const TCHAR *InCall,
    const FString &InContextMsg);
const FOnlineError CacheDirectoryInvalid(const FUniqueNetId &InActorId);
const FOnlineError CacheDirectoryInvalid(
    const FUniqueNetId &InActorId,
    const FString &InObjectId,
    const TCHAR *InCall,
    const FString &InContextMsg);
const FOnlineError &InvalidState();
const FOnlineError InvalidState(const TCHAR *InCall, const FString &InContextMsg);
const FOnlineError InvalidState(const TCHAR *InCall, const TCHAR *InContextMsg);
const FOnlineError InvalidState(const FUniqueNetId &InActorId, const TCHAR *InCall, const FString &InContextMsg);
const FOnlineError InvalidState(const FUniqueNetId &InActorId);
const FOnlineError InvalidState(
    const FUniqueNetId &InActorId,
    const FString &InObjectId,
    const TCHAR *InCall,
    const FString &InContextMsg);
const FOnlineError &RequestInProgress();
const FOnlineError RequestInProgress(const TCHAR *InCall, const FString &InContextMsg);
const FOnlineError RequestInProgress(const TCHAR *InCall, const TCHAR *InContextMsg);
const FOnlineError RequestInProgress(const FUniqueNetId &InActorId, const TCHAR *InCall, const FString &InContextMsg);
const FOnlineError RequestInProgress(const FUniqueNetId &InActorId);
const FOnlineError RequestInProgress(
    const FUniqueNetId &InActorId,
    const FString &InObjectId,
    const TCHAR *InCall,
    const FString &InContextMsg);
const FOnlineError &InvalidAuth();
const FOnlineError InvalidAuth(const TCHAR *InCall, const FString &InContextMsg);
const FOnlineError InvalidAuth(const TCHAR *InCall, const TCHAR *InContextMsg);
const FOnlineError InvalidAuth(const FUniqueNetId &InActorId, const TCHAR *InCall, const FString &InContextMsg);
const FOnlineError InvalidAuth(const FUniqueNetId &InActorId);
const FOnlineError InvalidAuth(
    const FUniqueNetId &InActorId,
    const FString &InObjectId,
    const TCHAR *InCall,
    const FString &InContextMsg);
const FOnlineError &AccessDenied();
const FOnlineError AccessDenied(const TCHAR *InCall, const FString &InContextMsg);
const FOnlineError AccessDenied(const TCHAR *InCall, const TCHAR *InContextMsg);
const FOnlineError AccessDenied(const FUniqueNetId &InActorId, const TCHAR *InCall, const FString &InContextMsg);
const FOnlineError AccessDenied(const FUniqueNetId &InActorId);
const FOnlineError AccessDenied(
    const FUniqueNetId &InActorId,
    const FString &InObjectId,
    const TCHAR *InCall,
    const FString &InContextMsg);
const FOnlineError &MissingPermissions();
const FOnlineError MissingPermissions(const TCHAR *InCall, const FString &InContextMsg);
const FOnlineError MissingPermissions(const TCHAR *InCall, const TCHAR *InContextMsg);
const FOnlineError MissingPermissions(const FUniqueNetId &InActorId, const TCHAR *InCall, const FString &InContextMsg);
const FOnlineError MissingPermissions(const FUniqueNetId &InActorId);
const FOnlineError MissingPermissions(
    const FUniqueNetId &InActorId,
    const FString &InObjectId,
    const TCHAR *InCall,
    const FString &InContextMsg);
const FOnlineError &Token_Not_Account();
const FOnlineError Token_Not_Account(const TCHAR *InCall, const FString &InContextMsg);
const FOnlineError Token_Not_Account(const TCHAR *InCall, const TCHAR *InContextMsg);
const FOnlineError Token_Not_Account(const FUniqueNetId &InActorId, const TCHAR *InCall, const FString &InContextMsg);
const FOnlineError Token_Not_Account(const FUniqueNetId &InActorId);
const FOnlineError Token_Not_Account(
    const FUniqueNetId &InActorId,
    const FString &InObjectId,
    const TCHAR *InCall,
    const FString &InContextMsg);
const FOnlineError &TooManyRequests();
const FOnlineError TooManyRequests(const TCHAR *InCall, const FString &InContextMsg);
const FOnlineError TooManyRequests(const TCHAR *InCall, const TCHAR *InContextMsg);
const FOnlineError TooManyRequests(const FUniqueNetId &InActorId, const TCHAR *InCall, const FString &InContextMsg);
const FOnlineError TooManyRequests(const FUniqueNetId &InActorId);
const FOnlineError TooManyRequests(
    const FUniqueNetId &InActorId,
    const FString &InObjectId,
    const TCHAR *InCall,
    const FString &InContextMsg);
const FOnlineError &AlreadyPending();
const FOnlineError AlreadyPending(const TCHAR *InCall, const FString &InContextMsg);
const FOnlineError AlreadyPending(const TCHAR *InCall, const TCHAR *InContextMsg);
const FOnlineError AlreadyPending(const FUniqueNetId &InActorId, const TCHAR *InCall, const FString &InContextMsg);
const FOnlineError AlreadyPending(const FUniqueNetId &InActorId);
const FOnlineError AlreadyPending(
    const FUniqueNetId &InActorId,
    const FString &InObjectId,
    const TCHAR *InCall,
    const FString &InContextMsg);
namespace Auth
{
const FOnlineError &AccountLocked();
const FOnlineError AccountLocked(const TCHAR *InCall, const FString &InContextMsg);
const FOnlineError AccountLocked(const TCHAR *InCall, const TCHAR *InContextMsg);
const FOnlineError AccountLocked(const FUniqueNetId &InActorId, const TCHAR *InCall, const FString &InContextMsg);
const FOnlineError AccountLocked(const FUniqueNetId &InActorId);
const FOnlineError AccountLocked(
    const FUniqueNetId &InActorId,
    const FString &InObjectId,
    const TCHAR *InCall,
    const FString &InContextMsg);
const FOnlineError &AccountLockedForUpdate();
const FOnlineError AccountLockedForUpdate(const TCHAR *InCall, const FString &InContextMsg);
const FOnlineError AccountLockedForUpdate(const TCHAR *InCall, const TCHAR *InContextMsg);
const FOnlineError AccountLockedForUpdate(
    const FUniqueNetId &InActorId,
    const TCHAR *InCall,
    const FString &InContextMsg);
const FOnlineError AccountLockedForUpdate(const FUniqueNetId &InActorId);
const FOnlineError AccountLockedForUpdate(
    const FUniqueNetId &InActorId,
    const FString &InObjectId,
    const TCHAR *InCall,
    const FString &InContextMsg);
const FOnlineError &InvalidRefreshToken();
const FOnlineError InvalidRefreshToken(const TCHAR *InCall, const FString &InContextMsg);
const FOnlineError InvalidRefreshToken(const TCHAR *InCall, const TCHAR *InContextMsg);
const FOnlineError InvalidRefreshToken(const FUniqueNetId &InActorId, const TCHAR *InCall, const FString &InContextMsg);
const FOnlineError InvalidRefreshToken(const FUniqueNetId &InActorId);
const FOnlineError InvalidRefreshToken(
    const FUniqueNetId &InActorId,
    const FString &InObjectId,
    const TCHAR *InCall,
    const FString &InContextMsg);
const FOnlineError &InvalidToken();
const FOnlineError InvalidToken(const TCHAR *InCall, const FString &InContextMsg);
const FOnlineError InvalidToken(const TCHAR *InCall, const TCHAR *InContextMsg);
const FOnlineError InvalidToken(const FUniqueNetId &InActorId, const TCHAR *InCall, const FString &InContextMsg);
const FOnlineError InvalidToken(const FUniqueNetId &InActorId);
const FOnlineError InvalidToken(
    const FUniqueNetId &InActorId,
    const FString &InObjectId,
    const TCHAR *InCall,
    const FString &InContextMsg);
const FOnlineError &AuthenticationFailure();
const FOnlineError AuthenticationFailure(const TCHAR *InCall, const FString &InContextMsg);
const FOnlineError AuthenticationFailure(const TCHAR *InCall, const TCHAR *InContextMsg);
const FOnlineError AuthenticationFailure(
    const FUniqueNetId &InActorId,
    const TCHAR *InCall,
    const FString &InContextMsg);
const FOnlineError AuthenticationFailure(const FUniqueNetId &InActorId);
const FOnlineError AuthenticationFailure(
    const FUniqueNetId &InActorId,
    const FString &InObjectId,
    const TCHAR *InCall,
    const FString &InContextMsg);
const FOnlineError &InvalidPlatformToken();
const FOnlineError InvalidPlatformToken(const TCHAR *InCall, const FString &InContextMsg);
const FOnlineError InvalidPlatformToken(const TCHAR *InCall, const TCHAR *InContextMsg);
const FOnlineError InvalidPlatformToken(
    const FUniqueNetId &InActorId,
    const TCHAR *InCall,
    const FString &InContextMsg);
const FOnlineError InvalidPlatformToken(const FUniqueNetId &InActorId);
const FOnlineError InvalidPlatformToken(
    const FUniqueNetId &InActorId,
    const FString &InObjectId,
    const TCHAR *InCall,
    const FString &InContextMsg);
const FOnlineError &WrongAccount();
const FOnlineError WrongAccount(const TCHAR *InCall, const FString &InContextMsg);
const FOnlineError WrongAccount(const TCHAR *InCall, const TCHAR *InContextMsg);
const FOnlineError WrongAccount(const FUniqueNetId &InActorId, const TCHAR *InCall, const FString &InContextMsg);
const FOnlineError WrongAccount(const FUniqueNetId &InActorId);
const FOnlineError WrongAccount(
    const FUniqueNetId &InActorId,
    const FString &InObjectId,
    const TCHAR *InCall,
    const FString &InContextMsg);
const FOnlineError &WrongClient();
const FOnlineError WrongClient(const TCHAR *InCall, const FString &InContextMsg);
const FOnlineError WrongClient(const TCHAR *InCall, const TCHAR *InContextMsg);
const FOnlineError WrongClient(const FUniqueNetId &InActorId, const TCHAR *InCall, const FString &InContextMsg);
const FOnlineError WrongClient(const FUniqueNetId &InActorId);
const FOnlineError WrongClient(
    const FUniqueNetId &InActorId,
    const FString &InObjectId,
    const TCHAR *InCall,
    const FString &InContextMsg);
const FOnlineError &FullAccountRequired();
const FOnlineError FullAccountRequired(const TCHAR *InCall, const FString &InContextMsg);
const FOnlineError FullAccountRequired(const TCHAR *InCall, const TCHAR *InContextMsg);
const FOnlineError FullAccountRequired(const FUniqueNetId &InActorId, const TCHAR *InCall, const FString &InContextMsg);
const FOnlineError FullAccountRequired(const FUniqueNetId &InActorId);
const FOnlineError FullAccountRequired(
    const FUniqueNetId &InActorId,
    const FString &InObjectId,
    const TCHAR *InCall,
    const FString &InContextMsg);
const FOnlineError &HeadlessAccountRequired();
const FOnlineError HeadlessAccountRequired(const TCHAR *InCall, const FString &InContextMsg);
const FOnlineError HeadlessAccountRequired(const TCHAR *InCall, const TCHAR *InContextMsg);
const FOnlineError HeadlessAccountRequired(
    const FUniqueNetId &InActorId,
    const TCHAR *InCall,
    const FString &InContextMsg);
const FOnlineError HeadlessAccountRequired(const FUniqueNetId &InActorId);
const FOnlineError HeadlessAccountRequired(
    const FUniqueNetId &InActorId,
    const FString &InObjectId,
    const TCHAR *InCall,
    const FString &InContextMsg);
const FOnlineError &PasswordResetRequired();
const FOnlineError PasswordResetRequired(const TCHAR *InCall, const FString &InContextMsg);
const FOnlineError PasswordResetRequired(const TCHAR *InCall, const TCHAR *InContextMsg);
const FOnlineError PasswordResetRequired(
    const FUniqueNetId &InActorId,
    const TCHAR *InCall,
    const FString &InContextMsg);
const FOnlineError PasswordResetRequired(const FUniqueNetId &InActorId);
const FOnlineError PasswordResetRequired(
    const FUniqueNetId &InActorId,
    const FString &InObjectId,
    const TCHAR *InCall,
    const FString &InContextMsg);
const FOnlineError &PasswordCannotBeReused();
const FOnlineError PasswordCannotBeReused(const TCHAR *InCall, const FString &InContextMsg);
const FOnlineError PasswordCannotBeReused(const TCHAR *InCall, const TCHAR *InContextMsg);
const FOnlineError PasswordCannotBeReused(
    const FUniqueNetId &InActorId,
    const TCHAR *InCall,
    const FString &InContextMsg);
const FOnlineError PasswordCannotBeReused(const FUniqueNetId &InActorId);
const FOnlineError PasswordCannotBeReused(
    const FUniqueNetId &InActorId,
    const FString &InObjectId,
    const TCHAR *InCall,
    const FString &InContextMsg);
const FOnlineError &Expired();
const FOnlineError Expired(const TCHAR *InCall, const FString &InContextMsg);
const FOnlineError Expired(const TCHAR *InCall, const TCHAR *InContextMsg);
const FOnlineError Expired(const FUniqueNetId &InActorId, const TCHAR *InCall, const FString &InContextMsg);
const FOnlineError Expired(const FUniqueNetId &InActorId);
const FOnlineError Expired(
    const FUniqueNetId &InActorId,
    const FString &InObjectId,
    const TCHAR *InCall,
    const FString &InContextMsg);
const FOnlineError &ScopeConsentRequired();
const FOnlineError ScopeConsentRequired(const TCHAR *InCall, const FString &InContextMsg);
const FOnlineError ScopeConsentRequired(const TCHAR *InCall, const TCHAR *InContextMsg);
const FOnlineError ScopeConsentRequired(
    const FUniqueNetId &InActorId,
    const TCHAR *InCall,
    const FString &InContextMsg);
const FOnlineError ScopeConsentRequired(const FUniqueNetId &InActorId);
const FOnlineError ScopeConsentRequired(
    const FUniqueNetId &InActorId,
    const FString &InObjectId,
    const TCHAR *InCall,
    const FString &InContextMsg);
const FOnlineError &ApplicationNotFound();
const FOnlineError ApplicationNotFound(const TCHAR *InCall, const FString &InContextMsg);
const FOnlineError ApplicationNotFound(const TCHAR *InCall, const TCHAR *InContextMsg);
const FOnlineError ApplicationNotFound(const FUniqueNetId &InActorId, const TCHAR *InCall, const FString &InContextMsg);
const FOnlineError ApplicationNotFound(const FUniqueNetId &InActorId);
const FOnlineError ApplicationNotFound(
    const FUniqueNetId &InActorId,
    const FString &InObjectId,
    const TCHAR *InCall,
    const FString &InContextMsg);
const FOnlineError &ScopeNotFound();
const FOnlineError ScopeNotFound(const TCHAR *InCall, const FString &InContextMsg);
const FOnlineError ScopeNotFound(const TCHAR *InCall, const TCHAR *InContextMsg);
const FOnlineError ScopeNotFound(const FUniqueNetId &InActorId, const TCHAR *InCall, const FString &InContextMsg);
const FOnlineError ScopeNotFound(const FUniqueNetId &InActorId);
const FOnlineError ScopeNotFound(
    const FUniqueNetId &InActorId,
    const FString &InObjectId,
    const TCHAR *InCall,
    const FString &InContextMsg);
const FOnlineError &AccountFeatureRestricted();
const FOnlineError AccountFeatureRestricted(const TCHAR *InCall, const FString &InContextMsg);
const FOnlineError AccountFeatureRestricted(const TCHAR *InCall, const TCHAR *InContextMsg);
const FOnlineError AccountFeatureRestricted(
    const FUniqueNetId &InActorId,
    const TCHAR *InCall,
    const FString &InContextMsg);
const FOnlineError AccountFeatureRestricted(const FUniqueNetId &InActorId);
const FOnlineError AccountFeatureRestricted(
    const FUniqueNetId &InActorId,
    const FString &InObjectId,
    const TCHAR *InCall,
    const FString &InContextMsg);
const FOnlineError &PinGrantCode();
const FOnlineError PinGrantCode(const TCHAR *InCall, const FString &InContextMsg);
const FOnlineError PinGrantCode(const TCHAR *InCall, const TCHAR *InContextMsg);
const FOnlineError PinGrantCode(const FUniqueNetId &InActorId, const TCHAR *InCall, const FString &InContextMsg);
const FOnlineError PinGrantCode(const FUniqueNetId &InActorId);
const FOnlineError PinGrantCode(
    const FUniqueNetId &InActorId,
    const FString &InObjectId,
    const TCHAR *InCall,
    const FString &InContextMsg);
const FOnlineError &PinGrantExpired();
const FOnlineError PinGrantExpired(const TCHAR *InCall, const FString &InContextMsg);
const FOnlineError PinGrantExpired(const TCHAR *InCall, const TCHAR *InContextMsg);
const FOnlineError PinGrantExpired(const FUniqueNetId &InActorId, const TCHAR *InCall, const FString &InContextMsg);
const FOnlineError PinGrantExpired(const FUniqueNetId &InActorId);
const FOnlineError PinGrantExpired(
    const FUniqueNetId &InActorId,
    const FString &InObjectId,
    const TCHAR *InCall,
    const FString &InContextMsg);
const FOnlineError &PinGrantPending();
const FOnlineError PinGrantPending(const TCHAR *InCall, const FString &InContextMsg);
const FOnlineError PinGrantPending(const TCHAR *InCall, const TCHAR *InContextMsg);
const FOnlineError PinGrantPending(const FUniqueNetId &InActorId, const TCHAR *InCall, const FString &InContextMsg);
const FOnlineError PinGrantPending(const FUniqueNetId &InActorId);
const FOnlineError PinGrantPending(
    const FUniqueNetId &InActorId,
    const FString &InObjectId,
    const TCHAR *InCall,
    const FString &InContextMsg);
const FOnlineError &ExternalAuthNotLinked();
const FOnlineError ExternalAuthNotLinked(const TCHAR *InCall, const FString &InContextMsg);
const FOnlineError ExternalAuthNotLinked(const TCHAR *InCall, const TCHAR *InContextMsg);
const FOnlineError ExternalAuthNotLinked(
    const FUniqueNetId &InActorId,
    const TCHAR *InCall,
    const FString &InContextMsg);
const FOnlineError ExternalAuthNotLinked(const FUniqueNetId &InActorId);
const FOnlineError ExternalAuthNotLinked(
    const FUniqueNetId &InActorId,
    const FString &InObjectId,
    const TCHAR *InCall,
    const FString &InContextMsg);
const FOnlineError &ExternalAuthRevoked();
const FOnlineError ExternalAuthRevoked(const TCHAR *InCall, const FString &InContextMsg);
const FOnlineError ExternalAuthRevoked(const TCHAR *InCall, const TCHAR *InContextMsg);
const FOnlineError ExternalAuthRevoked(const FUniqueNetId &InActorId, const TCHAR *InCall, const FString &InContextMsg);
const FOnlineError ExternalAuthRevoked(const FUniqueNetId &InActorId);
const FOnlineError ExternalAuthRevoked(
    const FUniqueNetId &InActorId,
    const FString &InObjectId,
    const TCHAR *InCall,
    const FString &InContextMsg);
const FOnlineError &ExternalAuthInvalid();
const FOnlineError ExternalAuthInvalid(const TCHAR *InCall, const FString &InContextMsg);
const FOnlineError ExternalAuthInvalid(const TCHAR *InCall, const TCHAR *InContextMsg);
const FOnlineError ExternalAuthInvalid(const FUniqueNetId &InActorId, const TCHAR *InCall, const FString &InContextMsg);
const FOnlineError ExternalAuthInvalid(const FUniqueNetId &InActorId);
const FOnlineError ExternalAuthInvalid(
    const FUniqueNetId &InActorId,
    const FString &InObjectId,
    const TCHAR *InCall,
    const FString &InContextMsg);
const FOnlineError &ExternalAuthRestricted();
const FOnlineError ExternalAuthRestricted(const TCHAR *InCall, const FString &InContextMsg);
const FOnlineError ExternalAuthRestricted(const TCHAR *InCall, const TCHAR *InContextMsg);
const FOnlineError ExternalAuthRestricted(
    const FUniqueNetId &InActorId,
    const TCHAR *InCall,
    const FString &InContextMsg);
const FOnlineError ExternalAuthRestricted(const FUniqueNetId &InActorId);
const FOnlineError ExternalAuthRestricted(
    const FUniqueNetId &InActorId,
    const FString &InObjectId,
    const TCHAR *InCall,
    const FString &InContextMsg);
const FOnlineError &ExternalAuthCannotLogin();
const FOnlineError ExternalAuthCannotLogin(const TCHAR *InCall, const FString &InContextMsg);
const FOnlineError ExternalAuthCannotLogin(const TCHAR *InCall, const TCHAR *InContextMsg);
const FOnlineError ExternalAuthCannotLogin(
    const FUniqueNetId &InActorId,
    const TCHAR *InCall,
    const FString &InContextMsg);
const FOnlineError ExternalAuthCannotLogin(const FUniqueNetId &InActorId);
const FOnlineError ExternalAuthCannotLogin(
    const FUniqueNetId &InActorId,
    const FString &InObjectId,
    const TCHAR *InCall,
    const FString &InContextMsg);
const FOnlineError &ExternalAuthExpired();
const FOnlineError ExternalAuthExpired(const TCHAR *InCall, const FString &InContextMsg);
const FOnlineError ExternalAuthExpired(const TCHAR *InCall, const TCHAR *InContextMsg);
const FOnlineError ExternalAuthExpired(const FUniqueNetId &InActorId, const TCHAR *InCall, const FString &InContextMsg);
const FOnlineError ExternalAuthExpired(const FUniqueNetId &InActorId);
const FOnlineError ExternalAuthExpired(
    const FUniqueNetId &InActorId,
    const FString &InObjectId,
    const TCHAR *InCall,
    const FString &InContextMsg);
const FOnlineError &ExternalAuthIsLastLoginType();
const FOnlineError ExternalAuthIsLastLoginType(const TCHAR *InCall, const FString &InContextMsg);
const FOnlineError ExternalAuthIsLastLoginType(const TCHAR *InCall, const TCHAR *InContextMsg);
const FOnlineError ExternalAuthIsLastLoginType(
    const FUniqueNetId &InActorId,
    const TCHAR *InCall,
    const FString &InContextMsg);
const FOnlineError ExternalAuthIsLastLoginType(const FUniqueNetId &InActorId);
const FOnlineError ExternalAuthIsLastLoginType(
    const FUniqueNetId &InActorId,
    const FString &InObjectId,
    const TCHAR *InCall,
    const FString &InContextMsg);
const FOnlineError &ExchangeCodeNotFound();
const FOnlineError ExchangeCodeNotFound(const TCHAR *InCall, const FString &InContextMsg);
const FOnlineError ExchangeCodeNotFound(const TCHAR *InCall, const TCHAR *InContextMsg);
const FOnlineError ExchangeCodeNotFound(
    const FUniqueNetId &InActorId,
    const TCHAR *InCall,
    const FString &InContextMsg);
const FOnlineError ExchangeCodeNotFound(const FUniqueNetId &InActorId);
const FOnlineError ExchangeCodeNotFound(
    const FUniqueNetId &InActorId,
    const FString &InObjectId,
    const TCHAR *InCall,
    const FString &InContextMsg);
const FOnlineError &OriginatingExchangeCodeSessionExpired();
const FOnlineError OriginatingExchangeCodeSessionExpired(const TCHAR *InCall, const FString &InContextMsg);
const FOnlineError OriginatingExchangeCodeSessionExpired(const TCHAR *InCall, const TCHAR *InContextMsg);
const FOnlineError OriginatingExchangeCodeSessionExpired(
    const FUniqueNetId &InActorId,
    const TCHAR *InCall,
    const FString &InContextMsg);
const FOnlineError OriginatingExchangeCodeSessionExpired(const FUniqueNetId &InActorId);
const FOnlineError OriginatingExchangeCodeSessionExpired(
    const FUniqueNetId &InActorId,
    const FString &InObjectId,
    const TCHAR *InCall,
    const FString &InContextMsg);
const FOnlineError &PersistentAuth_AccountNotActive();
const FOnlineError PersistentAuth_AccountNotActive(const TCHAR *InCall, const FString &InContextMsg);
const FOnlineError PersistentAuth_AccountNotActive(const TCHAR *InCall, const TCHAR *InContextMsg);
const FOnlineError PersistentAuth_AccountNotActive(
    const FUniqueNetId &InActorId,
    const TCHAR *InCall,
    const FString &InContextMsg);
const FOnlineError PersistentAuth_AccountNotActive(const FUniqueNetId &InActorId);
const FOnlineError PersistentAuth_AccountNotActive(
    const FUniqueNetId &InActorId,
    const FString &InObjectId,
    const TCHAR *InCall,
    const FString &InContextMsg);
const FOnlineError &MFARequired();
const FOnlineError MFARequired(const TCHAR *InCall, const FString &InContextMsg);
const FOnlineError MFARequired(const TCHAR *InCall, const TCHAR *InContextMsg);
const FOnlineError MFARequired(const FUniqueNetId &InActorId, const TCHAR *InCall, const FString &InContextMsg);
const FOnlineError MFARequired(const FUniqueNetId &InActorId);
const FOnlineError MFARequired(
    const FUniqueNetId &InActorId,
    const FString &InObjectId,
    const TCHAR *InCall,
    const FString &InContextMsg);
const FOnlineError &ParentalControls();
const FOnlineError ParentalControls(const TCHAR *InCall, const FString &InContextMsg);
const FOnlineError ParentalControls(const TCHAR *InCall, const TCHAR *InContextMsg);
const FOnlineError ParentalControls(const FUniqueNetId &InActorId, const TCHAR *InCall, const FString &InContextMsg);
const FOnlineError ParentalControls(const FUniqueNetId &InActorId);
const FOnlineError ParentalControls(
    const FUniqueNetId &InActorId,
    const FString &InObjectId,
    const TCHAR *InCall,
    const FString &InContextMsg);
const FOnlineError &NoRealId();
const FOnlineError NoRealId(const TCHAR *InCall, const FString &InContextMsg);
const FOnlineError NoRealId(const TCHAR *InCall, const TCHAR *InContextMsg);
const FOnlineError NoRealId(const FUniqueNetId &InActorId, const TCHAR *InCall, const FString &InContextMsg);
const FOnlineError NoRealId(const FUniqueNetId &InActorId);
const FOnlineError NoRealId(
    const FUniqueNetId &InActorId,
    const FString &InObjectId,
    const TCHAR *InCall,
    const FString &InContextMsg);
} // namespace Auth
namespace Friends
{
const FOnlineError &InviteAwaitingAcceptance();
const FOnlineError InviteAwaitingAcceptance(const TCHAR *InCall, const FString &InContextMsg);
const FOnlineError InviteAwaitingAcceptance(const TCHAR *InCall, const TCHAR *InContextMsg);
const FOnlineError InviteAwaitingAcceptance(
    const FUniqueNetId &InActorId,
    const TCHAR *InCall,
    const FString &InContextMsg);
const FOnlineError InviteAwaitingAcceptance(const FUniqueNetId &InActorId);
const FOnlineError InviteAwaitingAcceptance(
    const FUniqueNetId &InActorId,
    const FString &InObjectId,
    const TCHAR *InCall,
    const FString &InContextMsg);
const FOnlineError &NoInvitation();
const FOnlineError NoInvitation(const TCHAR *InCall, const FString &InContextMsg);
const FOnlineError NoInvitation(const TCHAR *InCall, const TCHAR *InContextMsg);
const FOnlineError NoInvitation(const FUniqueNetId &InActorId, const TCHAR *InCall, const FString &InContextMsg);
const FOnlineError NoInvitation(const FUniqueNetId &InActorId);
const FOnlineError NoInvitation(
    const FUniqueNetId &InActorId,
    const FString &InObjectId,
    const TCHAR *InCall,
    const FString &InContextMsg);
const FOnlineError &AlreadyFriends();
const FOnlineError AlreadyFriends(const TCHAR *InCall, const FString &InContextMsg);
const FOnlineError AlreadyFriends(const TCHAR *InCall, const TCHAR *InContextMsg);
const FOnlineError AlreadyFriends(const FUniqueNetId &InActorId, const TCHAR *InCall, const FString &InContextMsg);
const FOnlineError AlreadyFriends(const FUniqueNetId &InActorId);
const FOnlineError AlreadyFriends(
    const FUniqueNetId &InActorId,
    const FString &InObjectId,
    const TCHAR *InCall,
    const FString &InContextMsg);
const FOnlineError &NotFriends();
const FOnlineError NotFriends(const TCHAR *InCall, const FString &InContextMsg);
const FOnlineError NotFriends(const TCHAR *InCall, const TCHAR *InContextMsg);
const FOnlineError NotFriends(const FUniqueNetId &InActorId, const TCHAR *InCall, const FString &InContextMsg);
const FOnlineError NotFriends(const FUniqueNetId &InActorId);
const FOnlineError NotFriends(
    const FUniqueNetId &InActorId,
    const FString &InObjectId,
    const TCHAR *InCall,
    const FString &InContextMsg);
const FOnlineError &TargetUserTooManyInvites();
const FOnlineError TargetUserTooManyInvites(const TCHAR *InCall, const FString &InContextMsg);
const FOnlineError TargetUserTooManyInvites(const TCHAR *InCall, const TCHAR *InContextMsg);
const FOnlineError TargetUserTooManyInvites(
    const FUniqueNetId &InActorId,
    const TCHAR *InCall,
    const FString &InContextMsg);
const FOnlineError TargetUserTooManyInvites(const FUniqueNetId &InActorId);
const FOnlineError TargetUserTooManyInvites(
    const FUniqueNetId &InActorId,
    const FString &InObjectId,
    const TCHAR *InCall,
    const FString &InContextMsg);
const FOnlineError &LocalUserTooManyInvites();
const FOnlineError LocalUserTooManyInvites(const TCHAR *InCall, const FString &InContextMsg);
const FOnlineError LocalUserTooManyInvites(const TCHAR *InCall, const TCHAR *InContextMsg);
const FOnlineError LocalUserTooManyInvites(
    const FUniqueNetId &InActorId,
    const TCHAR *InCall,
    const FString &InContextMsg);
const FOnlineError LocalUserTooManyInvites(const FUniqueNetId &InActorId);
const FOnlineError LocalUserTooManyInvites(
    const FUniqueNetId &InActorId,
    const FString &InObjectId,
    const TCHAR *InCall,
    const FString &InContextMsg);
const FOnlineError &TargetUserFriendLimitExceeded();
const FOnlineError TargetUserFriendLimitExceeded(const TCHAR *InCall, const FString &InContextMsg);
const FOnlineError TargetUserFriendLimitExceeded(const TCHAR *InCall, const TCHAR *InContextMsg);
const FOnlineError TargetUserFriendLimitExceeded(
    const FUniqueNetId &InActorId,
    const TCHAR *InCall,
    const FString &InContextMsg);
const FOnlineError TargetUserFriendLimitExceeded(const FUniqueNetId &InActorId);
const FOnlineError TargetUserFriendLimitExceeded(
    const FUniqueNetId &InActorId,
    const FString &InObjectId,
    const TCHAR *InCall,
    const FString &InContextMsg);
const FOnlineError &LocalUserFriendLimitExceeded();
const FOnlineError LocalUserFriendLimitExceeded(const TCHAR *InCall, const FString &InContextMsg);
const FOnlineError LocalUserFriendLimitExceeded(const TCHAR *InCall, const TCHAR *InContextMsg);
const FOnlineError LocalUserFriendLimitExceeded(
    const FUniqueNetId &InActorId,
    const TCHAR *InCall,
    const FString &InContextMsg);
const FOnlineError LocalUserFriendLimitExceeded(const FUniqueNetId &InActorId);
const FOnlineError LocalUserFriendLimitExceeded(
    const FUniqueNetId &InActorId,
    const FString &InObjectId,
    const TCHAR *InCall,
    const FString &InContextMsg);
} // namespace Friends
namespace Presence
{
const FOnlineError &DataInvalid();
const FOnlineError DataInvalid(const TCHAR *InCall, const FString &InContextMsg);
const FOnlineError DataInvalid(const TCHAR *InCall, const TCHAR *InContextMsg);
const FOnlineError DataInvalid(const FUniqueNetId &InActorId, const TCHAR *InCall, const FString &InContextMsg);
const FOnlineError DataInvalid(const FUniqueNetId &InActorId);
const FOnlineError DataInvalid(
    const FUniqueNetId &InActorId,
    const FString &InObjectId,
    const TCHAR *InCall,
    const FString &InContextMsg);
const FOnlineError &DataLengthInvalid();
const FOnlineError DataLengthInvalid(const TCHAR *InCall, const FString &InContextMsg);
const FOnlineError DataLengthInvalid(const TCHAR *InCall, const TCHAR *InContextMsg);
const FOnlineError DataLengthInvalid(const FUniqueNetId &InActorId, const TCHAR *InCall, const FString &InContextMsg);
const FOnlineError DataLengthInvalid(const FUniqueNetId &InActorId);
const FOnlineError DataLengthInvalid(
    const FUniqueNetId &InActorId,
    const FString &InObjectId,
    const TCHAR *InCall,
    const FString &InContextMsg);
const FOnlineError &DataKeyInvalid();
const FOnlineError DataKeyInvalid(const TCHAR *InCall, const FString &InContextMsg);
const FOnlineError DataKeyInvalid(const TCHAR *InCall, const TCHAR *InContextMsg);
const FOnlineError DataKeyInvalid(const FUniqueNetId &InActorId, const TCHAR *InCall, const FString &InContextMsg);
const FOnlineError DataKeyInvalid(const FUniqueNetId &InActorId);
const FOnlineError DataKeyInvalid(
    const FUniqueNetId &InActorId,
    const FString &InObjectId,
    const TCHAR *InCall,
    const FString &InContextMsg);
const FOnlineError &DataKeyLengthInvalid();
const FOnlineError DataKeyLengthInvalid(const TCHAR *InCall, const FString &InContextMsg);
const FOnlineError DataKeyLengthInvalid(const TCHAR *InCall, const TCHAR *InContextMsg);
const FOnlineError DataKeyLengthInvalid(
    const FUniqueNetId &InActorId,
    const TCHAR *InCall,
    const FString &InContextMsg);
const FOnlineError DataKeyLengthInvalid(const FUniqueNetId &InActorId);
const FOnlineError DataKeyLengthInvalid(
    const FUniqueNetId &InActorId,
    const FString &InObjectId,
    const TCHAR *InCall,
    const FString &InContextMsg);
const FOnlineError &DataValueInvalid();
const FOnlineError DataValueInvalid(const TCHAR *InCall, const FString &InContextMsg);
const FOnlineError DataValueInvalid(const TCHAR *InCall, const TCHAR *InContextMsg);
const FOnlineError DataValueInvalid(const FUniqueNetId &InActorId, const TCHAR *InCall, const FString &InContextMsg);
const FOnlineError DataValueInvalid(const FUniqueNetId &InActorId);
const FOnlineError DataValueInvalid(
    const FUniqueNetId &InActorId,
    const FString &InObjectId,
    const TCHAR *InCall,
    const FString &InContextMsg);
const FOnlineError &DataValueLengthInvalid();
const FOnlineError DataValueLengthInvalid(const TCHAR *InCall, const FString &InContextMsg);
const FOnlineError DataValueLengthInvalid(const TCHAR *InCall, const TCHAR *InContextMsg);
const FOnlineError DataValueLengthInvalid(
    const FUniqueNetId &InActorId,
    const TCHAR *InCall,
    const FString &InContextMsg);
const FOnlineError DataValueLengthInvalid(const FUniqueNetId &InActorId);
const FOnlineError DataValueLengthInvalid(
    const FUniqueNetId &InActorId,
    const FString &InObjectId,
    const TCHAR *InCall,
    const FString &InContextMsg);
const FOnlineError &RichTextInvalid();
const FOnlineError RichTextInvalid(const TCHAR *InCall, const FString &InContextMsg);
const FOnlineError RichTextInvalid(const TCHAR *InCall, const TCHAR *InContextMsg);
const FOnlineError RichTextInvalid(const FUniqueNetId &InActorId, const TCHAR *InCall, const FString &InContextMsg);
const FOnlineError RichTextInvalid(const FUniqueNetId &InActorId);
const FOnlineError RichTextInvalid(
    const FUniqueNetId &InActorId,
    const FString &InObjectId,
    const TCHAR *InCall,
    const FString &InContextMsg);
const FOnlineError &RichTextLengthInvalid();
const FOnlineError RichTextLengthInvalid(const TCHAR *InCall, const FString &InContextMsg);
const FOnlineError RichTextLengthInvalid(const TCHAR *InCall, const TCHAR *InContextMsg);
const FOnlineError RichTextLengthInvalid(
    const FUniqueNetId &InActorId,
    const TCHAR *InCall,
    const FString &InContextMsg);
const FOnlineError RichTextLengthInvalid(const FUniqueNetId &InActorId);
const FOnlineError RichTextLengthInvalid(
    const FUniqueNetId &InActorId,
    const FString &InObjectId,
    const TCHAR *InCall,
    const FString &InContextMsg);
const FOnlineError &StatusInvalid();
const FOnlineError StatusInvalid(const TCHAR *InCall, const FString &InContextMsg);
const FOnlineError StatusInvalid(const TCHAR *InCall, const TCHAR *InContextMsg);
const FOnlineError StatusInvalid(const FUniqueNetId &InActorId, const TCHAR *InCall, const FString &InContextMsg);
const FOnlineError StatusInvalid(const FUniqueNetId &InActorId);
const FOnlineError StatusInvalid(
    const FUniqueNetId &InActorId,
    const FString &InObjectId,
    const TCHAR *InCall,
    const FString &InContextMsg);
} // namespace Presence
namespace Ecom
{
const FOnlineError &EntitlementStale();
const FOnlineError EntitlementStale(const TCHAR *InCall, const FString &InContextMsg);
const FOnlineError EntitlementStale(const TCHAR *InCall, const TCHAR *InContextMsg);
const FOnlineError EntitlementStale(const FUniqueNetId &InActorId, const TCHAR *InCall, const FString &InContextMsg);
const FOnlineError EntitlementStale(const FUniqueNetId &InActorId);
const FOnlineError EntitlementStale(
    const FUniqueNetId &InActorId,
    const FString &InObjectId,
    const TCHAR *InCall,
    const FString &InContextMsg);
const FOnlineError &CatalogOfferStale();
const FOnlineError CatalogOfferStale(const TCHAR *InCall, const FString &InContextMsg);
const FOnlineError CatalogOfferStale(const TCHAR *InCall, const TCHAR *InContextMsg);
const FOnlineError CatalogOfferStale(const FUniqueNetId &InActorId, const TCHAR *InCall, const FString &InContextMsg);
const FOnlineError CatalogOfferStale(const FUniqueNetId &InActorId);
const FOnlineError CatalogOfferStale(
    const FUniqueNetId &InActorId,
    const FString &InObjectId,
    const TCHAR *InCall,
    const FString &InContextMsg);
const FOnlineError &CatalogItemStale();
const FOnlineError CatalogItemStale(const TCHAR *InCall, const FString &InContextMsg);
const FOnlineError CatalogItemStale(const TCHAR *InCall, const TCHAR *InContextMsg);
const FOnlineError CatalogItemStale(const FUniqueNetId &InActorId, const TCHAR *InCall, const FString &InContextMsg);
const FOnlineError CatalogItemStale(const FUniqueNetId &InActorId);
const FOnlineError CatalogItemStale(
    const FUniqueNetId &InActorId,
    const FString &InObjectId,
    const TCHAR *InCall,
    const FString &InContextMsg);
const FOnlineError &CatalogOfferPriceInvalid();
const FOnlineError CatalogOfferPriceInvalid(const TCHAR *InCall, const FString &InContextMsg);
const FOnlineError CatalogOfferPriceInvalid(const TCHAR *InCall, const TCHAR *InContextMsg);
const FOnlineError CatalogOfferPriceInvalid(
    const FUniqueNetId &InActorId,
    const TCHAR *InCall,
    const FString &InContextMsg);
const FOnlineError CatalogOfferPriceInvalid(const FUniqueNetId &InActorId);
const FOnlineError CatalogOfferPriceInvalid(
    const FUniqueNetId &InActorId,
    const FString &InObjectId,
    const TCHAR *InCall,
    const FString &InContextMsg);
const FOnlineError &CheckoutLoadError();
const FOnlineError CheckoutLoadError(const TCHAR *InCall, const FString &InContextMsg);
const FOnlineError CheckoutLoadError(const TCHAR *InCall, const TCHAR *InContextMsg);
const FOnlineError CheckoutLoadError(const FUniqueNetId &InActorId, const TCHAR *InCall, const FString &InContextMsg);
const FOnlineError CheckoutLoadError(const FUniqueNetId &InActorId);
const FOnlineError CheckoutLoadError(
    const FUniqueNetId &InActorId,
    const FString &InObjectId,
    const TCHAR *InCall,
    const FString &InContextMsg);
} // namespace Ecom
namespace Sessions
{
const FOnlineError &SessionInProgress();
const FOnlineError SessionInProgress(const TCHAR *InCall, const FString &InContextMsg);
const FOnlineError SessionInProgress(const TCHAR *InCall, const TCHAR *InContextMsg);
const FOnlineError SessionInProgress(const FUniqueNetId &InActorId, const TCHAR *InCall, const FString &InContextMsg);
const FOnlineError SessionInProgress(const FUniqueNetId &InActorId);
const FOnlineError SessionInProgress(
    const FUniqueNetId &InActorId,
    const FString &InObjectId,
    const TCHAR *InCall,
    const FString &InContextMsg);
const FOnlineError &TooManyPlayers();
const FOnlineError TooManyPlayers(const TCHAR *InCall, const FString &InContextMsg);
const FOnlineError TooManyPlayers(const TCHAR *InCall, const TCHAR *InContextMsg);
const FOnlineError TooManyPlayers(const FUniqueNetId &InActorId, const TCHAR *InCall, const FString &InContextMsg);
const FOnlineError TooManyPlayers(const FUniqueNetId &InActorId);
const FOnlineError TooManyPlayers(
    const FUniqueNetId &InActorId,
    const FString &InObjectId,
    const TCHAR *InCall,
    const FString &InContextMsg);
const FOnlineError &NoPermission();
const FOnlineError NoPermission(const TCHAR *InCall, const FString &InContextMsg);
const FOnlineError NoPermission(const TCHAR *InCall, const TCHAR *InContextMsg);
const FOnlineError NoPermission(const FUniqueNetId &InActorId, const TCHAR *InCall, const FString &InContextMsg);
const FOnlineError NoPermission(const FUniqueNetId &InActorId);
const FOnlineError NoPermission(
    const FUniqueNetId &InActorId,
    const FString &InObjectId,
    const TCHAR *InCall,
    const FString &InContextMsg);
const FOnlineError &SessionAlreadyExists();
const FOnlineError SessionAlreadyExists(const TCHAR *InCall, const FString &InContextMsg);
const FOnlineError SessionAlreadyExists(const TCHAR *InCall, const TCHAR *InContextMsg);
const FOnlineError SessionAlreadyExists(
    const FUniqueNetId &InActorId,
    const TCHAR *InCall,
    const FString &InContextMsg);
const FOnlineError SessionAlreadyExists(const FUniqueNetId &InActorId);
const FOnlineError SessionAlreadyExists(
    const FUniqueNetId &InActorId,
    const FString &InObjectId,
    const TCHAR *InCall,
    const FString &InContextMsg);
const FOnlineError &InvalidLock();
const FOnlineError InvalidLock(const TCHAR *InCall, const FString &InContextMsg);
const FOnlineError InvalidLock(const TCHAR *InCall, const TCHAR *InContextMsg);
const FOnlineError InvalidLock(const FUniqueNetId &InActorId, const TCHAR *InCall, const FString &InContextMsg);
const FOnlineError InvalidLock(const FUniqueNetId &InActorId);
const FOnlineError InvalidLock(
    const FUniqueNetId &InActorId,
    const FString &InObjectId,
    const TCHAR *InCall,
    const FString &InContextMsg);
const FOnlineError &InvalidSession();
const FOnlineError InvalidSession(const TCHAR *InCall, const FString &InContextMsg);
const FOnlineError InvalidSession(const TCHAR *InCall, const TCHAR *InContextMsg);
const FOnlineError InvalidSession(const FUniqueNetId &InActorId, const TCHAR *InCall, const FString &InContextMsg);
const FOnlineError InvalidSession(const FUniqueNetId &InActorId);
const FOnlineError InvalidSession(
    const FUniqueNetId &InActorId,
    const FString &InObjectId,
    const TCHAR *InCall,
    const FString &InContextMsg);
const FOnlineError &SandboxNotAllowed();
const FOnlineError SandboxNotAllowed(const TCHAR *InCall, const FString &InContextMsg);
const FOnlineError SandboxNotAllowed(const TCHAR *InCall, const TCHAR *InContextMsg);
const FOnlineError SandboxNotAllowed(const FUniqueNetId &InActorId, const TCHAR *InCall, const FString &InContextMsg);
const FOnlineError SandboxNotAllowed(const FUniqueNetId &InActorId);
const FOnlineError SandboxNotAllowed(
    const FUniqueNetId &InActorId,
    const FString &InObjectId,
    const TCHAR *InCall,
    const FString &InContextMsg);
const FOnlineError &InviteFailed();
const FOnlineError InviteFailed(const TCHAR *InCall, const FString &InContextMsg);
const FOnlineError InviteFailed(const TCHAR *InCall, const TCHAR *InContextMsg);
const FOnlineError InviteFailed(const FUniqueNetId &InActorId, const TCHAR *InCall, const FString &InContextMsg);
const FOnlineError InviteFailed(const FUniqueNetId &InActorId);
const FOnlineError InviteFailed(
    const FUniqueNetId &InActorId,
    const FString &InObjectId,
    const TCHAR *InCall,
    const FString &InContextMsg);
const FOnlineError &InviteNotFound();
const FOnlineError InviteNotFound(const TCHAR *InCall, const FString &InContextMsg);
const FOnlineError InviteNotFound(const TCHAR *InCall, const TCHAR *InContextMsg);
const FOnlineError InviteNotFound(const FUniqueNetId &InActorId, const TCHAR *InCall, const FString &InContextMsg);
const FOnlineError InviteNotFound(const FUniqueNetId &InActorId);
const FOnlineError InviteNotFound(
    const FUniqueNetId &InActorId,
    const FString &InObjectId,
    const TCHAR *InCall,
    const FString &InContextMsg);
const FOnlineError &UpsertNotAllowed();
const FOnlineError UpsertNotAllowed(const TCHAR *InCall, const FString &InContextMsg);
const FOnlineError UpsertNotAllowed(const TCHAR *InCall, const TCHAR *InContextMsg);
const FOnlineError UpsertNotAllowed(const FUniqueNetId &InActorId, const TCHAR *InCall, const FString &InContextMsg);
const FOnlineError UpsertNotAllowed(const FUniqueNetId &InActorId);
const FOnlineError UpsertNotAllowed(
    const FUniqueNetId &InActorId,
    const FString &InObjectId,
    const TCHAR *InCall,
    const FString &InContextMsg);
const FOnlineError &AggregationFailed();
const FOnlineError AggregationFailed(const TCHAR *InCall, const FString &InContextMsg);
const FOnlineError AggregationFailed(const TCHAR *InCall, const TCHAR *InContextMsg);
const FOnlineError AggregationFailed(const FUniqueNetId &InActorId, const TCHAR *InCall, const FString &InContextMsg);
const FOnlineError AggregationFailed(const FUniqueNetId &InActorId);
const FOnlineError AggregationFailed(
    const FUniqueNetId &InActorId,
    const FString &InObjectId,
    const TCHAR *InCall,
    const FString &InContextMsg);
const FOnlineError &HostAtCapacity();
const FOnlineError HostAtCapacity(const TCHAR *InCall, const FString &InContextMsg);
const FOnlineError HostAtCapacity(const TCHAR *InCall, const TCHAR *InContextMsg);
const FOnlineError HostAtCapacity(const FUniqueNetId &InActorId, const TCHAR *InCall, const FString &InContextMsg);
const FOnlineError HostAtCapacity(const FUniqueNetId &InActorId);
const FOnlineError HostAtCapacity(
    const FUniqueNetId &InActorId,
    const FString &InObjectId,
    const TCHAR *InCall,
    const FString &InContextMsg);
const FOnlineError &SandboxAtCapacity();
const FOnlineError SandboxAtCapacity(const TCHAR *InCall, const FString &InContextMsg);
const FOnlineError SandboxAtCapacity(const TCHAR *InCall, const TCHAR *InContextMsg);
const FOnlineError SandboxAtCapacity(const FUniqueNetId &InActorId, const TCHAR *InCall, const FString &InContextMsg);
const FOnlineError SandboxAtCapacity(const FUniqueNetId &InActorId);
const FOnlineError SandboxAtCapacity(
    const FUniqueNetId &InActorId,
    const FString &InObjectId,
    const TCHAR *InCall,
    const FString &InContextMsg);
const FOnlineError &SessionNotAnonymous();
const FOnlineError SessionNotAnonymous(const TCHAR *InCall, const FString &InContextMsg);
const FOnlineError SessionNotAnonymous(const TCHAR *InCall, const TCHAR *InContextMsg);
const FOnlineError SessionNotAnonymous(const FUniqueNetId &InActorId, const TCHAR *InCall, const FString &InContextMsg);
const FOnlineError SessionNotAnonymous(const FUniqueNetId &InActorId);
const FOnlineError SessionNotAnonymous(
    const FUniqueNetId &InActorId,
    const FString &InObjectId,
    const TCHAR *InCall,
    const FString &InContextMsg);
const FOnlineError &OutOfSync();
const FOnlineError OutOfSync(const TCHAR *InCall, const FString &InContextMsg);
const FOnlineError OutOfSync(const TCHAR *InCall, const TCHAR *InContextMsg);
const FOnlineError OutOfSync(const FUniqueNetId &InActorId, const TCHAR *InCall, const FString &InContextMsg);
const FOnlineError OutOfSync(const FUniqueNetId &InActorId);
const FOnlineError OutOfSync(
    const FUniqueNetId &InActorId,
    const FString &InObjectId,
    const TCHAR *InCall,
    const FString &InContextMsg);
const FOnlineError &TooManyInvites();
const FOnlineError TooManyInvites(const TCHAR *InCall, const FString &InContextMsg);
const FOnlineError TooManyInvites(const TCHAR *InCall, const TCHAR *InContextMsg);
const FOnlineError TooManyInvites(const FUniqueNetId &InActorId, const TCHAR *InCall, const FString &InContextMsg);
const FOnlineError TooManyInvites(const FUniqueNetId &InActorId);
const FOnlineError TooManyInvites(
    const FUniqueNetId &InActorId,
    const FString &InObjectId,
    const TCHAR *InCall,
    const FString &InContextMsg);
const FOnlineError &PresenceSessionExists();
const FOnlineError PresenceSessionExists(const TCHAR *InCall, const FString &InContextMsg);
const FOnlineError PresenceSessionExists(const TCHAR *InCall, const TCHAR *InContextMsg);
const FOnlineError PresenceSessionExists(
    const FUniqueNetId &InActorId,
    const TCHAR *InCall,
    const FString &InContextMsg);
const FOnlineError PresenceSessionExists(const FUniqueNetId &InActorId);
const FOnlineError PresenceSessionExists(
    const FUniqueNetId &InActorId,
    const FString &InObjectId,
    const TCHAR *InCall,
    const FString &InContextMsg);
const FOnlineError &DeploymentAtCapacity();
const FOnlineError DeploymentAtCapacity(const TCHAR *InCall, const FString &InContextMsg);
const FOnlineError DeploymentAtCapacity(const TCHAR *InCall, const TCHAR *InContextMsg);
const FOnlineError DeploymentAtCapacity(
    const FUniqueNetId &InActorId,
    const TCHAR *InCall,
    const FString &InContextMsg);
const FOnlineError DeploymentAtCapacity(const FUniqueNetId &InActorId);
const FOnlineError DeploymentAtCapacity(
    const FUniqueNetId &InActorId,
    const FString &InObjectId,
    const TCHAR *InCall,
    const FString &InContextMsg);
const FOnlineError &NotAllowed();
const FOnlineError NotAllowed(const TCHAR *InCall, const FString &InContextMsg);
const FOnlineError NotAllowed(const TCHAR *InCall, const TCHAR *InContextMsg);
const FOnlineError NotAllowed(const FUniqueNetId &InActorId, const TCHAR *InCall, const FString &InContextMsg);
const FOnlineError NotAllowed(const FUniqueNetId &InActorId);
const FOnlineError NotAllowed(
    const FUniqueNetId &InActorId,
    const FString &InObjectId,
    const TCHAR *InCall,
    const FString &InContextMsg);
} // namespace Sessions
namespace PlayerDataStorage
{
const FOnlineError &FilenameInvalid();
const FOnlineError FilenameInvalid(const TCHAR *InCall, const FString &InContextMsg);
const FOnlineError FilenameInvalid(const TCHAR *InCall, const TCHAR *InContextMsg);
const FOnlineError FilenameInvalid(const FUniqueNetId &InActorId, const TCHAR *InCall, const FString &InContextMsg);
const FOnlineError FilenameInvalid(const FUniqueNetId &InActorId);
const FOnlineError FilenameInvalid(
    const FUniqueNetId &InActorId,
    const FString &InObjectId,
    const TCHAR *InCall,
    const FString &InContextMsg);
const FOnlineError &FilenameLengthInvalid();
const FOnlineError FilenameLengthInvalid(const TCHAR *InCall, const FString &InContextMsg);
const FOnlineError FilenameLengthInvalid(const TCHAR *InCall, const TCHAR *InContextMsg);
const FOnlineError FilenameLengthInvalid(
    const FUniqueNetId &InActorId,
    const TCHAR *InCall,
    const FString &InContextMsg);
const FOnlineError FilenameLengthInvalid(const FUniqueNetId &InActorId);
const FOnlineError FilenameLengthInvalid(
    const FUniqueNetId &InActorId,
    const FString &InObjectId,
    const TCHAR *InCall,
    const FString &InContextMsg);
const FOnlineError &FilenameInvalidChars();
const FOnlineError FilenameInvalidChars(const TCHAR *InCall, const FString &InContextMsg);
const FOnlineError FilenameInvalidChars(const TCHAR *InCall, const TCHAR *InContextMsg);
const FOnlineError FilenameInvalidChars(
    const FUniqueNetId &InActorId,
    const TCHAR *InCall,
    const FString &InContextMsg);
const FOnlineError FilenameInvalidChars(const FUniqueNetId &InActorId);
const FOnlineError FilenameInvalidChars(
    const FUniqueNetId &InActorId,
    const FString &InObjectId,
    const TCHAR *InCall,
    const FString &InContextMsg);
const FOnlineError &FileSizeTooLarge();
const FOnlineError FileSizeTooLarge(const TCHAR *InCall, const FString &InContextMsg);
const FOnlineError FileSizeTooLarge(const TCHAR *InCall, const TCHAR *InContextMsg);
const FOnlineError FileSizeTooLarge(const FUniqueNetId &InActorId, const TCHAR *InCall, const FString &InContextMsg);
const FOnlineError FileSizeTooLarge(const FUniqueNetId &InActorId);
const FOnlineError FileSizeTooLarge(
    const FUniqueNetId &InActorId,
    const FString &InObjectId,
    const TCHAR *InCall,
    const FString &InContextMsg);
const FOnlineError &FileSizeInvalid();
const FOnlineError FileSizeInvalid(const TCHAR *InCall, const FString &InContextMsg);
const FOnlineError FileSizeInvalid(const TCHAR *InCall, const TCHAR *InContextMsg);
const FOnlineError FileSizeInvalid(const FUniqueNetId &InActorId, const TCHAR *InCall, const FString &InContextMsg);
const FOnlineError FileSizeInvalid(const FUniqueNetId &InActorId);
const FOnlineError FileSizeInvalid(
    const FUniqueNetId &InActorId,
    const FString &InObjectId,
    const TCHAR *InCall,
    const FString &InContextMsg);
const FOnlineError &FileHandleInvalid();
const FOnlineError FileHandleInvalid(const TCHAR *InCall, const FString &InContextMsg);
const FOnlineError FileHandleInvalid(const TCHAR *InCall, const TCHAR *InContextMsg);
const FOnlineError FileHandleInvalid(const FUniqueNetId &InActorId, const TCHAR *InCall, const FString &InContextMsg);
const FOnlineError FileHandleInvalid(const FUniqueNetId &InActorId);
const FOnlineError FileHandleInvalid(
    const FUniqueNetId &InActorId,
    const FString &InObjectId,
    const TCHAR *InCall,
    const FString &InContextMsg);
const FOnlineError &DataInvalid();
const FOnlineError DataInvalid(const TCHAR *InCall, const FString &InContextMsg);
const FOnlineError DataInvalid(const TCHAR *InCall, const TCHAR *InContextMsg);
const FOnlineError DataInvalid(const FUniqueNetId &InActorId, const TCHAR *InCall, const FString &InContextMsg);
const FOnlineError DataInvalid(const FUniqueNetId &InActorId);
const FOnlineError DataInvalid(
    const FUniqueNetId &InActorId,
    const FString &InObjectId,
    const TCHAR *InCall,
    const FString &InContextMsg);
const FOnlineError &DataLengthInvalid();
const FOnlineError DataLengthInvalid(const TCHAR *InCall, const FString &InContextMsg);
const FOnlineError DataLengthInvalid(const TCHAR *InCall, const TCHAR *InContextMsg);
const FOnlineError DataLengthInvalid(const FUniqueNetId &InActorId, const TCHAR *InCall, const FString &InContextMsg);
const FOnlineError DataLengthInvalid(const FUniqueNetId &InActorId);
const FOnlineError DataLengthInvalid(
    const FUniqueNetId &InActorId,
    const FString &InObjectId,
    const TCHAR *InCall,
    const FString &InContextMsg);
const FOnlineError &StartIndexInvalid();
const FOnlineError StartIndexInvalid(const TCHAR *InCall, const FString &InContextMsg);
const FOnlineError StartIndexInvalid(const TCHAR *InCall, const TCHAR *InContextMsg);
const FOnlineError StartIndexInvalid(const FUniqueNetId &InActorId, const TCHAR *InCall, const FString &InContextMsg);
const FOnlineError StartIndexInvalid(const FUniqueNetId &InActorId);
const FOnlineError StartIndexInvalid(
    const FUniqueNetId &InActorId,
    const FString &InObjectId,
    const TCHAR *InCall,
    const FString &InContextMsg);
const FOnlineError &RequestInProgress();
const FOnlineError RequestInProgress(const TCHAR *InCall, const FString &InContextMsg);
const FOnlineError RequestInProgress(const TCHAR *InCall, const TCHAR *InContextMsg);
const FOnlineError RequestInProgress(const FUniqueNetId &InActorId, const TCHAR *InCall, const FString &InContextMsg);
const FOnlineError RequestInProgress(const FUniqueNetId &InActorId);
const FOnlineError RequestInProgress(
    const FUniqueNetId &InActorId,
    const FString &InObjectId,
    const TCHAR *InCall,
    const FString &InContextMsg);
const FOnlineError &UserThrottled();
const FOnlineError UserThrottled(const TCHAR *InCall, const FString &InContextMsg);
const FOnlineError UserThrottled(const TCHAR *InCall, const TCHAR *InContextMsg);
const FOnlineError UserThrottled(const FUniqueNetId &InActorId, const TCHAR *InCall, const FString &InContextMsg);
const FOnlineError UserThrottled(const FUniqueNetId &InActorId);
const FOnlineError UserThrottled(
    const FUniqueNetId &InActorId,
    const FString &InObjectId,
    const TCHAR *InCall,
    const FString &InContextMsg);
const FOnlineError &EncryptionKeyNotSet();
const FOnlineError EncryptionKeyNotSet(const TCHAR *InCall, const FString &InContextMsg);
const FOnlineError EncryptionKeyNotSet(const TCHAR *InCall, const TCHAR *InContextMsg);
const FOnlineError EncryptionKeyNotSet(const FUniqueNetId &InActorId, const TCHAR *InCall, const FString &InContextMsg);
const FOnlineError EncryptionKeyNotSet(const FUniqueNetId &InActorId);
const FOnlineError EncryptionKeyNotSet(
    const FUniqueNetId &InActorId,
    const FString &InObjectId,
    const TCHAR *InCall,
    const FString &InContextMsg);
const FOnlineError &UserErrorFromDataCallback();
const FOnlineError UserErrorFromDataCallback(const TCHAR *InCall, const FString &InContextMsg);
const FOnlineError UserErrorFromDataCallback(const TCHAR *InCall, const TCHAR *InContextMsg);
const FOnlineError UserErrorFromDataCallback(
    const FUniqueNetId &InActorId,
    const TCHAR *InCall,
    const FString &InContextMsg);
const FOnlineError UserErrorFromDataCallback(const FUniqueNetId &InActorId);
const FOnlineError UserErrorFromDataCallback(
    const FUniqueNetId &InActorId,
    const FString &InObjectId,
    const TCHAR *InCall,
    const FString &InContextMsg);
const FOnlineError &FileHeaderHasNewerVersion();
const FOnlineError FileHeaderHasNewerVersion(const TCHAR *InCall, const FString &InContextMsg);
const FOnlineError FileHeaderHasNewerVersion(const TCHAR *InCall, const TCHAR *InContextMsg);
const FOnlineError FileHeaderHasNewerVersion(
    const FUniqueNetId &InActorId,
    const TCHAR *InCall,
    const FString &InContextMsg);
const FOnlineError FileHeaderHasNewerVersion(const FUniqueNetId &InActorId);
const FOnlineError FileHeaderHasNewerVersion(
    const FUniqueNetId &InActorId,
    const FString &InObjectId,
    const TCHAR *InCall,
    const FString &InContextMsg);
const FOnlineError &FileCorrupted();
const FOnlineError FileCorrupted(const TCHAR *InCall, const FString &InContextMsg);
const FOnlineError FileCorrupted(const TCHAR *InCall, const TCHAR *InContextMsg);
const FOnlineError FileCorrupted(const FUniqueNetId &InActorId, const TCHAR *InCall, const FString &InContextMsg);
const FOnlineError FileCorrupted(const FUniqueNetId &InActorId);
const FOnlineError FileCorrupted(
    const FUniqueNetId &InActorId,
    const FString &InObjectId,
    const TCHAR *InCall,
    const FString &InContextMsg);
} // namespace PlayerDataStorage
namespace Connect
{
const FOnlineError &ExternalTokenValidationFailed();
const FOnlineError ExternalTokenValidationFailed(const TCHAR *InCall, const FString &InContextMsg);
const FOnlineError ExternalTokenValidationFailed(const TCHAR *InCall, const TCHAR *InContextMsg);
const FOnlineError ExternalTokenValidationFailed(
    const FUniqueNetId &InActorId,
    const TCHAR *InCall,
    const FString &InContextMsg);
const FOnlineError ExternalTokenValidationFailed(const FUniqueNetId &InActorId);
const FOnlineError ExternalTokenValidationFailed(
    const FUniqueNetId &InActorId,
    const FString &InObjectId,
    const TCHAR *InCall,
    const FString &InContextMsg);
const FOnlineError &UserAlreadyExists();
const FOnlineError UserAlreadyExists(const TCHAR *InCall, const FString &InContextMsg);
const FOnlineError UserAlreadyExists(const TCHAR *InCall, const TCHAR *InContextMsg);
const FOnlineError UserAlreadyExists(const FUniqueNetId &InActorId, const TCHAR *InCall, const FString &InContextMsg);
const FOnlineError UserAlreadyExists(const FUniqueNetId &InActorId);
const FOnlineError UserAlreadyExists(
    const FUniqueNetId &InActorId,
    const FString &InObjectId,
    const TCHAR *InCall,
    const FString &InContextMsg);
const FOnlineError &AuthExpired();
const FOnlineError AuthExpired(const TCHAR *InCall, const FString &InContextMsg);
const FOnlineError AuthExpired(const TCHAR *InCall, const TCHAR *InContextMsg);
const FOnlineError AuthExpired(const FUniqueNetId &InActorId, const TCHAR *InCall, const FString &InContextMsg);
const FOnlineError AuthExpired(const FUniqueNetId &InActorId);
const FOnlineError AuthExpired(
    const FUniqueNetId &InActorId,
    const FString &InObjectId,
    const TCHAR *InCall,
    const FString &InContextMsg);
const FOnlineError &InvalidToken();
const FOnlineError InvalidToken(const TCHAR *InCall, const FString &InContextMsg);
const FOnlineError InvalidToken(const TCHAR *InCall, const TCHAR *InContextMsg);
const FOnlineError InvalidToken(const FUniqueNetId &InActorId, const TCHAR *InCall, const FString &InContextMsg);
const FOnlineError InvalidToken(const FUniqueNetId &InActorId);
const FOnlineError InvalidToken(
    const FUniqueNetId &InActorId,
    const FString &InObjectId,
    const TCHAR *InCall,
    const FString &InContextMsg);
const FOnlineError &UnsupportedTokenType();
const FOnlineError UnsupportedTokenType(const TCHAR *InCall, const FString &InContextMsg);
const FOnlineError UnsupportedTokenType(const TCHAR *InCall, const TCHAR *InContextMsg);
const FOnlineError UnsupportedTokenType(
    const FUniqueNetId &InActorId,
    const TCHAR *InCall,
    const FString &InContextMsg);
const FOnlineError UnsupportedTokenType(const FUniqueNetId &InActorId);
const FOnlineError UnsupportedTokenType(
    const FUniqueNetId &InActorId,
    const FString &InObjectId,
    const TCHAR *InCall,
    const FString &InContextMsg);
const FOnlineError &LinkAccountFailed();
const FOnlineError LinkAccountFailed(const TCHAR *InCall, const FString &InContextMsg);
const FOnlineError LinkAccountFailed(const TCHAR *InCall, const TCHAR *InContextMsg);
const FOnlineError LinkAccountFailed(const FUniqueNetId &InActorId, const TCHAR *InCall, const FString &InContextMsg);
const FOnlineError LinkAccountFailed(const FUniqueNetId &InActorId);
const FOnlineError LinkAccountFailed(
    const FUniqueNetId &InActorId,
    const FString &InObjectId,
    const TCHAR *InCall,
    const FString &InContextMsg);
const FOnlineError &ExternalServiceUnavailable();
const FOnlineError ExternalServiceUnavailable(const TCHAR *InCall, const FString &InContextMsg);
const FOnlineError ExternalServiceUnavailable(const TCHAR *InCall, const TCHAR *InContextMsg);
const FOnlineError ExternalServiceUnavailable(
    const FUniqueNetId &InActorId,
    const TCHAR *InCall,
    const FString &InContextMsg);
const FOnlineError ExternalServiceUnavailable(const FUniqueNetId &InActorId);
const FOnlineError ExternalServiceUnavailable(
    const FUniqueNetId &InActorId,
    const FString &InObjectId,
    const TCHAR *InCall,
    const FString &InContextMsg);
const FOnlineError &ExternalServiceConfigurationFailure();
const FOnlineError ExternalServiceConfigurationFailure(const TCHAR *InCall, const FString &InContextMsg);
const FOnlineError ExternalServiceConfigurationFailure(const TCHAR *InCall, const TCHAR *InContextMsg);
const FOnlineError ExternalServiceConfigurationFailure(
    const FUniqueNetId &InActorId,
    const TCHAR *InCall,
    const FString &InContextMsg);
const FOnlineError ExternalServiceConfigurationFailure(const FUniqueNetId &InActorId);
const FOnlineError ExternalServiceConfigurationFailure(
    const FUniqueNetId &InActorId,
    const FString &InObjectId,
    const TCHAR *InCall,
    const FString &InContextMsg);
const FOnlineError &LinkAccountFailedMissingNintendoIdAccount();
const FOnlineError LinkAccountFailedMissingNintendoIdAccount(const TCHAR *InCall, const FString &InContextMsg);
const FOnlineError LinkAccountFailedMissingNintendoIdAccount(const TCHAR *InCall, const TCHAR *InContextMsg);
const FOnlineError LinkAccountFailedMissingNintendoIdAccount(
    const FUniqueNetId &InActorId,
    const TCHAR *InCall,
    const FString &InContextMsg);
const FOnlineError LinkAccountFailedMissingNintendoIdAccount(const FUniqueNetId &InActorId);
const FOnlineError LinkAccountFailedMissingNintendoIdAccount(
    const FUniqueNetId &InActorId,
    const FString &InObjectId,
    const TCHAR *InCall,
    const FString &InContextMsg);
} // namespace Connect
namespace UI
{
const FOnlineError &SocialOverlayLoadError();
const FOnlineError SocialOverlayLoadError(const TCHAR *InCall, const FString &InContextMsg);
const FOnlineError SocialOverlayLoadError(const TCHAR *InCall, const TCHAR *InContextMsg);
const FOnlineError SocialOverlayLoadError(
    const FUniqueNetId &InActorId,
    const TCHAR *InCall,
    const FString &InContextMsg);
const FOnlineError SocialOverlayLoadError(const FUniqueNetId &InActorId);
const FOnlineError SocialOverlayLoadError(
    const FUniqueNetId &InActorId,
    const FString &InObjectId,
    const TCHAR *InCall,
    const FString &InContextMsg);
} // namespace UI
namespace Lobby
{
const FOnlineError &NotOwner();
const FOnlineError NotOwner(const TCHAR *InCall, const FString &InContextMsg);
const FOnlineError NotOwner(const TCHAR *InCall, const TCHAR *InContextMsg);
const FOnlineError NotOwner(const FUniqueNetId &InActorId, const TCHAR *InCall, const FString &InContextMsg);
const FOnlineError NotOwner(const FUniqueNetId &InActorId);
const FOnlineError NotOwner(
    const FUniqueNetId &InActorId,
    const FString &InObjectId,
    const TCHAR *InCall,
    const FString &InContextMsg);
const FOnlineError &InvalidLock();
const FOnlineError InvalidLock(const TCHAR *InCall, const FString &InContextMsg);
const FOnlineError InvalidLock(const TCHAR *InCall, const TCHAR *InContextMsg);
const FOnlineError InvalidLock(const FUniqueNetId &InActorId, const TCHAR *InCall, const FString &InContextMsg);
const FOnlineError InvalidLock(const FUniqueNetId &InActorId);
const FOnlineError InvalidLock(
    const FUniqueNetId &InActorId,
    const FString &InObjectId,
    const TCHAR *InCall,
    const FString &InContextMsg);
const FOnlineError &LobbyAlreadyExists();
const FOnlineError LobbyAlreadyExists(const TCHAR *InCall, const FString &InContextMsg);
const FOnlineError LobbyAlreadyExists(const TCHAR *InCall, const TCHAR *InContextMsg);
const FOnlineError LobbyAlreadyExists(const FUniqueNetId &InActorId, const TCHAR *InCall, const FString &InContextMsg);
const FOnlineError LobbyAlreadyExists(const FUniqueNetId &InActorId);
const FOnlineError LobbyAlreadyExists(
    const FUniqueNetId &InActorId,
    const FString &InObjectId,
    const TCHAR *InCall,
    const FString &InContextMsg);
const FOnlineError &SessionInProgress();
const FOnlineError SessionInProgress(const TCHAR *InCall, const FString &InContextMsg);
const FOnlineError SessionInProgress(const TCHAR *InCall, const TCHAR *InContextMsg);
const FOnlineError SessionInProgress(const FUniqueNetId &InActorId, const TCHAR *InCall, const FString &InContextMsg);
const FOnlineError SessionInProgress(const FUniqueNetId &InActorId);
const FOnlineError SessionInProgress(
    const FUniqueNetId &InActorId,
    const FString &InObjectId,
    const TCHAR *InCall,
    const FString &InContextMsg);
const FOnlineError &TooManyPlayers();
const FOnlineError TooManyPlayers(const TCHAR *InCall, const FString &InContextMsg);
const FOnlineError TooManyPlayers(const TCHAR *InCall, const TCHAR *InContextMsg);
const FOnlineError TooManyPlayers(const FUniqueNetId &InActorId, const TCHAR *InCall, const FString &InContextMsg);
const FOnlineError TooManyPlayers(const FUniqueNetId &InActorId);
const FOnlineError TooManyPlayers(
    const FUniqueNetId &InActorId,
    const FString &InObjectId,
    const TCHAR *InCall,
    const FString &InContextMsg);
const FOnlineError &NoPermission();
const FOnlineError NoPermission(const TCHAR *InCall, const FString &InContextMsg);
const FOnlineError NoPermission(const TCHAR *InCall, const TCHAR *InContextMsg);
const FOnlineError NoPermission(const FUniqueNetId &InActorId, const TCHAR *InCall, const FString &InContextMsg);
const FOnlineError NoPermission(const FUniqueNetId &InActorId);
const FOnlineError NoPermission(
    const FUniqueNetId &InActorId,
    const FString &InObjectId,
    const TCHAR *InCall,
    const FString &InContextMsg);
const FOnlineError &InvalidSession();
const FOnlineError InvalidSession(const TCHAR *InCall, const FString &InContextMsg);
const FOnlineError InvalidSession(const TCHAR *InCall, const TCHAR *InContextMsg);
const FOnlineError InvalidSession(const FUniqueNetId &InActorId, const TCHAR *InCall, const FString &InContextMsg);
const FOnlineError InvalidSession(const FUniqueNetId &InActorId);
const FOnlineError InvalidSession(
    const FUniqueNetId &InActorId,
    const FString &InObjectId,
    const TCHAR *InCall,
    const FString &InContextMsg);
const FOnlineError &SandboxNotAllowed();
const FOnlineError SandboxNotAllowed(const TCHAR *InCall, const FString &InContextMsg);
const FOnlineError SandboxNotAllowed(const TCHAR *InCall, const TCHAR *InContextMsg);
const FOnlineError SandboxNotAllowed(const FUniqueNetId &InActorId, const TCHAR *InCall, const FString &InContextMsg);
const FOnlineError SandboxNotAllowed(const FUniqueNetId &InActorId);
const FOnlineError SandboxNotAllowed(
    const FUniqueNetId &InActorId,
    const FString &InObjectId,
    const TCHAR *InCall,
    const FString &InContextMsg);
const FOnlineError &InviteFailed();
const FOnlineError InviteFailed(const TCHAR *InCall, const FString &InContextMsg);
const FOnlineError InviteFailed(const TCHAR *InCall, const TCHAR *InContextMsg);
const FOnlineError InviteFailed(const FUniqueNetId &InActorId, const TCHAR *InCall, const FString &InContextMsg);
const FOnlineError InviteFailed(const FUniqueNetId &InActorId);
const FOnlineError InviteFailed(
    const FUniqueNetId &InActorId,
    const FString &InObjectId,
    const TCHAR *InCall,
    const FString &InContextMsg);
const FOnlineError &InviteNotFound();
const FOnlineError InviteNotFound(const TCHAR *InCall, const FString &InContextMsg);
const FOnlineError InviteNotFound(const TCHAR *InCall, const TCHAR *InContextMsg);
const FOnlineError InviteNotFound(const FUniqueNetId &InActorId, const TCHAR *InCall, const FString &InContextMsg);
const FOnlineError InviteNotFound(const FUniqueNetId &InActorId);
const FOnlineError InviteNotFound(
    const FUniqueNetId &InActorId,
    const FString &InObjectId,
    const TCHAR *InCall,
    const FString &InContextMsg);
const FOnlineError &UpsertNotAllowed();
const FOnlineError UpsertNotAllowed(const TCHAR *InCall, const FString &InContextMsg);
const FOnlineError UpsertNotAllowed(const TCHAR *InCall, const TCHAR *InContextMsg);
const FOnlineError UpsertNotAllowed(const FUniqueNetId &InActorId, const TCHAR *InCall, const FString &InContextMsg);
const FOnlineError UpsertNotAllowed(const FUniqueNetId &InActorId);
const FOnlineError UpsertNotAllowed(
    const FUniqueNetId &InActorId,
    const FString &InObjectId,
    const TCHAR *InCall,
    const FString &InContextMsg);
const FOnlineError &AggregationFailed();
const FOnlineError AggregationFailed(const TCHAR *InCall, const FString &InContextMsg);
const FOnlineError AggregationFailed(const TCHAR *InCall, const TCHAR *InContextMsg);
const FOnlineError AggregationFailed(const FUniqueNetId &InActorId, const TCHAR *InCall, const FString &InContextMsg);
const FOnlineError AggregationFailed(const FUniqueNetId &InActorId);
const FOnlineError AggregationFailed(
    const FUniqueNetId &InActorId,
    const FString &InObjectId,
    const TCHAR *InCall,
    const FString &InContextMsg);
const FOnlineError &HostAtCapacity();
const FOnlineError HostAtCapacity(const TCHAR *InCall, const FString &InContextMsg);
const FOnlineError HostAtCapacity(const TCHAR *InCall, const TCHAR *InContextMsg);
const FOnlineError HostAtCapacity(const FUniqueNetId &InActorId, const TCHAR *InCall, const FString &InContextMsg);
const FOnlineError HostAtCapacity(const FUniqueNetId &InActorId);
const FOnlineError HostAtCapacity(
    const FUniqueNetId &InActorId,
    const FString &InObjectId,
    const TCHAR *InCall,
    const FString &InContextMsg);
const FOnlineError &SandboxAtCapacity();
const FOnlineError SandboxAtCapacity(const TCHAR *InCall, const FString &InContextMsg);
const FOnlineError SandboxAtCapacity(const TCHAR *InCall, const TCHAR *InContextMsg);
const FOnlineError SandboxAtCapacity(const FUniqueNetId &InActorId, const TCHAR *InCall, const FString &InContextMsg);
const FOnlineError SandboxAtCapacity(const FUniqueNetId &InActorId);
const FOnlineError SandboxAtCapacity(
    const FUniqueNetId &InActorId,
    const FString &InObjectId,
    const TCHAR *InCall,
    const FString &InContextMsg);
const FOnlineError &TooManyInvites();
const FOnlineError TooManyInvites(const TCHAR *InCall, const FString &InContextMsg);
const FOnlineError TooManyInvites(const TCHAR *InCall, const TCHAR *InContextMsg);
const FOnlineError TooManyInvites(const FUniqueNetId &InActorId, const TCHAR *InCall, const FString &InContextMsg);
const FOnlineError TooManyInvites(const FUniqueNetId &InActorId);
const FOnlineError TooManyInvites(
    const FUniqueNetId &InActorId,
    const FString &InObjectId,
    const TCHAR *InCall,
    const FString &InContextMsg);
const FOnlineError &DeploymentAtCapacity();
const FOnlineError DeploymentAtCapacity(const TCHAR *InCall, const FString &InContextMsg);
const FOnlineError DeploymentAtCapacity(const TCHAR *InCall, const TCHAR *InContextMsg);
const FOnlineError DeploymentAtCapacity(
    const FUniqueNetId &InActorId,
    const TCHAR *InCall,
    const FString &InContextMsg);
const FOnlineError DeploymentAtCapacity(const FUniqueNetId &InActorId);
const FOnlineError DeploymentAtCapacity(
    const FUniqueNetId &InActorId,
    const FString &InObjectId,
    const TCHAR *InCall,
    const FString &InContextMsg);
const FOnlineError &NotAllowed();
const FOnlineError NotAllowed(const TCHAR *InCall, const FString &InContextMsg);
const FOnlineError NotAllowed(const TCHAR *InCall, const TCHAR *InContextMsg);
const FOnlineError NotAllowed(const FUniqueNetId &InActorId, const TCHAR *InCall, const FString &InContextMsg);
const FOnlineError NotAllowed(const FUniqueNetId &InActorId);
const FOnlineError NotAllowed(
    const FUniqueNetId &InActorId,
    const FString &InObjectId,
    const TCHAR *InCall,
    const FString &InContextMsg);
const FOnlineError &MemberUpdateOnly();
const FOnlineError MemberUpdateOnly(const TCHAR *InCall, const FString &InContextMsg);
const FOnlineError MemberUpdateOnly(const TCHAR *InCall, const TCHAR *InContextMsg);
const FOnlineError MemberUpdateOnly(const FUniqueNetId &InActorId, const TCHAR *InCall, const FString &InContextMsg);
const FOnlineError MemberUpdateOnly(const FUniqueNetId &InActorId);
const FOnlineError MemberUpdateOnly(
    const FUniqueNetId &InActorId,
    const FString &InObjectId,
    const TCHAR *InCall,
    const FString &InContextMsg);
const FOnlineError &PresenceLobbyExists();
const FOnlineError PresenceLobbyExists(const TCHAR *InCall, const FString &InContextMsg);
const FOnlineError PresenceLobbyExists(const TCHAR *InCall, const TCHAR *InContextMsg);
const FOnlineError PresenceLobbyExists(const FUniqueNetId &InActorId, const TCHAR *InCall, const FString &InContextMsg);
const FOnlineError PresenceLobbyExists(const FUniqueNetId &InActorId);
const FOnlineError PresenceLobbyExists(
    const FUniqueNetId &InActorId,
    const FString &InObjectId,
    const TCHAR *InCall,
    const FString &InContextMsg);
} // namespace Lobby
namespace TitleStorage
{
const FOnlineError &UserErrorFromDataCallback();
const FOnlineError UserErrorFromDataCallback(const TCHAR *InCall, const FString &InContextMsg);
const FOnlineError UserErrorFromDataCallback(const TCHAR *InCall, const TCHAR *InContextMsg);
const FOnlineError UserErrorFromDataCallback(
    const FUniqueNetId &InActorId,
    const TCHAR *InCall,
    const FString &InContextMsg);
const FOnlineError UserErrorFromDataCallback(const FUniqueNetId &InActorId);
const FOnlineError UserErrorFromDataCallback(
    const FUniqueNetId &InActorId,
    const FString &InObjectId,
    const TCHAR *InCall,
    const FString &InContextMsg);
const FOnlineError &EncryptionKeyNotSet();
const FOnlineError EncryptionKeyNotSet(const TCHAR *InCall, const FString &InContextMsg);
const FOnlineError EncryptionKeyNotSet(const TCHAR *InCall, const TCHAR *InContextMsg);
const FOnlineError EncryptionKeyNotSet(const FUniqueNetId &InActorId, const TCHAR *InCall, const FString &InContextMsg);
const FOnlineError EncryptionKeyNotSet(const FUniqueNetId &InActorId);
const FOnlineError EncryptionKeyNotSet(
    const FUniqueNetId &InActorId,
    const FString &InObjectId,
    const TCHAR *InCall,
    const FString &InContextMsg);
const FOnlineError &FileCorrupted();
const FOnlineError FileCorrupted(const TCHAR *InCall, const FString &InContextMsg);
const FOnlineError FileCorrupted(const TCHAR *InCall, const TCHAR *InContextMsg);
const FOnlineError FileCorrupted(const FUniqueNetId &InActorId, const TCHAR *InCall, const FString &InContextMsg);
const FOnlineError FileCorrupted(const FUniqueNetId &InActorId);
const FOnlineError FileCorrupted(
    const FUniqueNetId &InActorId,
    const FString &InObjectId,
    const TCHAR *InCall,
    const FString &InContextMsg);
const FOnlineError &FileHeaderHasNewerVersion();
const FOnlineError FileHeaderHasNewerVersion(const TCHAR *InCall, const FString &InContextMsg);
const FOnlineError FileHeaderHasNewerVersion(const TCHAR *InCall, const TCHAR *InContextMsg);
const FOnlineError FileHeaderHasNewerVersion(
    const FUniqueNetId &InActorId,
    const TCHAR *InCall,
    const FString &InContextMsg);
const FOnlineError FileHeaderHasNewerVersion(const FUniqueNetId &InActorId);
const FOnlineError FileHeaderHasNewerVersion(
    const FUniqueNetId &InActorId,
    const FString &InObjectId,
    const TCHAR *InCall,
    const FString &InContextMsg);
} // namespace TitleStorage
namespace Mods
{
const FOnlineError &ModSdkProcessIsAlreadyRunning();
const FOnlineError ModSdkProcessIsAlreadyRunning(const TCHAR *InCall, const FString &InContextMsg);
const FOnlineError ModSdkProcessIsAlreadyRunning(const TCHAR *InCall, const TCHAR *InContextMsg);
const FOnlineError ModSdkProcessIsAlreadyRunning(
    const FUniqueNetId &InActorId,
    const TCHAR *InCall,
    const FString &InContextMsg);
const FOnlineError ModSdkProcessIsAlreadyRunning(const FUniqueNetId &InActorId);
const FOnlineError ModSdkProcessIsAlreadyRunning(
    const FUniqueNetId &InActorId,
    const FString &InObjectId,
    const TCHAR *InCall,
    const FString &InContextMsg);
const FOnlineError &ModSdkCommandIsEmpty();
const FOnlineError ModSdkCommandIsEmpty(const TCHAR *InCall, const FString &InContextMsg);
const FOnlineError ModSdkCommandIsEmpty(const TCHAR *InCall, const TCHAR *InContextMsg);
const FOnlineError ModSdkCommandIsEmpty(
    const FUniqueNetId &InActorId,
    const TCHAR *InCall,
    const FString &InContextMsg);
const FOnlineError ModSdkCommandIsEmpty(const FUniqueNetId &InActorId);
const FOnlineError ModSdkCommandIsEmpty(
    const FUniqueNetId &InActorId,
    const FString &InObjectId,
    const TCHAR *InCall,
    const FString &InContextMsg);
const FOnlineError &ModSdkProcessCreationFailed();
const FOnlineError ModSdkProcessCreationFailed(const TCHAR *InCall, const FString &InContextMsg);
const FOnlineError ModSdkProcessCreationFailed(const TCHAR *InCall, const TCHAR *InContextMsg);
const FOnlineError ModSdkProcessCreationFailed(
    const FUniqueNetId &InActorId,
    const TCHAR *InCall,
    const FString &InContextMsg);
const FOnlineError ModSdkProcessCreationFailed(const FUniqueNetId &InActorId);
const FOnlineError ModSdkProcessCreationFailed(
    const FUniqueNetId &InActorId,
    const FString &InObjectId,
    const TCHAR *InCall,
    const FString &InContextMsg);
const FOnlineError &CriticalError();
const FOnlineError CriticalError(const TCHAR *InCall, const FString &InContextMsg);
const FOnlineError CriticalError(const TCHAR *InCall, const TCHAR *InContextMsg);
const FOnlineError CriticalError(const FUniqueNetId &InActorId, const TCHAR *InCall, const FString &InContextMsg);
const FOnlineError CriticalError(const FUniqueNetId &InActorId);
const FOnlineError CriticalError(
    const FUniqueNetId &InActorId,
    const FString &InObjectId,
    const TCHAR *InCall,
    const FString &InContextMsg);
const FOnlineError &ToolInternalError();
const FOnlineError ToolInternalError(const TCHAR *InCall, const FString &InContextMsg);
const FOnlineError ToolInternalError(const TCHAR *InCall, const TCHAR *InContextMsg);
const FOnlineError ToolInternalError(const FUniqueNetId &InActorId, const TCHAR *InCall, const FString &InContextMsg);
const FOnlineError ToolInternalError(const FUniqueNetId &InActorId);
const FOnlineError ToolInternalError(
    const FUniqueNetId &InActorId,
    const FString &InObjectId,
    const TCHAR *InCall,
    const FString &InContextMsg);
const FOnlineError &IPCFailure();
const FOnlineError IPCFailure(const TCHAR *InCall, const FString &InContextMsg);
const FOnlineError IPCFailure(const TCHAR *InCall, const TCHAR *InContextMsg);
const FOnlineError IPCFailure(const FUniqueNetId &InActorId, const TCHAR *InCall, const FString &InContextMsg);
const FOnlineError IPCFailure(const FUniqueNetId &InActorId);
const FOnlineError IPCFailure(
    const FUniqueNetId &InActorId,
    const FString &InObjectId,
    const TCHAR *InCall,
    const FString &InContextMsg);
const FOnlineError &InvalidIPCResponse();
const FOnlineError InvalidIPCResponse(const TCHAR *InCall, const FString &InContextMsg);
const FOnlineError InvalidIPCResponse(const TCHAR *InCall, const TCHAR *InContextMsg);
const FOnlineError InvalidIPCResponse(const FUniqueNetId &InActorId, const TCHAR *InCall, const FString &InContextMsg);
const FOnlineError InvalidIPCResponse(const FUniqueNetId &InActorId);
const FOnlineError InvalidIPCResponse(
    const FUniqueNetId &InActorId,
    const FString &InObjectId,
    const TCHAR *InCall,
    const FString &InContextMsg);
const FOnlineError &URILaunchFailure();
const FOnlineError URILaunchFailure(const TCHAR *InCall, const FString &InContextMsg);
const FOnlineError URILaunchFailure(const TCHAR *InCall, const TCHAR *InContextMsg);
const FOnlineError URILaunchFailure(const FUniqueNetId &InActorId, const TCHAR *InCall, const FString &InContextMsg);
const FOnlineError URILaunchFailure(const FUniqueNetId &InActorId);
const FOnlineError URILaunchFailure(
    const FUniqueNetId &InActorId,
    const FString &InObjectId,
    const TCHAR *InCall,
    const FString &InContextMsg);
const FOnlineError &ModIsNotInstalled();
const FOnlineError ModIsNotInstalled(const TCHAR *InCall, const FString &InContextMsg);
const FOnlineError ModIsNotInstalled(const TCHAR *InCall, const TCHAR *InContextMsg);
const FOnlineError ModIsNotInstalled(const FUniqueNetId &InActorId, const TCHAR *InCall, const FString &InContextMsg);
const FOnlineError ModIsNotInstalled(const FUniqueNetId &InActorId);
const FOnlineError ModIsNotInstalled(
    const FUniqueNetId &InActorId,
    const FString &InObjectId,
    const TCHAR *InCall,
    const FString &InContextMsg);
const FOnlineError &UserDoesNotOwnTheGame();
const FOnlineError UserDoesNotOwnTheGame(const TCHAR *InCall, const FString &InContextMsg);
const FOnlineError UserDoesNotOwnTheGame(const TCHAR *InCall, const TCHAR *InContextMsg);
const FOnlineError UserDoesNotOwnTheGame(
    const FUniqueNetId &InActorId,
    const TCHAR *InCall,
    const FString &InContextMsg);
const FOnlineError UserDoesNotOwnTheGame(const FUniqueNetId &InActorId);
const FOnlineError UserDoesNotOwnTheGame(
    const FUniqueNetId &InActorId,
    const FString &InObjectId,
    const TCHAR *InCall,
    const FString &InContextMsg);
const FOnlineError &OfferRequestByIdInvalidResult();
const FOnlineError OfferRequestByIdInvalidResult(const TCHAR *InCall, const FString &InContextMsg);
const FOnlineError OfferRequestByIdInvalidResult(const TCHAR *InCall, const TCHAR *InContextMsg);
const FOnlineError OfferRequestByIdInvalidResult(
    const FUniqueNetId &InActorId,
    const TCHAR *InCall,
    const FString &InContextMsg);
const FOnlineError OfferRequestByIdInvalidResult(const FUniqueNetId &InActorId);
const FOnlineError OfferRequestByIdInvalidResult(
    const FUniqueNetId &InActorId,
    const FString &InObjectId,
    const TCHAR *InCall,
    const FString &InContextMsg);
const FOnlineError &CouldNotFindOffer();
const FOnlineError CouldNotFindOffer(const TCHAR *InCall, const FString &InContextMsg);
const FOnlineError CouldNotFindOffer(const TCHAR *InCall, const TCHAR *InContextMsg);
const FOnlineError CouldNotFindOffer(const FUniqueNetId &InActorId, const TCHAR *InCall, const FString &InContextMsg);
const FOnlineError CouldNotFindOffer(const FUniqueNetId &InActorId);
const FOnlineError CouldNotFindOffer(
    const FUniqueNetId &InActorId,
    const FString &InObjectId,
    const TCHAR *InCall,
    const FString &InContextMsg);
const FOnlineError &OfferRequestByIdFailure();
const FOnlineError OfferRequestByIdFailure(const TCHAR *InCall, const FString &InContextMsg);
const FOnlineError OfferRequestByIdFailure(const TCHAR *InCall, const TCHAR *InContextMsg);
const FOnlineError OfferRequestByIdFailure(
    const FUniqueNetId &InActorId,
    const TCHAR *InCall,
    const FString &InContextMsg);
const FOnlineError OfferRequestByIdFailure(const FUniqueNetId &InActorId);
const FOnlineError OfferRequestByIdFailure(
    const FUniqueNetId &InActorId,
    const FString &InObjectId,
    const TCHAR *InCall,
    const FString &InContextMsg);
const FOnlineError &PurchaseFailure();
const FOnlineError PurchaseFailure(const TCHAR *InCall, const FString &InContextMsg);
const FOnlineError PurchaseFailure(const TCHAR *InCall, const TCHAR *InContextMsg);
const FOnlineError PurchaseFailure(const FUniqueNetId &InActorId, const TCHAR *InCall, const FString &InContextMsg);
const FOnlineError PurchaseFailure(const FUniqueNetId &InActorId);
const FOnlineError PurchaseFailure(
    const FUniqueNetId &InActorId,
    const FString &InObjectId,
    const TCHAR *InCall,
    const FString &InContextMsg);
const FOnlineError &InvalidGameInstallInfo();
const FOnlineError InvalidGameInstallInfo(const TCHAR *InCall, const FString &InContextMsg);
const FOnlineError InvalidGameInstallInfo(const TCHAR *InCall, const TCHAR *InContextMsg);
const FOnlineError InvalidGameInstallInfo(
    const FUniqueNetId &InActorId,
    const TCHAR *InCall,
    const FString &InContextMsg);
const FOnlineError InvalidGameInstallInfo(const FUniqueNetId &InActorId);
const FOnlineError InvalidGameInstallInfo(
    const FUniqueNetId &InActorId,
    const FString &InObjectId,
    const TCHAR *InCall,
    const FString &InContextMsg);
const FOnlineError &CannotGetManifestLocation();
const FOnlineError CannotGetManifestLocation(const TCHAR *InCall, const FString &InContextMsg);
const FOnlineError CannotGetManifestLocation(const TCHAR *InCall, const TCHAR *InContextMsg);
const FOnlineError CannotGetManifestLocation(
    const FUniqueNetId &InActorId,
    const TCHAR *InCall,
    const FString &InContextMsg);
const FOnlineError CannotGetManifestLocation(const FUniqueNetId &InActorId);
const FOnlineError CannotGetManifestLocation(
    const FUniqueNetId &InActorId,
    const FString &InObjectId,
    const TCHAR *InCall,
    const FString &InContextMsg);
const FOnlineError &UnsupportedOS();
const FOnlineError UnsupportedOS(const TCHAR *InCall, const FString &InContextMsg);
const FOnlineError UnsupportedOS(const TCHAR *InCall, const TCHAR *InContextMsg);
const FOnlineError UnsupportedOS(const FUniqueNetId &InActorId, const TCHAR *InCall, const FString &InContextMsg);
const FOnlineError UnsupportedOS(const FUniqueNetId &InActorId);
const FOnlineError UnsupportedOS(
    const FUniqueNetId &InActorId,
    const FString &InObjectId,
    const TCHAR *InCall,
    const FString &InContextMsg);
} // namespace Mods
namespace AntiCheat
{
const FOnlineError &ClientProtectionNotAvailable();
const FOnlineError ClientProtectionNotAvailable(const TCHAR *InCall, const FString &InContextMsg);
const FOnlineError ClientProtectionNotAvailable(const TCHAR *InCall, const TCHAR *InContextMsg);
const FOnlineError ClientProtectionNotAvailable(
    const FUniqueNetId &InActorId,
    const TCHAR *InCall,
    const FString &InContextMsg);
const FOnlineError ClientProtectionNotAvailable(const FUniqueNetId &InActorId);
const FOnlineError ClientProtectionNotAvailable(
    const FUniqueNetId &InActorId,
    const FString &InObjectId,
    const TCHAR *InCall,
    const FString &InContextMsg);
const FOnlineError &InvalidMode();
const FOnlineError InvalidMode(const TCHAR *InCall, const FString &InContextMsg);
const FOnlineError InvalidMode(const TCHAR *InCall, const TCHAR *InContextMsg);
const FOnlineError InvalidMode(const FUniqueNetId &InActorId, const TCHAR *InCall, const FString &InContextMsg);
const FOnlineError InvalidMode(const FUniqueNetId &InActorId);
const FOnlineError InvalidMode(
    const FUniqueNetId &InActorId,
    const FString &InObjectId,
    const TCHAR *InCall,
    const FString &InContextMsg);
const FOnlineError &ClientProductIdMismatch();
const FOnlineError ClientProductIdMismatch(const TCHAR *InCall, const FString &InContextMsg);
const FOnlineError ClientProductIdMismatch(const TCHAR *InCall, const TCHAR *InContextMsg);
const FOnlineError ClientProductIdMismatch(
    const FUniqueNetId &InActorId,
    const TCHAR *InCall,
    const FString &InContextMsg);
const FOnlineError ClientProductIdMismatch(const FUniqueNetId &InActorId);
const FOnlineError ClientProductIdMismatch(
    const FUniqueNetId &InActorId,
    const FString &InObjectId,
    const TCHAR *InCall,
    const FString &InContextMsg);
const FOnlineError &ClientSandboxIdMismatch();
const FOnlineError ClientSandboxIdMismatch(const TCHAR *InCall, const FString &InContextMsg);
const FOnlineError ClientSandboxIdMismatch(const TCHAR *InCall, const TCHAR *InContextMsg);
const FOnlineError ClientSandboxIdMismatch(
    const FUniqueNetId &InActorId,
    const TCHAR *InCall,
    const FString &InContextMsg);
const FOnlineError ClientSandboxIdMismatch(const FUniqueNetId &InActorId);
const FOnlineError ClientSandboxIdMismatch(
    const FUniqueNetId &InActorId,
    const FString &InObjectId,
    const TCHAR *InCall,
    const FString &InContextMsg);
const FOnlineError &ProtectMessageSessionKeyRequired();
const FOnlineError ProtectMessageSessionKeyRequired(const TCHAR *InCall, const FString &InContextMsg);
const FOnlineError ProtectMessageSessionKeyRequired(const TCHAR *InCall, const TCHAR *InContextMsg);
const FOnlineError ProtectMessageSessionKeyRequired(
    const FUniqueNetId &InActorId,
    const TCHAR *InCall,
    const FString &InContextMsg);
const FOnlineError ProtectMessageSessionKeyRequired(const FUniqueNetId &InActorId);
const FOnlineError ProtectMessageSessionKeyRequired(
    const FUniqueNetId &InActorId,
    const FString &InObjectId,
    const TCHAR *InCall,
    const FString &InContextMsg);
const FOnlineError &ProtectMessageValidationFailed();
const FOnlineError ProtectMessageValidationFailed(const TCHAR *InCall, const FString &InContextMsg);
const FOnlineError ProtectMessageValidationFailed(const TCHAR *InCall, const TCHAR *InContextMsg);
const FOnlineError ProtectMessageValidationFailed(
    const FUniqueNetId &InActorId,
    const TCHAR *InCall,
    const FString &InContextMsg);
const FOnlineError ProtectMessageValidationFailed(const FUniqueNetId &InActorId);
const FOnlineError ProtectMessageValidationFailed(
    const FUniqueNetId &InActorId,
    const FString &InObjectId,
    const TCHAR *InCall,
    const FString &InContextMsg);
const FOnlineError &ProtectMessageInitializationFailed();
const FOnlineError ProtectMessageInitializationFailed(const TCHAR *InCall, const FString &InContextMsg);
const FOnlineError ProtectMessageInitializationFailed(const TCHAR *InCall, const TCHAR *InContextMsg);
const FOnlineError ProtectMessageInitializationFailed(
    const FUniqueNetId &InActorId,
    const TCHAR *InCall,
    const FString &InContextMsg);
const FOnlineError ProtectMessageInitializationFailed(const FUniqueNetId &InActorId);
const FOnlineError ProtectMessageInitializationFailed(
    const FUniqueNetId &InActorId,
    const FString &InObjectId,
    const TCHAR *InCall,
    const FString &InContextMsg);
const FOnlineError &PeerAlreadyRegistered();
const FOnlineError PeerAlreadyRegistered(const TCHAR *InCall, const FString &InContextMsg);
const FOnlineError PeerAlreadyRegistered(const TCHAR *InCall, const TCHAR *InContextMsg);
const FOnlineError PeerAlreadyRegistered(
    const FUniqueNetId &InActorId,
    const TCHAR *InCall,
    const FString &InContextMsg);
const FOnlineError PeerAlreadyRegistered(const FUniqueNetId &InActorId);
const FOnlineError PeerAlreadyRegistered(
    const FUniqueNetId &InActorId,
    const FString &InObjectId,
    const TCHAR *InCall,
    const FString &InContextMsg);
const FOnlineError &PeerNotFound();
const FOnlineError PeerNotFound(const TCHAR *InCall, const FString &InContextMsg);
const FOnlineError PeerNotFound(const TCHAR *InCall, const TCHAR *InContextMsg);
const FOnlineError PeerNotFound(const FUniqueNetId &InActorId, const TCHAR *InCall, const FString &InContextMsg);
const FOnlineError PeerNotFound(const FUniqueNetId &InActorId);
const FOnlineError PeerNotFound(
    const FUniqueNetId &InActorId,
    const FString &InObjectId,
    const TCHAR *InCall,
    const FString &InContextMsg);
const FOnlineError &PeerNotProtected();
const FOnlineError PeerNotProtected(const TCHAR *InCall, const FString &InContextMsg);
const FOnlineError PeerNotProtected(const TCHAR *InCall, const TCHAR *InContextMsg);
const FOnlineError PeerNotProtected(const FUniqueNetId &InActorId, const TCHAR *InCall, const FString &InContextMsg);
const FOnlineError PeerNotProtected(const FUniqueNetId &InActorId);
const FOnlineError PeerNotProtected(
    const FUniqueNetId &InActorId,
    const FString &InObjectId,
    const TCHAR *InCall,
    const FString &InContextMsg);
const FOnlineError &ClientDeploymentIdMismatch();
const FOnlineError ClientDeploymentIdMismatch(const TCHAR *InCall, const FString &InContextMsg);
const FOnlineError ClientDeploymentIdMismatch(const TCHAR *InCall, const TCHAR *InContextMsg);
const FOnlineError ClientDeploymentIdMismatch(
    const FUniqueNetId &InActorId,
    const TCHAR *InCall,
    const FString &InContextMsg);
const FOnlineError ClientDeploymentIdMismatch(const FUniqueNetId &InActorId);
const FOnlineError ClientDeploymentIdMismatch(
    const FUniqueNetId &InActorId,
    const FString &InObjectId,
    const TCHAR *InCall,
    const FString &InContextMsg);
const FOnlineError &DeviceIdAuthIsNotSupported();
const FOnlineError DeviceIdAuthIsNotSupported(const TCHAR *InCall, const FString &InContextMsg);
const FOnlineError DeviceIdAuthIsNotSupported(const TCHAR *InCall, const TCHAR *InContextMsg);
const FOnlineError DeviceIdAuthIsNotSupported(
    const FUniqueNetId &InActorId,
    const TCHAR *InCall,
    const FString &InContextMsg);
const FOnlineError DeviceIdAuthIsNotSupported(const FUniqueNetId &InActorId);
const FOnlineError DeviceIdAuthIsNotSupported(
    const FUniqueNetId &InActorId,
    const FString &InObjectId,
    const TCHAR *InCall,
    const FString &InContextMsg);
} // namespace AntiCheat
namespace RTC
{
const FOnlineError &TooManyParticipants();
const FOnlineError TooManyParticipants(const TCHAR *InCall, const FString &InContextMsg);
const FOnlineError TooManyParticipants(const TCHAR *InCall, const TCHAR *InContextMsg);
const FOnlineError TooManyParticipants(const FUniqueNetId &InActorId, const TCHAR *InCall, const FString &InContextMsg);
const FOnlineError TooManyParticipants(const FUniqueNetId &InActorId);
const FOnlineError TooManyParticipants(
    const FUniqueNetId &InActorId,
    const FString &InObjectId,
    const TCHAR *InCall,
    const FString &InContextMsg);
const FOnlineError &RoomAlreadyExists();
const FOnlineError RoomAlreadyExists(const TCHAR *InCall, const FString &InContextMsg);
const FOnlineError RoomAlreadyExists(const TCHAR *InCall, const TCHAR *InContextMsg);
const FOnlineError RoomAlreadyExists(const FUniqueNetId &InActorId, const TCHAR *InCall, const FString &InContextMsg);
const FOnlineError RoomAlreadyExists(const FUniqueNetId &InActorId);
const FOnlineError RoomAlreadyExists(
    const FUniqueNetId &InActorId,
    const FString &InObjectId,
    const TCHAR *InCall,
    const FString &InContextMsg);
const FOnlineError &UserKicked();
const FOnlineError UserKicked(const TCHAR *InCall, const FString &InContextMsg);
const FOnlineError UserKicked(const TCHAR *InCall, const TCHAR *InContextMsg);
const FOnlineError UserKicked(const FUniqueNetId &InActorId, const TCHAR *InCall, const FString &InContextMsg);
const FOnlineError UserKicked(const FUniqueNetId &InActorId);
const FOnlineError UserKicked(
    const FUniqueNetId &InActorId,
    const FString &InObjectId,
    const TCHAR *InCall,
    const FString &InContextMsg);
const FOnlineError &UserBanned();
const FOnlineError UserBanned(const TCHAR *InCall, const FString &InContextMsg);
const FOnlineError UserBanned(const TCHAR *InCall, const TCHAR *InContextMsg);
const FOnlineError UserBanned(const FUniqueNetId &InActorId, const TCHAR *InCall, const FString &InContextMsg);
const FOnlineError UserBanned(const FUniqueNetId &InActorId);
const FOnlineError UserBanned(
    const FUniqueNetId &InActorId,
    const FString &InObjectId,
    const TCHAR *InCall,
    const FString &InContextMsg);
const FOnlineError &RoomWasLeft();
const FOnlineError RoomWasLeft(const TCHAR *InCall, const FString &InContextMsg);
const FOnlineError RoomWasLeft(const TCHAR *InCall, const TCHAR *InContextMsg);
const FOnlineError RoomWasLeft(const FUniqueNetId &InActorId, const TCHAR *InCall, const FString &InContextMsg);
const FOnlineError RoomWasLeft(const FUniqueNetId &InActorId);
const FOnlineError RoomWasLeft(
    const FUniqueNetId &InActorId,
    const FString &InObjectId,
    const TCHAR *InCall,
    const FString &InContextMsg);
const FOnlineError &ReconnectionTimegateExpired();
const FOnlineError ReconnectionTimegateExpired(const TCHAR *InCall, const FString &InContextMsg);
const FOnlineError ReconnectionTimegateExpired(const TCHAR *InCall, const TCHAR *InContextMsg);
const FOnlineError ReconnectionTimegateExpired(
    const FUniqueNetId &InActorId,
    const TCHAR *InCall,
    const FString &InContextMsg);
const FOnlineError ReconnectionTimegateExpired(const FUniqueNetId &InActorId);
const FOnlineError ReconnectionTimegateExpired(
    const FUniqueNetId &InActorId,
    const FString &InObjectId,
    const TCHAR *InCall,
    const FString &InContextMsg);
} // namespace RTC
namespace ProgressionSnapshot
{
const FOnlineError &SnapshotIdUnavailable();
const FOnlineError SnapshotIdUnavailable(const TCHAR *InCall, const FString &InContextMsg);
const FOnlineError SnapshotIdUnavailable(const TCHAR *InCall, const TCHAR *InContextMsg);
const FOnlineError SnapshotIdUnavailable(
    const FUniqueNetId &InActorId,
    const TCHAR *InCall,
    const FString &InContextMsg);
const FOnlineError SnapshotIdUnavailable(const FUniqueNetId &InActorId);
const FOnlineError SnapshotIdUnavailable(
    const FUniqueNetId &InActorId,
    const FString &InObjectId,
    const TCHAR *InCall,
    const FString &InContextMsg);
} // namespace ProgressionSnapshot
namespace KWS
{
const FOnlineError &ParentEmailMissing();
const FOnlineError ParentEmailMissing(const TCHAR *InCall, const FString &InContextMsg);
const FOnlineError ParentEmailMissing(const TCHAR *InCall, const TCHAR *InContextMsg);
const FOnlineError ParentEmailMissing(const FUniqueNetId &InActorId, const TCHAR *InCall, const FString &InContextMsg);
const FOnlineError ParentEmailMissing(const FUniqueNetId &InActorId);
const FOnlineError ParentEmailMissing(
    const FUniqueNetId &InActorId,
    const FString &InObjectId,
    const TCHAR *InCall,
    const FString &InContextMsg);
const FOnlineError &UserGraduated();
const FOnlineError UserGraduated(const TCHAR *InCall, const FString &InContextMsg);
const FOnlineError UserGraduated(const TCHAR *InCall, const TCHAR *InContextMsg);
const FOnlineError UserGraduated(const FUniqueNetId &InActorId, const TCHAR *InCall, const FString &InContextMsg);
const FOnlineError UserGraduated(const FUniqueNetId &InActorId);
const FOnlineError UserGraduated(
    const FUniqueNetId &InActorId,
    const FString &InObjectId,
    const TCHAR *InCall,
    const FString &InContextMsg);
} // namespace KWS
namespace Android
{
const FOnlineError &JavaVMNotStored();
const FOnlineError JavaVMNotStored(const TCHAR *InCall, const FString &InContextMsg);
const FOnlineError JavaVMNotStored(const TCHAR *InCall, const TCHAR *InContextMsg);
const FOnlineError JavaVMNotStored(const FUniqueNetId &InActorId, const TCHAR *InCall, const FString &InContextMsg);
const FOnlineError JavaVMNotStored(const FUniqueNetId &InActorId);
const FOnlineError JavaVMNotStored(
    const FUniqueNetId &InActorId,
    const FString &InObjectId,
    const TCHAR *InCall,
    const FString &InContextMsg);
} // namespace Android
} // namespace Errors
} // namespace OnlineRedpointEOS
