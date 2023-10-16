// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Kismet/BlueprintFunctionLibrary.h"
//�O���w�b�_�ǂݍ��݂̒ǉ�2��
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


		//RenderTarget��n���ƁAPNG�̃o�C�g�z��ɂ��ĕۑ�����
		UFUNCTION(BlueprintCallable, Category = "TK")
		static void RenderTargetToPNG(FString filePath, UTextureRenderTarget2D* SourceImg);

		//���鐔���܂ł̑f����S�Ĕz��ɕۑ�����
		UFUNCTION(BlueprintCallable, Category = "TK")
		static void PrimeNumberCPP(UPARAM(ref) TArray<int>& PrimeArray, int MaxNum);
	
};
