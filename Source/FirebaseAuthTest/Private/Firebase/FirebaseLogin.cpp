// Fill out your copyright notice in the Description page of Project Settings.


#include "Firebase/FirebaseLogin.h"

#include "HttpModule.h"
#include "FirebaseAuthTest/FirebaseAuthTest.h"
#include "Interfaces/IHttpResponse.h"

const FString FIREBASE_LOGIN_URL = TEXT("https://identitytoolkit.googleapis.com/v1/accounts:signInWithPassword?key=");

UFirebaseLogin* UFirebaseLogin::Login(UObject* WorldContextObject, FString Email, FString Password)
{
	UFirebaseLogin* NewAction = NewObject<UFirebaseLogin>();
	NewAction->WorldContextObject = WorldContextObject;
	NewAction->Email = Email;
	NewAction->Password = Password;
	return NewAction;
}

void UFirebaseLogin::Activate()
{
	TSharedRef<IHttpRequest, ESPMode::ThreadSafe> HttpRequest = FHttpModule::Get().CreateRequest();
	
	HttpRequest->SetURL(FIREBASE_LOGIN_URL + FireBaseAPIKey);
	HttpRequest->SetVerb(TEXT("POST"));
	HttpRequest->SetHeader(TEXT("Content-Type"), TEXT("application/json"));
	
	TSharedPtr<FJsonObject> JsonObject = MakeShareable(new FJsonObject());
	JsonObject->SetStringField(TEXT("email"), Email);
	JsonObject->SetStringField(TEXT("password"), Password);
	JsonObject->SetBoolField(TEXT("returnSecureToken"), true);
	
	FString RequestBody;
	TSharedRef<TJsonWriter<>> Writer = TJsonWriterFactory<>::Create(&RequestBody);
	FJsonSerializer::Serialize(JsonObject.ToSharedRef(), Writer);
	
	HttpRequest->SetContentAsString(RequestBody);

	HttpRequest->OnProcessRequestComplete().BindUObject(this, &UFirebaseLogin::AuthLogin);

	HttpRequest->ProcessRequest();
}

void UFirebaseLogin::AuthLogin(FHttpRequestPtr Request, FHttpResponsePtr Response, bool bWasSuccessful)
{
	if (bWasSuccessful && Response.IsValid() && EHttpResponseCodes::IsOk(Response->GetResponseCode()))
	{
		Success.Broadcast(Response->GetContentAsString());
	}
	else
	{
		Error.Broadcast();
	}
	
	SetReadyToDestroy();
}
