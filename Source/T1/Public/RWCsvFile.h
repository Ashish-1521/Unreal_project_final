// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Kismet/BlueprintFunctionLibrary.h"
#include "RWCsvFile.generated.h"

/**
 * 
 */
USTRUCT(BlueprintType)
struct FYourGlobalArrays
{
    GENERATED_USTRUCT_BODY()
    UPROPERTY(BlueprintReadOnly)
    TArray<float> x;

    UPROPERTY(BlueprintReadOnly)
    TArray<float> y;

    UPROPERTY(BlueprintReadOnly)
    TArray<float> z;

    UPROPERTY(BlueprintReadOnly)
    TArray<float> conc;

    UPROPERTY(BlueprintReadOnly)
    TArray<int> timeinfo;
};
UCLASS()
class T1_API URWCsvFile : public UBlueprintFunctionLibrary
{
    GENERATED_BODY()

public:
    /*UFUNCTION(BlueprintCallable, Category = "Load File")
    static bool LoadCSVFile(const FString& FolderPath, URWTxtFile* Instance);*/
    //using FloatArray = TArray<float>;
    //static TArray<float> Column1;
    //static TArray<float> Column2;
    //static TArray<float> Column3;
    //static TArray<float> Column4;
   /* UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Load File")
    TArray<float> Column1;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Load File")
    TArray<float> Column2;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Load File")
    TArray<float> Column3;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Load File")
    TArray<float> Column4;*/

    UFUNCTION(BlueprintCallable, Category = "Load File")
    static FYourGlobalArrays LoadCSVFile(const FString& FolderPath/*, int32 hourval */,float minConc /*,float maxConc*/);

};
