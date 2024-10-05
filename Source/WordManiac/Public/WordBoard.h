// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Letter.h"
#include "WordBoard.generated.h"

UCLASS()
class WORDMANIAC_API AWordBoard : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AWordBoard();

	// Called every frame
	virtual void Tick(float DeltaTime) override;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	TSubclassOf<ALetter> LetterBlueprint;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	float LetterWidth = 100.0f;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	float LetterGap = 30.0f;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	int32 MaxLettersPerRowIncludingSpaces = 12;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	FString StartClause;

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	TArray<FString> ProcessStringToRows(const FString& InputString, int32 MaxRowLength = 12);
};
