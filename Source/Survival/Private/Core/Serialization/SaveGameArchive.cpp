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
	}
	else
	{
		FString SavedClass(Object->GetClass()->GetPathName());
		InnerArchive << SavedClass;
	}

	Object->Serialize(*this);
	return *this;
}
