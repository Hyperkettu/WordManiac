// Fill out your copyright notice in the Description page of Project Settings.


#include "SplineCameraActor.h"

#include "Components/SplineComponent.h"
#include "Camera/CameraComponent.h"

// Constructor
ASplineCameraActor::ASplineCameraActor()
{
	PrimaryActorTick.bCanEverTick = true;

	// Initialize Spline Component
	SplineComponent = CreateDefaultSubobject<USplineComponent>(TEXT("SplineComponent"));
	RootComponent = SplineComponent;

	// Initialize Camera Component
	CameraComponent = CreateDefaultSubobject<UCameraComponent>(TEXT("CameraComponent"));
	CameraComponent->SetupAttachment(RootComponent);

	// Default values
	SplineDuration = 10.0f;
	CurrentTime = 0.0f;
}

// Called when the game starts or when spawned
void ASplineCameraActor::BeginPlay()
{
	Super::BeginPlay();
}

// Called every frame
void ASplineCameraActor::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	MoveCameraAlongSpline(DeltaTime);
}

// Moves the camera along the spline based on elapsed time
void ASplineCameraActor::MoveCameraAlongSpline(float DeltaTime)
{
	if (!runSplineAnimation) {
		return;
	}

	if (!SplineComponent) return;

	// Update the current time
	CurrentTime += DeltaTime;
	if (CurrentTime > SplineDuration)
	{
		CurrentTime = 0.0f;  // Reset or handle the end of the movement
	}

	// Calculate the percentage of time elapsed
	float TimeRatio = CurrentTime / SplineDuration;

	// Get the spline's length
	float SplineLength = SplineComponent->GetSplineLength();

	// Calculate the distance along the spline based on time
	float Distance = TimeRatio * SplineLength;

	// Interpolate the location and rotation along the spline
	FVector NewLocation = SplineComponent->GetLocationAtDistanceAlongSpline(Distance, ESplineCoordinateSpace::World);
	FRotator NewRotation = SplineComponent->GetRotationAtDistanceAlongSpline(Distance, ESplineCoordinateSpace::World);

	// Set the camera's location and rotation
	CameraComponent->SetWorldLocation(NewLocation);
	CameraComponent->SetWorldRotation(NewRotation);
}