// Copyright Gradess. All Rights Reserved.


#include "Core/Serialization/SaveGameArchive.h"

FArchive& FSaveGameArchive::operator<<(UObject*& Object)
{
	if (IsLoading())
	{
		FString LoadedString;
		InnerArchive << LoadedString;

		const auto Class = FindObject<UClass>(nullptr, *LoadedString, false);
		if (!Class) { return *this; }
		
		Object = NewObject<UObject>(Class, Class);

		for (TFieldIterator<FProperty> It(Object->GetClass()); It; ++It)
		{
			FProperty* Property = *It;

			if (!(Property->PropertyFlags & CPF_SaveGame)) { continue; }

			auto Destination = TArray<uint8>();
			Destination.SetNum(Property->ElementSize);
			InnerArchive << Destination;

			const auto ValuePtr = Property->ContainerPtrToValuePtr<void>(Object);
			Property->CopySingleValue(ValuePtr, Destination.GetData());
		}

		if(!Object && bLoadIfFindFails)
		{
			Object = LoadObject<UObject>(nullptr, *LoadedString);
		}
	}
	else
	{
		FString SavedClass(Object->GetClass()->GetPathName());
		InnerArchive << SavedClass;
		for (TFieldIterator<FProperty> It(Object->GetClass()); It; ++It)
		{
			FProperty* Property = *It;
			if (!(Property->PropertyFlags & CPF_SaveGame)) { continue; }
			
			auto Destination = TArray<uint8>();
			Destination.SetNum(Property->ElementSize);

			const auto ValuePtr = Property->ContainerPtrToValuePtr<void>(Object);
			Property->CopySingleValue(Destination.GetData(), ValuePtr);
			
			InnerArchive << Destination;
		}
	}
	return *this;
}
