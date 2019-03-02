// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/EngineTypes.h"
#include "Kismet/BlueprintAsyncActionBase.h"
#include "TimeEnhancements.h"
#include "DelegateTimer.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE_ThreeParams(FDelegateTimerExec, const UDelegateTimer*, Timer, float, ElapsedTime, float, TimeSinceLast);
/**
 * 
 */
UCLASS(Blueprintable, BlueprintType)
class TIMEENHANCEMENTS_API UDelegateTimer : public UBlueprintAsyncActionBase
{
	GENERATED_BODY()
public:
  UPROPERTY(BlueprintAssignable)
  FDelegateTimerExec TickExec;

  UPROPERTY(BlueprintReadOnly)
  FDateTime TimeStart;

  UPROPERTY(BlueprintReadOnly)
  FDateTime TimeFirstExecution;

  UPROPERTY(BlueprintReadOnly)
  FDateTime TimeLastExecution;

  UFUNCTION(BlueprintCallable, Category = "Time Enhancements", meta = (BlueprintInternalUseOnly = "true", WorldContext = "WorldContextObject"))
  static UDelegateTimer* CreateDelegateTimer(UObject* WorldContextObject, float Period /*= 2.0f*/, float DelayToFirstExecution);

  UFUNCTION(BlueprintPure)
  FString ToString() const
  {
    return GetFName().ToString() + "@" + this->GetOuter()->GetName() + " > TimerHandleID." + TimerHandle.ToString();
  }

protected:
  virtual UDelegateTimer* Init(UObject* WorldContextObject, float Period, float DelayToFirstExecution);
  virtual void ExecutionCycle();
  FTimerHandle TimerHandle;
};
