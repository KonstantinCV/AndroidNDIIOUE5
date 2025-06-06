/*
	Copyright (C) 2024 Vizrt NDI AB. All rights reserved.

	This file and its use within a Product is bound by the terms of NDI SDK license that was provided
	as part of the NDI SDK. For more information, please review the license and the NDI SDK documentation.
*/

#include <Factories/NDIMediaReceiverFactory.h>

#include <AssetTypeCategories.h>
#include <Objects/Media/NDIMediaReceiver.h>

#define LOCTEXT_NAMESPACE "NDIIOEditorMediaReceiverFactory"

UNDIMediaReceiverFactory::UNDIMediaReceiverFactory(const FObjectInitializer& ObjectInitializer)
	: Super(ObjectInitializer) {

	this->bCreateNew = true;
	this->bEditAfterNew = true;

	this->SupportedClass = UNDIMediaReceiver::StaticClass();
}

FText UNDIMediaReceiverFactory::GetDisplayName() const { return LOCTEXT("NDIMediaReceiverFactoryDisplayName", "NDI Media Receiver"); }

uint32 UNDIMediaReceiverFactory::GetMenuCategories() const 
{
	return EAssetTypeCategories::Media; 
}

UObject* UNDIMediaReceiverFactory::FactoryCreateNew(UClass* InClass, UObject* InParent, FName InName, EObjectFlags Flags, UObject* Context, FFeedbackContext* Warn)
{
	return NewObject<UNDIMediaReceiver>(InParent, InClass, InName, Flags | RF_Transactional);
}

#undef LOCTEXT_NAMESPACE