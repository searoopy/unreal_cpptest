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

	
	TArray<UPerson*> People =
	{
		NewObject<UStudent>(),
		NewObject<UTeacher>(),
		NewObject<UStaff>()
	};


	for (const UPerson* Person : People)
	{
		UE_LOG(LogTemp, Log, TEXT("이름 : %s"), *Person->GetName());

	}

	UE_LOG(LogTemp, Log, TEXT("====================="));

		
	for ( UPerson* Person : People)
	{
		ILessonInterface* LessonInterface = Cast<ILessonInterface>(Person);
		if(LessonInterface )
		{
			UE_LOG(LogTemp, Log, TEXT("%s님은 수업에 참여할수있습니다"), *Person->GetName() );
			LessonInterface->DoLesson();
		}
		else
		{
			UE_LOG(LogTemp, Log, TEXT("%s님은 수업에 참여할없습니다"), *Person->GetName());
		}
	}


}
 