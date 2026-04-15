// Fill out your copyright notice in the Description page of Project Settings.


#include "MyGameInstance.h"
#include "StudentData.h"

UMyGameInstance::UMyGameInstance()
{

}	


void UMyGameInstance::Init()
{
	Super::Init();
	UE_LOG(LogTemp, Warning, TEXT("UMyGameInstance::Init() called"));


	//구조체 객체 생성.
	FStudentData RawDataSource(23, TEXT("이상현"));


	//파일로  저장하기 위한 경로 생성.
	const FString SavePath = FPaths::Combine(
		FPlatformMisc::ProjectDir(), TEXT("Saved")
	);

	//파일 저장 테스트를 위한 구간.
	{
		//파일이름
		const FString RawDataFileName = TEXT("RawData.bin");

		//저장 경로 + 파일 이름.
		FString RawDataFullPath = FPaths::Combine(
			SavePath, RawDataFileName
		);



		//경로 출력
		UE_LOG(LogTemp, Log, TEXT("RawDataFullPath : %s"), *RawDataFullPath);




		//경로 정리
		FPaths::MakeStandardFilename(RawDataFullPath);
		//경로 출력
		UE_LOG(LogTemp, Log, TEXT("RawDataFullPath : %s"), *RawDataFullPath);



		//직렬화 사용해서 저장
		FArchive* RawFileWriteAr = IFileManager::Get().CreateFileWriter(*RawDataFullPath);
		if (RawFileWriteAr)
		{
			*RawFileWriteAr << RawDataSource.Order;
			*RawFileWriteAr << RawDataSource.Name;
			RawFileWriteAr->Close();
			delete RawFileWriteAr;
			RawFileWriteAr = nullptr;
		}
	}
}