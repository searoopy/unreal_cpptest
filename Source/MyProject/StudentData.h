#pragma once

#include "CoreMinimal.h"
#include "StudentData.generated.h"

USTRUCT( /* BlueprintType, Atomic */)
struct FStudentData
{
	GENERATED_BODY()


	FStudentData()
	{
		Name = TEXT("기본 이름");
		Order = -1;

	}

	FStudentData(const FString& InName, int32 InOrder)
		: Name(InName)
		, Order(InOrder)
	{

	}


	//tset에 사용하기 위한 함수 오버로딩.
	bool operator==(const FStudentData& Other) const
	{
		return Name == Other.Name && Order == Other.Order;
		//return Name == Other.Name;
	}

	friend FORCEINLINE uint32 GetTypeHash(const FStudentData& InStudentData) 
	{
		return GetTypeHash(InStudentData.Order);
	}

	UPROPERTY()
	FString Name;

	UPROPERTY()
	int32 Order;

};