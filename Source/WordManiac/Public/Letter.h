// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Letter.generated.h"

UCLASS()
class WORDMANIAC_API ALetter : public AActor
{
	GENERATED_BODY()
	
public:

	// Sets default values for this actor's properties
	ALetter();

	// Called every frame
	virtual void Tick(float DeltaTime) override;

	void SetLetter(char Letter);

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite)
	UStaticMeshComponent* Mesh;

	UMaterialInstanceDynamic* DynamicMaterial;

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	UMaterialInterface* LetterMaterial;




};
