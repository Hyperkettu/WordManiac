// Fill out your copyright notice in the Description page of Project Settings.


#include "Letter.h"

// Sets default values
ALetter::ALetter()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	Mesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("StaticMesh"));
	Mesh->SetupAttachment(RootComponent);

	const ConstructorHelpers::FObjectFinder<UMaterial> Material(TEXT("Material'/Game/Materials/Mat_Letter.Mat_Letter'"));

	if (Material.Object) {
		LetterMaterial = (UMaterial*) Material.Object;
	}
}

// Called when the game starts or when spawned
void ALetter::BeginPlay()
{
	Super::BeginPlay();

	DynamicMaterial = Mesh->CreateDynamicMaterialInstance(0, LetterMaterial);
	Mesh->SetMaterial(0, DynamicMaterial);

	UTexture2D* Texture = LoadObject<UTexture2D>(nullptr, TEXT("/Game/Images/C.C"));
	DynamicMaterial->SetTextureParameterValue(FName("Albedo"), Texture);
}

// Called every frame
void ALetter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}