// Fill out your copyright notice in the Description page of Project Settings.


#include "MyGameInstance.h"

#include "Student.h"
#include "Teacher.h"


UMyGameInstance::UMyGameInstance()
{
	SchoolName = TEXT("기본 학교");
}

void UMyGameInstance::Init()
{
	Super::Init();

	//로그 출력
	//UE_LOG(LogTemp, Log, TEXT("%s"),TEXT("abccc") );



	UClass* ClassRunTime = GetClass();

	UClass* ClassCompile = UMyGameInstance::StaticClass();

	//check(ClassRunTime != ClassCompile); //클래시까지.
	//ensure(ClassCompile != ClassRunTime); // 출력로그까지만


	//클래스 이름 출력.
	UE_LOG(
		LogTemp,
		Log,
		TEXT("학교를 담당하는 클래스 : %s %s"),
		*ClassRunTime->GetName(),
		*ClassCompile->GetName()

	);

	SchoolName = TEXT("청강문화산업대학");

	UE_LOG(
		LogTemp,
		Log,
		TEXT("학교 이름 : %s"),
		*SchoolName
	);

	UE_LOG(
		LogTemp,
		Log,
		TEXT("학교 이름 : %s"),
		*GetClass()->GetDefaultObject<UMyGameInstance>()->SchoolName
	);




	UStudent* Student = NewObject<UStudent>();
	UTeacher* Teacher = NewObject<UTeacher>();


	Student->SetName(TEXT("홍 길 동"));
	UE_LOG(LogTemp, Log, TEXT("학생 이름 : %s"), *Student->GetName());



	FProperty* NameProp=
		Teacher->GetClass()->FindPropertyByName(TEXT("Name"));	
	if (NameProp)
	{
		//리플렉션을 활용해 현재 프로퍼티에 저장된 값 가져오기.
		FString CurrentTeacherName;
		NameProp->GetValue_InContainer(Teacher, &CurrentTeacherName);	

		UE_LOG(LogTemp, Log, TEXT("현재 선생님 이름 : %s"), *CurrentTeacherName);
	}


	//리플렉션을 활용해 프로퍼티에 새로운 값 저장.
	FString newteacherName = TEXT("김 선 생");
	NameProp->SetValue_InContainer(Teacher, &newteacherName);
	UE_LOG(LogTemp, Log, TEXT("새로운 선생님 이름 : %s"), *(Teacher->GetName()) );




	//함수 호출(리플렉션 활용)
	UFunction* DoLessonFunc = Teacher->GetClass()->FindFunctionByName(TEXT("DoLesson"));

	if(DoLessonFunc)
	{
		Teacher->ProcessEvent(DoLessonFunc, nullptr);
	}


}
 