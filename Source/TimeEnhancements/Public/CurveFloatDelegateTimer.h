// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "DelegateTimer.h"
#include "Curves/CurveFloat.h"
#include "TimeEnhancements.h"
#include "CurveFloatDelegateTimer.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE_FiveParams(FDelegateTimerFloatExec, const UCurveFloatDelegateTimer*, CurveFloatTimer, float, CurveElapsedTime, float, CurveTimeSinceLast, float, CurveValue, float, CurveTime);
/**
 * 
 */
UCLASS()
class TIMEENHANCEMENTS_API UCurveFloatDelegateTimer : public UBlueprintAsyncActionBase
{
	GENERATED_BODY()

public:
  UFUNCTION(BlueprintCallable, Category = "Time Enhancements", meta = (BlueprintInternalUseOnly = "true", WorldContext = "WorldContextObject", AdvancedDisplay = "bLoops, CurveDuration"))
  static UCurveFloatDelegateTimer* CreateCurveFloatDelegateTimer(UObject* WorldContextObject, float Period, float DelayToFirstExecution, const UCurveFloat* Curve, bool bLoops = true, float CurveDuration = 0.0f);
  
  UPROPERTY(BlueprintAssignable)
  FDelegateTimerFloatExec CurveEvalTick;

protected:
  virtual UCurveFloatDelegateTimer* Init(UObject* WorldContextObject, float Period, float DelayToFirstExecution, const UCurveFloat* Curve, bool bLoops, float CurveDuration);

  const UCurveFloat* Curve;
  bool bLoops;
  float CurveDuration;

private:

  UFUNCTION()
  void FireCurveEvalTick(const UDelegateTimer* Timer, float ElapsedTime, float TimeSinceLast);
};
