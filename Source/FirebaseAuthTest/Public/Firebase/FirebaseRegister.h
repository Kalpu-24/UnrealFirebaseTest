// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Interfaces/IHttpRequest.h"
#include "Kismet/BlueprintAsyncActionBase.h"
#include "FirebaseRegister.generated.h"

/**
 * 
 */

DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FFirebaseRegisterResultDelegate, const FString&, ResponseData);
DECLARE_DYNAMIC_MULTICAST_DELEGATE(FFirebaseRegisterErrorDelegate);

UCLASS()
class FIREBASEAUTHTEST_API UFirebaseRegister : public UBlueprintAsyncActionBase
{
	GENERATED_BODY()
	
public:
	UPROPERTY(BlueprintAssignable)
	FFirebaseRegisterResultDelegate Success;

	UPROPERTY(BlueprintAssignable)
	FFirebaseRegisterErrorDelegate Error;

	UFUNCTION(BlueprintCallable, meta = (BlueprintInternalUseOnly = "true", WorldContext = "self"), Category = "Firebase Functions")
	static UFirebaseRegister* Register(UObject* WorldContextObject, FString Email, FString Password);

private:
	UPROPERTY()
	UObject* WorldContextObject;

	FString Email;

	FString Password;

	virtual void Activate() override;

	void AuthLogin(FHttpRequestPtr Request, FHttpResponsePtr Response, bool bWasSuccessful);
};
