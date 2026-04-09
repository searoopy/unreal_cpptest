// Fill out your copyright notice in the Description page of Project Settings.


#include "Student.h"

UStudent::UStudent()
{

	Year = 3;
	Id = 1;
}

void UStudent::DoLesson()
{
	Super::DoLesson();

	UE_LOG(LogTemp, Log, TEXT("학생이 수업을 듣습니다."));
}
