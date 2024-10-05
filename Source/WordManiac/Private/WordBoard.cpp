// Fill out your copyright notice in the Description page of Project Settings.


#include "WordBoard.h"

// Sets default values
AWordBoard::AWordBoard()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

// Called when the game starts or when spawned
void AWordBoard::BeginPlay()
{
	Super::BeginPlay();

    TArray<FString> Rows = ProcessStringToRows(StartClause, 12);

    int32 RowIndex = 1;

    for (FString Row : Rows) {

        FString RowWords = Row.TrimStartAndEnd();
        int32 NumberOfLetters = RowWords.Len();

        for (int32 i = 1; i <= NumberOfLetters; i++) {

            if (RowWords[i - 1] == ' ') {
                continue;
            }

		    FActorSpawnParameters SpawnParams;
		    SpawnParams.Owner = this; 
		    SpawnParams.SpawnCollisionHandlingOverride = ESpawnActorCollisionHandlingMethod::AdjustIfPossibleButAlwaysSpawn;

		    FVector Position;

            float OffsetX = 0.0f;
            float OffsetZ = 0.0f;

		    if (NumberOfLetters % 2 == 0) {
			    OffsetX = -0.5f * (LetterGap + LetterWidth) + (i - NumberOfLetters / 2.0f) * (LetterWidth + LetterGap);        
		    } else {
			    int32 j = i - 1;
			    
                OffsetX = (j - FMath::Floor(NumberOfLetters / 2.0f)) * (LetterWidth + LetterGap);
		    }

            if (Rows.Num() % 2 == 0) {
                OffsetZ = -0.5f * (LetterGap + LetterWidth) + (RowIndex - Rows.Num() / 2.0f) * (LetterWidth + LetterGap);
            } else {
                int32 k = RowIndex - 1;
                OffsetZ = (k - FMath::Floor(Rows.Num() / 2.0f)) * (LetterWidth + LetterGap);
            }

            Position = FVector(OffsetX, 0.0f, -OffsetZ);

		    ALetter* SpawnedLetter = GetWorld()->SpawnActor<ALetter>(LetterBlueprint, Position,FRotator::ZeroRotator, SpawnParams);
            SpawnedLetter->SetLetter(RowWords[i - 1]);
	    }
        RowIndex++;
    }
}

// Called every frame
void AWordBoard::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}


TArray<FString> AWordBoard::ProcessStringToRows(const FString& InputString, int32 MaxRowLength)
{
        TArray<FString> Words;
        TArray<FString> Rows;

        // Split the input string into words
        InputString.ParseIntoArray(Words, TEXT(" "), true);

        FString CurrentRow;

        for (const FString& Word : Words)
        {
            // If the word itself is longer than the max row length, just add it as its own row
            if (Word.Len() > MaxRowLength)
            {
                // If there is already some content in the current row, push it first
                if (!CurrentRow.IsEmpty())
                {
                    Rows.Add(CurrentRow);
                    CurrentRow.Empty();
                }

                // Add the long word as its own row and continue
                Rows.Add(Word);
            } else
            {
                // Check if adding the word would exceed the max row length
                int32 NewRowLength = CurrentRow.Len() + Word.Len() + (CurrentRow.IsEmpty() ? 0 : 1); // +1 for space if needed

                if (NewRowLength <= MaxRowLength)
                {
                    // Add the word to the current row
                    if (!CurrentRow.IsEmpty())
                    {
                        CurrentRow.Append(TEXT(" "));  // Add a space before appending the next word
                    }
                    CurrentRow.Append(Word);
                } else
                {
                    // If it exceeds, add the current row to the list of rows and start a new row with the word
                    Rows.Add(CurrentRow);
                    CurrentRow = Word;
                }
            }
        }

        // Add the last row if there is any
        if (!CurrentRow.IsEmpty())
        {
            Rows.Add(CurrentRow);
        }

        return Rows;
}
