// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/ObjectMacros.h"
#include "UObject/Object.h"
#include "MyxState.generated.h"

class UMyxStateMachine;

/**
 * 
 */
UCLASS(Blueprintable, BlueprintType)
class MYXSTATE_API UMyxState : public UObject
{
	GENERATED_BODY()

private:
	float ElapsedTime = 0.f;

	int32 TickFrames = 0;

	TMap<FName, UMyxState*> Transitions;

	UMyxStateMachine* StateMachine;

	UObject* StateContext;

protected:
	UFUNCTION(BlueprintCallable)
	void EnterTransition(FName TransitionName);

public:
	UFUNCTION(BlueprintCallable, BlueprintNativeEvent)
	void InitState();
	virtual void InitState_Implementation();

	UFUNCTION(BlueprintNativeEvent)
	void EnterState();
	virtual void EnterState_Implementation();

	UFUNCTION(BlueprintCallable, BlueprintNativeEvent)
	void TickState(float DeltaTime);
	virtual void TickState_Implementation(float DeltaTime);

	UFUNCTION(BlueprintNativeEvent)
	void ExitState();
	virtual void ExitState_Implementation();

	UFUNCTION(BlueprintCallable, BlueprintNativeEvent)
	void HandleInput(uint8 input);
	virtual void HandleInput_Implementation(uint8 Input);

	UFUNCTION(BlueprintCallable)
	void AddTransition(FName TransitionName, UMyxState* TargetState);

	UFUNCTION(BlueprintPure)
	float GetElapsedTime();

	UFUNCTION(BlueprintPure)
	int32 GetTickFrames();

	UFUNCTION(BlueprintPure)
	UMyxStateMachine* GetStateMachine()const;

	UFUNCTION(BlueprintPure)
	UObject* GetStateContext()const;

};
