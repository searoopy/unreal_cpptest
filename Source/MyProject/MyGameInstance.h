// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/GameInstance.h"
#include "Algo/Transform.h"
#include "StudentData.h"
#include "MyGameInstance.generated.h"

/**
 * 
 */
UCLASS()
class MYPROJECT_API UMyGameInstance : public UGameInstance
{
	GENERATED_BODY()

public:
	virtual void Init() override;
	
private:
	//구조체의 경우 , 스택 메모리(항상은 아님)에서 관리.
	TArray<FStudentData> StudentDataArray;


	//UObject의 경우 힙에 배치 및 관리됨.
	//TArray에서 uobject타입을 사용할때는 uproperty 필수.
	UPROPERTY()
	TArray<TObjectPtr<class UStudent>> Students;


	TMap<int32, FString> StudentsDataMap;
};
