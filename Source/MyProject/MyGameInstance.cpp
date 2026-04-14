// Fill out your copyright notice in the Description page of Project Settings.


#include "MyGameInstance.h"


FString MakeRandomName()
{
	//3글자
	TCHAR FirstChar[] = TEXT("김이박최");

	TCHAR MiddleChar[] = TEXT("상혜지성");

	TCHAR LastChar[] = TEXT("수은원연");

	//동적 배열을 사용할때 가능하다면 재할당을 방지하는게 좋음.
	TArray<TCHAR> RandArray;
	RandArray.SetNum(3);
	RandArray[0] = FirstChar[FMath::RandRange(0, 3)];
	RandArray[1] = MiddleChar[FMath::RandRange(0, 3)];
	RandArray[2] = LastChar[FMath::RandRange(0, 3)];


	//문자열로 변환이 가능하도록 반환.
	return FString(RandArray.GetData());
}

void UMyGameInstance::Init()
{
	Super::Init();

	//학생 이름 데이터 생성.
	const int32 StudentNum = 300;
	for( int i = 0; i < StudentNum; i++)
	{
		StudentDataArray.Emplace(
			FStudentData(MakeRandomName(), i)
		);
	}

	UE_LOG(
		LogTemp,
		Log,
		TEXT("모든 학생 데이터의 수:%d"),
		StudentDataArray.Num()
	);



	//학생 데이터에서 이름 값만 추출해서 배열에 저장.
	TArray<FString> AllStudentNames;

	//알고리즘을 활용해서 이름값 추출,.
	Algo::Transform(
		StudentDataArray,
		AllStudentNames,
		[](const FStudentData& Value)-> FString
		{
			return (Value.Name);
		}
	);


	UE_LOG(
		LogTemp,
		Log,
		TEXT("모든 학생 이름의 수:%d"),
		AllStudentNames.Num()
	);


	//학생 데이터를 TSet으로 변환.
	TSet<FString> AllUniqueNames;

	Algo::Transform(
		StudentDataArray,
		AllUniqueNames,
		[](const FStudentData& Val)
		{
			return Val.Name;
		}
	);

	UE_LOG(
		LogTemp,
		Log,
		TEXT("중복없는 학생이름의수 :%d"),
		AllUniqueNames.Num()
	);


	//학생 데이터를 tmap으로 변환
	Algo::Transform(
		StudentDataArray,
		StudentsDataMap,
		[](const FStudentData& val)
		{
			return TPair<int32, FString>(
				val.Order, val.Name
				);
		}
	);

	UE_LOG(
		LogTemp,
		Log,
		TEXT("순번에 따른 학생 맵의 데이터수  :%d"),
		StudentsDataMap.Num()
	);

	//이름 값을 키로 하는맵
	TMap<FString, int32> NameToOrderMap;
	
	//학생 데이터를 map으로 변환
	Algo::Transform(
		StudentDataArray,
		NameToOrderMap,
		[](const FStudentData& val)
		{
			return TPair<FString, int32>(
				val.Name, val.Order
				);
		}
	);


	UE_LOG(
		LogTemp,
		Log,
		TEXT("이름에 따른 학생 맵의 데이터수  :%d"),
		NameToOrderMap.Num()
	);




	//이름을 중복으로 하려는경우
	TMultiMap<FString, int32> NameToOrderMultiMap;
	Algo::Transform(
		StudentDataArray,
		NameToOrderMultiMap,
		[](const FStudentData& val) 
		{
			return TPair<FString, int32>(
				val.Name, val.Order
			);
		}
	);




	UE_LOG(
		LogTemp,
		Log,
		TEXT("이름에 따른 학생 멀티맵의 데이터수  :%d"),
		NameToOrderMultiMap.Num()
	);



	//검색.
	const FString TargetName(TEXT("이혜은"));
	TArray<int32> TargetOrders;
	NameToOrderMultiMap.MultiFind(TargetName, TargetOrders);
	UE_LOG(
		LogTemp,
		Log,
		TEXT("이름 '%s'에 해당하는 학생 순번의 수: %d"),
		*TargetName,
		TargetOrders.Num()
	);


	//TSET에 구조체 넣어보기.
	TSet<FStudentData> StudentsSet;
	for (int i = 0; i < StudentNum; i++)
	{
		StudentsSet.Emplace(FStudentData(MakeRandomName(), i));
	}

	UE_LOG(
		LogTemp,
		Log,
		TEXT("이름 set수 : % d"),
		
		StudentsSet.Num()
	);
}