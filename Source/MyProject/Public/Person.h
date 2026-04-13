// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"

#include "Card.h"
#include "Person.generated.h"



/**
 * 
 */
UCLASS()
class MYPROJECT_API UPerson : public UObject
{
	GENERATED_BODY()

public:
	UPerson();

	UFUNCTION()
	//virtual void DoLesson();

	FORCEINLINE FString GetName() const { return Name; }
	FORCEINLINE void SetName(const FString& InName) { Name = InName; }
	
	FORCEINLINE UCard* GetCard() const { return Card; }
	FORCEINLINE void SetCard(UCard* InCard)
	{
		Card = InCard;
	}


protected:
	UPROPERTY()
	FString Name;

	UPROPERTY()
	int32 Year;


	UPROPERTY()
	TObjectPtr<UCard> Card;
};
