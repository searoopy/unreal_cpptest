// Fill out your copyright notice in the Description page of Project Settings.


#include "MyGameInstance.h"
#include "StudentData.h"
#include "Student.h"
#include "JsonObjectConverter.h"
#include "UObject/SavePackage.h"

const FString UMyGameInstance::PackageName = TEXT("/Game/Student");
const FString UMyGameInstance::AssetName = TEXT("Student");


void PrintStudentInfo(
	const UStudent* Student,
	const FString& InTag)
{

	UE_LOG(LogTemp, Log, TEXT("[%s] 이름 :%s,  순번: %d"), *InTag, *Student->GetName(), Student->GetOrder());
}

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
			//*RawFileWriteAr << RawDataSource.Order;
			//*RawFileWriteAr << RawDataSource.Name;
			*RawFileWriteAr << RawDataSource;


			RawFileWriteAr->Close();
			delete RawFileWriteAr;
			RawFileWriteAr = nullptr;
		}



		//파일로부터 데이터를 읽어와서 구조체에 복원.
		//역직렬화(deserialization)
		FStudentData RawDataDest;




		//파일 읽기를 위한 아카이브 얻어오기.
		FArchive* RawFileReaderAr=
			IFileManager::Get().CreateFileReader(*RawDataFullPath);
		if (RawFileReaderAr)
		{
			*RawFileReaderAr << RawDataDest;

			RawFileReaderAr->Close();
			delete RawFileReaderAr;
			RawFileReaderAr = nullptr;


			UE_LOG(LogTemp, Log, TEXT("RawDataDest.Order : %d"), RawDataDest.Order);
			UE_LOG(LogTemp, Log, TEXT("RawDataDest.Name : %s"), *RawDataDest.Name);	

		}
	}



	//언리얼 오브젝트 생성./
	StudentSource = NewObject<UStudent>();
	StudentSource->SetOrder(33);
	StudentSource->SetName(TEXT("개똥이"));


	//직렬화 테스트를 위한 구간 나누기.
	{
		const FString& StudentDataFileName = TEXT("StudentData.bin");


		//파일이름을 포함한 경로 생성.
		FString StudentDataFullPath = FPaths::Combine(
			SavePath, StudentDataFileName
		);

		//경로 정리
		FPaths::MakeStandardFilename(StudentDataFullPath);


		//메모리를 담을 버퍼.
		TArray<uint8> BufferArray;
		FMemoryWriter MemoryWriter(BufferArray);

		//memory writer로 직렬화하기.
		StudentSource->Serialize(MemoryWriter);


		//파일에 기록
		TUniquePtr<FArchive>
			FileWriteAr = TUniquePtr<FArchive>(
				IFileManager::Get().CreateFileWriter(*StudentDataFullPath)
			);

		//파일 잘 열었는지 확인
		if (FileWriteAr)
		{
			*FileWriteAr << BufferArray;

			FileWriteAr->Close();
		}


		//언리얼 오브젝트로 복원.
		TArray<uint8> BufferArrayFromFile;
		//파일에 기록
		TUniquePtr<FArchive>
			FileReadAr = TUniquePtr<FArchive>(
				IFileManager::Get().CreateFileReader(*StudentDataFullPath)
			);
		if (FileReadAr)
		{
			*FileReadAr << BufferArrayFromFile;
			FileReadAr->Close();

			//바이트 배열에 저장된 정보를
			//메모리 리더를 통해 객체로 복원.
			FMemoryReader MemoryReader(BufferArrayFromFile);
			UStudent* StudentDest = NewObject<UStudent>();
			StudentDest->Serialize(MemoryReader);



			UE_LOG(LogTemp, Log, TEXT("RawDataDest.Order : %d"), StudentDest->GetOrder());
			UE_LOG(LogTemp, Log, TEXT("RawDataDest.Name : %s"), *StudentDest->GetName());



		}

	}




	//json(javascript object notation)
	{
		const FString JsonFileName = TEXT("StudentJsonData.txt");

		//저장할 파일 경로값	
		FString JsonFullPath = FPaths::Combine(
			SavePath, JsonFileName
		);
		//경로 정리
		FPaths::MakeStandardFilename(JsonFullPath);


		//json직렬화 과정
		//uobject -> json object -> json 문자열 -> 기록.
		TSharedRef<FJsonObject> JsonObject = MakeShared<FJsonObject>();

		//json오브젝트로 변환.
		FJsonObjectConverter::UStructToJsonObject(StudentSource->StaticClass(), StudentSource, JsonObject);

		//직렬화
		FString JsonString;

		TSharedRef<TJsonWriter<TCHAR>> JsonWriter =
		TJsonWriterFactory<TCHAR>::Create(&JsonString);

		if (FJsonSerializer::Serialize(JsonObject, JsonWriter))
		{
			//성공한 경우에 파일에 저장.
			FFileHelper::SaveStringToFile(
				JsonString, *JsonFullPath);
		}




		//역 직렬화.
		FString JsonInString;

		//파일에서 문자열로 읽어오기.,
		FFileHelper::LoadFileToString(JsonInString, *JsonFullPath);

		UE_LOG(LogTemp, Log, TEXT("JsonInString : %s"), *JsonInString);


		//역직렬화를 위한 아카이브 생성.
		TSharedRef<TJsonReader<TCHAR>> JsonReaderAr
			= TJsonReaderFactory<TCHAR>::Create(JsonInString);

		TSharedPtr<FJsonObject> JsonObjectDest;
		if (FJsonSerializer::Deserialize(JsonReaderAr, JsonObjectDest))
		{
			//인리얼 오브젝트 생성후 변환.
			UStudent* JsonStudentDest = NewObject<UStudent>();
			if (FJsonObjectConverter::JsonObjectToUStruct(
				JsonObjectDest.ToSharedRef(),
				JsonStudentDest->StaticClass(),
				JsonStudentDest)
				)
			{
				//UE_LOG(LogTemp, Log, TEXT("JsonStudentDest.Order : %d"), JsonStudentDest->GetOrder());
				//UE_LOG(LogTemp, Log, TEXT("JsonStudentDest.Name : %s"), *JsonStudentDest->GetName());	


				PrintStudentInfo(JsonStudentDest, TEXT("FJsonObject"));
			}
		}
		



	}


	//패키지 저장 함수 실행
	//SaveStudentPackage();
	// 패키지 로드 함수 실행
	//LoadStudentPackage();

	//경로 기반으로 언리얼 오브젝트 로드 함수 실행.
	LoadStudentObject();
}

