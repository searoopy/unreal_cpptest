// Fill out your copyright notice in the Description page of Project Settings.


#include "Person.h"
#include "Card.h"

UPerson::UPerson()
{
	Name = TEXT("개노무");
	Year = 1;


	Card = CreateDefaultSubobject<UCard>(TEXT("Card"));
}


