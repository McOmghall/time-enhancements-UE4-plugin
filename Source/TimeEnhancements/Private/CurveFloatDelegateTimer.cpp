// Fill out your copyright notice in the Description page of Project Settings.

#include "CurveFloatDelegateTimer.h"

UCurveFloatDelegateTimer* UCurveFloatDelegateTimer::CreateCurveFloatDelegateTimer(UObject* WorldContextObject, float Period, float DelayToFirstExecution, const UCurveFloat* Curve, bool bLoops, float CurveDuration)
{
  UCurveFloatDelegateTimer* Timer = NewObject<UCurveFloatDelegateTimer>(WorldContextObject);
  return Timer->Init(WorldContextObject, Period, DelayToFirstExecution, Curve, bLoops, CurveDuration);
}

UCurveFloatDelegateTimer* UCurveFloatDelegateTimer::Init(UObject* WorldContextObject, float Period, float DelayToFirstExecution, const UCurveFloat* Curve, bool bLoops, float CurveDuration)
{
  UDelegateTimer* AuxDelegate = UDelegateTimer::CreateDelegateTimer(WorldContextObject, Period, DelayToFirstExecution);
  AuxDelegate->TickExec.AddDynamic(this, &UCurveFloatDelegateTimer::FireCurveEvalTick);
  this->Curve = Curve == nullptr ? NewObject<UCurveFloat>() : Curve;
  this->bLoops = bLoops;
  this->CurveDuration = CurveDuration == 0.0f ? Curve->GetCurves()[0].CurveToEdit->GetLastKey().Time : CurveDuration;
  return this;
}

void UCurveFloatDelegateTimer::FireCurveEvalTick(const UDelegateTimer * Timer, float ElapsedTime, float TimeSinceLast)
{
  UE_LOG(TimeEnhancementsLog, Log, TEXT("Timer %s in UCurveFloatDelegateTimer::FireCurveEvalTick"), *this->GetName());
  if (this->CurveEvalTick.IsBound())
  {
    float TimeToEvalCurve = this->bLoops ? FMath::Fmod(ElapsedTime, this->CurveDuration) : this->CurveDuration;
    this->CurveEvalTick.Broadcast(this, ElapsedTime, TimeSinceLast, this->Curve->GetFloatValue(TimeToEvalCurve), TimeToEvalCurve);
  }
}
