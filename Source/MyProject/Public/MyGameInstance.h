// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/GameInstance.h"

//#include "CourseInfo.h"
#include "MyGameInstance.generated.h"

class UCourseInfo;
/**
 * 
 */
UCLASS()
class MYPROJECT_API UMyGameInstance : public UGameInstance
{
	GENERATED_BODY()
public:
	UMyGameInstance();


private:
	virtual void Init() override;
	
private:
	UPROPERTY()
	FString SchoolName;

	//학사 정보 객체.
	UPROPERTY()
	TObjectPtr<class UCourseInfo> CourseInfo; 
};
