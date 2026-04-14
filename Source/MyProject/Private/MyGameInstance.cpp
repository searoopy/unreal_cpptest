// Fill out your copyright notice in the Description page of Project Settings.


#include "MyGameInstance.h"

#include "Student.h"
#include "Teacher.h"
#include "Staff.h"
#include "Person.h"

#include "CourseInfo.h"
#include "Algo/Accumulate.h"



UMyGameInstance::UMyGameInstance()
{
	SchoolName = TEXT("기본 학교");
}

void UMyGameInstance::Init()
{
	Super::Init();
	UE_LOG(LogTemp, Log, TEXT("====================="));
	


	const int32 ArrayNum = 10;
	TArray<int32> Int32Array;


	for (int32 ix = 1; ix < ArrayNum; ix++)
	{
		Int32Array.Add(ix);
	}


	//짝수 제거.
	Int32Array.RemoveAll(
		//[]- 캡처 (외부내용을 람다안에서 사용할때 활용).
		//() - 파라메터
		//-> 반환형.
		//{} 본문.
		[](int32 Val) -> bool
		{
			return Val % 2 == 0;
		}
	);


	//짝수 삽입.
	Int32Array += {2, 4, 6, 8, 10};



	//비교(동등 비교).
	TArray<int32> Int32ArrayCompare;
	int32 CArray[] = { 1, 3, 5, 7, 9, 2, 4, 6, 8, 10 };
	Int32ArrayCompare.AddUninitialized(ArrayNum); //비교 실패를 위해 추가.


	//c스타일배열을 TArray에 메모리 복사.
	FMemory::Memcpy(Int32ArrayCompare.GetData(), CArray , sizeof(int32) * ArrayNum);


	// 어서트 (크래시를 발생시키지 않고, 출력 로그 창에 오류 메시지 출력).
	ensureAlways(Int32Array == Int32ArrayCompare);



	//합계
	int32 Sum = 0;
	for(const int32& Val : Int32Array)
	{
		Sum += Val;
	}
	

	//알고리즘 활용(합계 구하기).
	int32 SumByAlgo = Algo::Accumulate(Int32Array, 0);

	UE_LOG(LogTemp, Log, TEXT("sum= %d | SumByAlgo: %d "), Sum, SumByAlgo);



	//tset 사용.
	TSet<int32> Int32Set;
	for( int32 ix = 1; ix < ArrayNum; ix++)
	{
		Int32Set.Add(ix);
	}

	//제거.
	Int32Set.Remove(2);
	Int32Set.Remove(4);
	Int32Set.Remove(6);
	Int32Set.Remove(8);
	Int32Set.Remove(10);


	//추가.
	Int32Set.Add(2);
	Int32Set.Add(4);
	Int32Set.Add(6);
	Int32Set.Add(8);
	Int32Set.Add(10);

	

}
 