// Fill out your copyright notice in the Description page of Project Settings.

#include "DelegateTimer.h"
#include "Engine/World.h"
#include "TimerManager.h"

DEFINE_LOG_CATEGORY(TimeEnhancementsLog);

UDelegateTimer* UDelegateTimer::CreateDelegateTimer(UObject* WorldContextObject, float Period, float DelayToFirstExecution)
{
  UDelegateTimer* Timer = NewObject<UDelegateTimer>(WorldContextObject);
  return Timer->Init(WorldContextObject, Period, DelayToFirstExecution);
}

UDelegateTimer* UDelegateTimer::Init(UObject * WorldContextObject, float Period, float DelayToFirstExecution)
{
  this->TimeStart = FDateTime::UtcNow();

  WorldContextObject->GetWorld()->GetTimerManager().SetTimer(this->TimerHandle, this, &UDelegateTimer::ExecutionCycle, FMath::Max(Period, 0.016f), true, DelayToFirstExecution);
  UE_LOG(TimeEnhancementsLog, Log, TEXT("Created %s with %f + %f"), *this->GetName(), Period, DelayToFirstExecution);
  return this;
}

void UDelegateTimer::ExecutionCycle()
{
  UE_LOG(TimeEnhancementsLog, Log, TEXT("Timer %s in UDelegateTimer::ExecutionCycle"), *this->GetName());
  if (this->TickExec.IsBound())
  {
    float TimeSinceLastExecution = this->TimeLastExecution == 0 ? 0.0f : (FDateTime::UtcNow() - this->TimeLastExecution).GetTotalSeconds();
    this->TimeFirstExecution = this->TimeFirstExecution == 0 ? FDateTime::UtcNow() : this->TimeFirstExecution;
    this->TimeLastExecution = FDateTime::UtcNow();
    this->TickExec.Broadcast(this, (this->TimeLastExecution - this->TimeStart).GetTotalSeconds(), TimeSinceLastExecution);
  }
}