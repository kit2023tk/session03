// Fill out your copyright notice in the Description page of Project Settings.


#include "MyBlueprintFunctionLibrary.h"

int UMyBlueprintFunctionLibrary::CalculateValues()
{
	return 10;
}

void UMyBlueprintFunctionLibrary::RenderTargetToPNG(FString filePath, UTextureRenderTarget2D* SourceImg)
{
    //きちんと処理ができるRender Targetかどうか判定とエラー処理
    if (!SourceImg || !SourceImg->GetResource() || !SourceImg->GetResource()->TextureRHI)
    {
        UE_LOG(LogTemp, Warning, TEXT("Upload Texture is invalid"));
        return;
    }

    FTexture2DRHIRef Texture2D = SourceImg->GetResource()->TextureRHI->GetTexture2D();
    if (!Texture2D)
    {
        UE_LOG(LogTemp, Warning, TEXT("Upload Texture2D is invalid"));
        return;
    }

    //Render Targetの内部データを格納するための構造体の設定と作成
    TArray<FColor> OutPixels;
    struct FReadSurfaceContext
    {
        FTexture2DRHIRef Texture;
        TArray<FColor>* OutData;
        FIntRect Rect;
        FReadSurfaceDataFlags Flags;
    };

    FReadSurfaceContext ReadSurfaceContext =
    {
        Texture2D,
        &OutPixels,
        FIntRect(0, 0, Texture2D->GetSizeXY().X, Texture2D->GetSizeXY().Y),
        FReadSurfaceDataFlags(RCM_UNorm, CubeFace_MAX)
    };

    //Render Targetの画像データを取得
    FReadSurfaceContext Context = ReadSurfaceContext;
    ENQUEUE_RENDER_COMMAND(ReadSurfaceCommand)(
        [Context](FRHICommandListImmediate& RHICmdList)
        {
            RHICmdList.ReadSurfaceData(
                Context.Texture,
                Context.Rect,
                *Context.OutData,
                Context.Flags
            );
        });

    FlushRenderingCommands();

    //PNG圧縮
    TArray<uint8> ImgData;
    TArray64<uint8> ImgData64;
    FImageUtils::PNGCompressImageArray(Context.Rect.Width(), Context.Rect.Height(), OutPixels, ImgData64);

    ImgData.AddUninitialized(ImgData64.Num());
    FMemory::Memcpy(ImgData.GetData(), ImgData64.GetData(), ImgData64.Num() * sizeof(uint8));

    //ファイルとして保存
    FString fullPath = FPaths::ProjectSavedDir() + filePath;
    FFileHelper::SaveArrayToFile(ImgData, *fullPath);
    
}
