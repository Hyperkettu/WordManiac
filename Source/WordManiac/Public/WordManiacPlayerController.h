// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerController.h"
#include "WordManiacPlayerController.generated.h"

/**
 * 
 */
UCLASS()
class WORDMANIAC_API AWordManiacPlayerController : public APlayerController
{
	GENERATED_BODY()

protected:
    virtual void BeginPlay() override;

private:
    // Camera class that we'll search for in the level
    TSubclassOf<AActor> CustomCameraClass;
};
