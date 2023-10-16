// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Kismet/BlueprintFunctionLibrary.h"
//外部ヘッダ読み込みの追加2個
#include "ImageUtils.h"
#include "Engine/TextureRenderTarget2D.h"

#include "MyBlueprintFunctionLibrary.generated.h"

/**
 * 
 */
UCLASS()
class THIRDPERSONCPP_API UMyBlueprintFunctionLibrary : public UBlueprintFunctionLibrary
{
	GENERATED_BODY()

		UFUNCTION(BlueprintCallable, Category = "TK")
		static int CalculateValues();


		//RenderTargetを渡すと、PNGのバイト配列にして保存する
		UFUNCTION(BlueprintCallable, Category = "TK")
		static void RenderTargetToPNG(FString filePath, UTextureRenderTarget2D* SourceImg);

		//ある数字までの素数を全て配列に保存する
		UFUNCTION(BlueprintCallable, Category = "TK")
		static void PrimeNumberCPP(UPARAM(ref) TArray<int>& PrimeArray, int MaxNum);
	
};
