// Fill out your copyright notice in the Description page of Project Settings.


#include "RWCsvFile.h"
#include "Misc/FileHelper.h"
#include "Misc/Paths.h"
#include "HAL/FileManagerGeneric.h"

// Structure to represent a row in the CSV file
//struct FCSVRow
//{
//    TArray<float> Column1;
//    TArray<float> Column2;
//    TArray<float> Column3;
//    TArray<float> Column4;
////};
//UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Load File")
//TArray<float> Column1;
//
//UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Load File")
//TArray<float> Column2;
//
//UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Load File")
//TArray<float> Column3;
//
//UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Load File")
//TArray<float> Column4;

bool success_Status = true;
using floatarray1 = TArray<float>;
TArray<floatarray1> NestedArray;
//TArray<float> URWTxtFile::Column1;
//TArray<float> URWTxtFile::Column2;
//TArray<float> URWTxtFile::Column3;
//TArray<float> URWTxtFile::Column4;

FYourGlobalArrays URWCsvFile::LoadCSVFile(const FString& FolderPath/*, int32 hourVal*/, float minConc/*, float maxConc*/)
{
    //FCSVRow csvData;
    FYourGlobalArrays GlobalArrays;

    int noofpoints = 0;

    //clear all arrays of any old values
    GlobalArrays.x.Empty();
    GlobalArrays.y.Empty();
    GlobalArrays.z.Empty();
    GlobalArrays.conc.Empty();
    GlobalArrays.timeinfo.Empty();

    IFileManager& FileManager = IFileManager::Get();

    // Get a list of all files in the specified folder
    TArray<FString> FileNames;
    FileManager.FindFiles(FileNames, *FolderPath, nullptr);

    // Process each file in the folder
    for (const FString& FileName : FileNames)
    {
        // Print or process each file name
        UE_LOG(LogTemp, Warning, TEXT("File found in folder: %s"), *FileName);
        /*UE_LOG(LogTemp, Warning, TEXT("time to check: %d"), hourVal);*/
        // Combine the folder path and file name to get the full file path
        FString FullFilePath = FPaths::Combine(FolderPath, FileName);

        // Read the entire file into a string
        FString FileContent;
        if (FFileHelper::LoadFileToString(FileContent, *FullFilePath))
        {
            TArray<FString> Rows;
            FileContent.ParseIntoArray(Rows, TEXT("\n"), true); // Split by newlines
            //UE_LOG(LogTemp, Warning, TEXT("Column : % s"), Rows.Num());
            int64 row_pointer = 0;

            FString check = "18081801";
            // Ensure that the file has at least 4 columns
            for (const FString& Row : Rows)
            {
                /*if (row_pointer == 0)
                {
                    row_pointer += 1;
                    continue;
                }*/
                TArray<FString> Columns;
                Row.ParseIntoArray(Columns, TEXT(","), true); // Split by spaces

                int c = 0;
                // Log each individual column for debugging
                if (/*FCString::Atoi(*Columns[4].Right(3)) == hourVal && (*/FCString::Atof(*Columns[3])>minConc /*&& FCString::Atof(*Columns[3])<maxConc)*/)                                   // if (FCString::Atof(*Columns[3]) > 50) -- previous commented statement
                {
                    //if (Columns[4].Equals(check))
                    //{
                    //    UE_LOG(LogTemp, Error, TEXT("incorrect value : %s"), *Columns[4]);
                    //    //UE_LOG(LogTemp, Error, TEXT("type value : %s"), *FString::Printf(TEXT("%s"), *Columns[4].GetTypeName()));
                    //    break;
                    //}
                    /*UE_LOG(LogTemp, Warning, TEXT("time : %s"), *Columns[4]);
                    UE_LOG(LogTemp, Warning, TEXT("right 2 places : %d"), FCString::Atoi(*Columns[4].Right(3)));*/
                    noofpoints += 1;
                    for (int32 Index = 0; Index < Columns.Num(); Index++)
                    {
                        if (c == 0)
                        {
                            GlobalArrays.x.Add(FCString::Atof(*Columns[Index]));
                        }
                        else if (c == 1)
                        {
                            GlobalArrays.y.Add(FCString::Atof(*Columns[Index]));
                        }
                        else if (c == 2)
                        {
                            GlobalArrays.z.Add(FCString::Atof(*Columns[Index]));
                        }
                        else if (c == 3)
                        {
                            /*if (FCString::Atof(*Columns[3]) > 10)
                            {
                            }*/
                            GlobalArrays.conc.Add(FCString::Atof(*Columns[Index]));
                        }
                        //else if (c == 4)
                        //{
                        //   /* UE_LOG(LogTemp, Warning, TEXT("Column : entered 5th case"));
                        //    UE_LOG(LogTemp, Warning, TEXT("time : %s"), *Columns[Index].Right(2));*/
                        //    GlobalArrays.timeinfo.Add(FCString::Atoi(*Columns[Index]));
                        //    //GlobalArrays.timeinfo.Add(1);
                        //}
                        c += 1;
                        if (c >= 4)
                        {
                            c = 0;
                        }
                    }
                }
                // Log the length of the array
                //UE_LOG(LogTemp, Warning, TEXT("Row %d, Columns length: %d"), Rows.Find(Row) + 1, GlobalArrays.Column4.Num());
            }
        }
        else
        {
            UE_LOG(LogTemp, Error, TEXT("Failed to load file: %s"), *FullFilePath);
            success_Status = false;
        }
    }
    //UE_LOG(LogTemp, Warning, TEXT("Columns length: %d"), Columns.Num());
    //NestedArray.Add(Instance->Column1);
    //NestedArray.Add(Instance->Column2);
    //NestedArray.Add(Instance->Column3);
    //NestedArray.Add(Instance->Column4);
    //GlobalArrays.Column1 = Column1;
    //GlobalArrays.Column2 = Column2;
    //GlobalArrays.Column3 = Column3;
    //GlobalArrays.Column4 = Column4;
    UE_LOG(LogTemp, Warning, TEXT("col count : %d"),GlobalArrays.x.Num());
    UE_LOG(LogTemp, Warning, TEXT("col count : %d"), GlobalArrays.y.Num());
    UE_LOG(LogTemp, Warning, TEXT("col count : %d"), GlobalArrays.z.Num());
    UE_LOG(LogTemp, Warning, TEXT("col count : %d"), GlobalArrays.conc.Num());
    //UE_LOG(LogTemp, Warning, TEXT("col count : %d"), GlobalArrays.timeinfo.Num());

    UE_LOG(LogTemp, Warning, TEXT("total no of points : %lld"), noofpoints);

    //UE_LOG(LogTemp, Warning, TEXT("col count : %f"), GlobalArrays.x.Last());
    //UE_LOG(LogTemp, Warning, TEXT("col count : %f"), GlobalArrays.y.Last());
    //UE_LOG(LogTemp, Warning, TEXT("col count : %f"), GlobalArrays.z.Last());
    //UE_LOG(LogTemp, Warning, TEXT("col count : %f"), GlobalArrays.conc.Last());
    //UE_LOG(LogTemp, Warning, TEXT("col count : %d"), GlobalArrays.timeinfo.Last());
    return GlobalArrays;
}

