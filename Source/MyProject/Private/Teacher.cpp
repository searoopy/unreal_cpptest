// Fill out your copyright notice in the Description page of Project Settings.


#include "Teacher.h"

UTeacher::UTeacher()
{
	Year = 5;
	Id = 3;
}

void UTeacher::DoLesson()
{
	Super::DoLesson();

	UE_LOG(LogTemp, Log, TEXT("선생님이 수업을 강의함."));
}
