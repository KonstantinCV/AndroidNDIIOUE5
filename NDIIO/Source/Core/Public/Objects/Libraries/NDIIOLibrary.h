/*
	Copyright (C) 2024 Vizrt NDI AB. All rights reserved.

	This file and its use within a Product is bound by the terms of NDI SDK license that was provided
	as part of the NDI SDK. For more information, please review the license and the NDI SDK documentation.
*/

#pragma once

#include <CoreMinimal.h>
#include <Kismet/BlueprintFunctionLibrary.h>

#include <Structures/NDIConnectionInformation.h>
#include <Objects/Media/NDIMediaReceiver.h>
#include <Objects/Media/NDIMediaSender.h>

#include "NDIIOLibrary.generated.h"


/**
	An metadata element as returned by K2_ParseNDIMetaData()
	Blueprints do not support recursive datastructures, so parsing metadata
	with this will result in only the top-level elements being returned.
*/
USTRUCT(BlueprintType)
struct FNDIMetaDataElement
{
	GENERATED_USTRUCT_BODY()

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Metadata")
	FString ElementName;
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Metadata")
	TMap<FString,FString> Attributes;
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Metadata")
	FString Data;
};


UCLASS(META = (DisplayName = "NDI IO Library"))
class NDIIO_API UNDIIOLibrary : public UBlueprintFunctionLibrary
{
	GENERATED_BODY()

private:
	/**
		Retrieves a collection of NDI sources appearing on the network

		@return A collection of NDI Sources appearing on the network
	*/
	UFUNCTION(BlueprintCallable, BlueprintPure, Category = "NDI IO",
			  META = (DisplayName = "Get NDI Source Collection", AllowPrivateAccess = true))
	static const TArray<FNDIConnectionInformation> K2_GetNDISourceCollection();

	/**
		Attempts to search the NDI Source Collection for the source name, returning a result indicating
		success with the ConnectionInformation parameter filled with the found connection

		@param ConnectionInformation The connection information for a successful find with the supplied InSourceName
		@param InSourceName The name of the source to find within the collection of NDI sources

		@return The result of whether the search was successful
	*/
	UFUNCTION(BlueprintCallable, Category = "NDI IO",
			  META = (DisplayName = "Find Network Source by Name", DefaultToSelf = "WorldContextObject",
					  HidePin = "WorldContextObject", AllowPrivateAccess = true))
	static const bool K2_FindNetworkSourceByName(UObject* WorldContextObject,
												 FNDIConnectionInformation& ConnectionInformation,
												 FString InSourceName = FString(""));

private:
	/**
		Attempts to start broadcasting the active viewport. The output of the active viewport is the current camera
		that is actively being viewed (through), and does not have to be an NDI Broadcast Viewport Component.

		@return The result of whether broadcasting the active viewport was started
	*/
	UFUNCTION(BlueprintCallable, Category = "NDI IO",
			  META = (DisplayName = "Begin Broadcasting Active Viewport", DefaultToSelf = "WorldContextObject",
					  HidePin = "WorldContextObject", AllowPrivateAccess = true))
	static bool K2_BeginBroadcastingActiveViewport(UObject* WorldContextObject);

	/**
		Will stop broadcasting the active viewport, which was started by a previous call to 'Begin Broadcasting Active
	   Viewport'
	*/
	UFUNCTION(BlueprintCallable, Category = "NDI IO",
			  META = (DisplayName = "Stop Broadcasting Active Viewport", DefaultToSelf = "WorldContextObject",
					  HidePin = "WorldContextObject", AllowPrivateAccess = true))
	static void K2_StopBroadcastingActiveViewport(UObject* WorldContextObject);

private:
	/**
		Returns an NDI Media Receiver object

		@param Receiver The Receiver object to return
		@return The selected Receiver object
	*/
	UFUNCTION(BlueprintCallable, Category = "NDI IO",
			  META = (DisplayName = "Get NDI Media Receiver", AllowPrivateAccess = true))
	static UPARAM(ref) UNDIMediaReceiver* K2_GetNDIMediaReceiver(UNDIMediaReceiver* Receiver = nullptr);

	/**
		Returns an NDI Media Sender object

		@param Sender The Sender object to return
		@return The selected Sender object
	*/
	UFUNCTION(BlueprintCallable, Category = "NDI IO",
			  META = (DisplayName = "Get NDI Media Sender", AllowPrivateAccess = true))
	static UPARAM(ref) UNDIMediaSender* K2_GetNDIMediaSender(UNDIMediaSender* Sender = nullptr);

private:
	/**
		Parses a string as metadata
		Blueprints do not support recursive datastructures, so parsing metadata
		with this will result in only the top-level elements being returned.
	*/
	UFUNCTION(BlueprintCallable, Category = "NDI IO",
			  META = (DisplayName = "Parse NDI MetaData", AllowPrivateAccess = true))
	static const TArray<FNDIMetaDataElement> K2_ParseNDIMetaData(FString Data);
};
