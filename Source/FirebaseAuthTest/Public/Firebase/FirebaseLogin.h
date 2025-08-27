// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Interfaces/IHttpRequest.h"
#include "Kismet/BlueprintAsyncActionBase.h"
#include "FirebaseLogin.generated.h"

/**
 * 
 */

DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FFirebaseLoginResultDelegate, const FString&, ResponseData);
DECLARE_DYNAMIC_MULTICAST_DELEGATE(FFirebaseLoginErrorDelegate);

UCLASS()
class FIREBASEAUTHTEST_API UFirebaseLogin : public UBlueprintAsyncActionBase
{
	GENERATED_BODY()
	
public:
	UPROPERTY(BlueprintAssignable)
	FFirebaseLoginResultDelegate Success;

	UPROPERTY(BlueprintAssignable)
	FFirebaseLoginErrorDelegate Error;

	UFUNCTION(BlueprintCallable, meta = (BlueprintInternalUseOnly = "true", WorldContext = "self"), Category = "Firebase Functions")
	static UFirebaseLogin* Login(UObject* WorldContextObject, FString Email, FString Password);

private:
	UPROPERTY()
	UObject* WorldContextObject;

	FString Email;

	FString Password;

	virtual void Activate() override;

	void AuthLogin(FHttpRequestPtr Request, FHttpResponsePtr Response, bool bWasSuccessful);
};
