// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Camera/CameraActor.h"
#include "SplineCameraActor.generated.h"

class USplineComponent;
class UCameraComponent;

UCLASS()
class WORDMANIAC_API ASplineCameraActor : public AActor
{
	GENERATED_BODY()

public:
	ASplineCameraActor();

protected:
	virtual void BeginPlay() override;

public:
	virtual void Tick(float DeltaTime) override;

	// Spline component to define the path
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Camera Path")
	USplineComponent* SplineComponent;

	// Camera component to be animated
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Camera")
	UCameraComponent* CameraComponent;

	// Time taken to move along the spline
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Camera Path")
	float SplineDuration;

	// Function to animate camera along the spline
	void MoveCameraAlongSpline(float DeltaTime);

private:
	float CurrentTime;  // Keeps track of elapsed time

	bool runSplineAnimation = false;
};