// Fill out your copyright notice in the Description page of Project Settings.


#include "MyGameInstance.h"

#include "Student.h"
#include "Teacher.h"
#include "Staff.h"
#include "Person.h"


UMyGameInstance::UMyGameInstance()
{
	SchoolName = TEXT("기본 학교");
}

void UMyGameInstance::Init()
{
	Super::Init();
	UE_LOG(LogTemp, Log, TEXT("====================="));
	

	//학사 정보 객체 생성
	CourseInfo = NewObject<UCourseInfo>(this);


	//3명의 학생 추가.
	UStudent* Student1 = NewObject<UStudent>(this);
	Student1->SetName(TEXT("학생1"));
	UStudent* Student2 = NewObject<UStudent>(this);
	Student2->SetName(TEXT("학생2"));				
	UStudent* Student3 = NewObject<UStudent>(this);	
	Student3->SetName(TEXT("학생3"));

	//알림에 구독.
	CourseInfo->OnChanged.AddUObject(Student1, &UStudent::GetNotification);
	CourseInfo->OnChanged.AddUObject(Student2, &UStudent::GetNotification);
	CourseInfo->OnChanged.AddUObject(Student3, &UStudent::GetNotification);



	//변경된 학사 정보 발행.
	CourseInfo->ChangeCourseInfo(SchoolName, TEXT("학사 정보가 변경되었습니다."));

	UE_LOG(LogTemp, Log, TEXT("====================="));

}
 