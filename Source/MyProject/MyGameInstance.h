// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/GameInstance.h"
#include "Engine/StreamableManager.h"
#include "MyGameInstance.generated.h"

/**
 * 
 */
UCLASS()
class MYPROJECT_API UMyGameInstance : public UGameInstance
{
	GENERATED_BODY()
	
public:
	UMyGameInstance();

protected:
	virtual void Init() override;


	//패키지 저장함수.
	void SaveStudentPackage() const;


	void LoadStudentPackage() const;

	//경로 기반으로 언리얼 오브젝트를 로드하는 함수.
	void LoadStudentObject() const;

private:
	UPROPERTY()
	TObjectPtr<class UStudent> StudentSource;


	//패키지이름
	static const FString PackageName;
	//에셋이름
	static const FString AssetName;


	//에셋 로드에 사용할 관리자
	FStreamableManager StreamableManager;

	//에셋을 스트리밍 방식으로 처리할떄 필요한 핸들.
	TSharedPtr<FStreamableHandle> Handle;
};