void UMyGameInstance::SaveStudentPackage() const
{

	//예외처리.
	UPackage* StudentPackage = LoadPackage(nullptr, *PackageName, LOAD_None);
	if (StudentPackage)
	{
		StudentPackage->FullyLoad();
	}


	//패키지 생성.
	StudentPackage = CreatePackage(*PackageName);

	//패키지에 사용할 플래그 지정.
	EObjectFlags PackageFlags = RF_Public | RF_Standalone;

	//패키지에 저장할 언리얼 오브젝트 생성.
	UStudent* StudentAsset = NewObject<UStudent>(
		StudentPackage,
		UStudent::StaticClass(),
		*AssetName,
		PackageFlags
	);

	StudentAsset->SetOrder(55);
	StudentAsset->SetName(TEXT("봉순이"));


	//서브 오브젝트 추가.
	const int32 SubObjectCount = 10;
	for( int32 i= 0; i < SubObjectCount; ++i)
	{
		FString SubAssetName = FString::Printf(TEXT("%s_Sub_%d"), *AssetName, i);

		//객체 생성....
		UStudent* SubStudentAsset = NewObject<UStudent>(
			StudentAsset,
			UStudent::StaticClass(),
			*SubAssetName,
			PackageFlags
		);
		SubStudentAsset->SetOrder(i);
		SubStudentAsset->SetName(FString::Printf(TEXT("서브 학생 %d"), i));
	}



	//패키지 저장.
	FString PackageFileName
		= FPackageName::LongPackageNameToFilename(PackageName,
			FPackageName::GetAssetPackageExtension() );


	//참고로 이렇게도 가능....
	/*FString PackageFileName2
		= FPaths::Combine(
			FPaths::ProjectDir(),
			TEXT("Content"),
			FString::Printf(TEXT("%s%s"), *PackageName, *FPackageName::GetAssetPackageExtension())
		);*/

	//경로값 정리
	FPaths::MakeStandardFilename(PackageFileName);

	//저장할 옵션 설정.
	FSavePackageArgs SaveArgs;
	SaveArgs.TopLevelFlags = PackageFlags;

	//패키지 저장.
	if (UPackage::SavePackage(
		StudentPackage,
		nullptr,
		*PackageFileName,
		SaveArgs
	))
	{
		UE_LOG(LogTemp, Log, TEXT("패키지 저장 성공!"));
	}
	else
	{
		UE_LOG(LogTemp, Error, TEXT("패키지 저장 실패!"));
	}

}

void UMyGameInstance::LoadStudentPackage() const
{

	//패키지 로드
	UPackage* package = LoadPackage(nullptr, *PackageName, LOAD_None);
	if(!package)
			{
		UE_LOG(LogTemp, Error, TEXT("패키지 로드 실패!"));
		return;
	}


	//완전히 로드되도록 함수 실행.
	package->FullyLoad();


	//패키지 안에 있는 언리얼 오브젝트 검색.
	UStudent* student = FindObject<UStudent>(package, *AssetName);

	if (student)
	{
		PrintStudentInfo(student, TEXT("LoadPackage"));
	}
}

void UMyGameInstance::LoadStudentObject() const
{

	//오브젝트 경로값.
	const FString SoftObjectPath = FString::Printf(TEXT("%s.%s"), *PackageName, *AssetName);

	//오브젝트로드
	UStudent* StudentObject = LoadObject<UStudent>(nullptr, *SoftObjectPath);
	if (StudentObject)
	{
		PrintStudentInfo(StudentObject, TEXT("LoadObject"));
	}
}
