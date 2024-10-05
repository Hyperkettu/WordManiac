// Fill out your copyright notice in the Description page of Project Settings.


#include "WordManiacPlayerController.h"
#include "Kismet/GameplayStatics.h"
#include "GameFramework/Actor.h"
#include "SplineCameraActor.h"


void AWordManiacPlayerController::BeginPlay()
{
    Super::BeginPlay();

    CustomCameraClass = ASplineCameraActor::StaticClass();

    // Find the first instance of the custom camera actor in the level
    AActor* CustomCamera = UGameplayStatics::GetActorOfClass(GetWorld(), CustomCameraClass);

    if (CustomCamera)
    {
        // Set this camera as the new view target for the player controller
        SetViewTarget(CustomCamera);
    }
}