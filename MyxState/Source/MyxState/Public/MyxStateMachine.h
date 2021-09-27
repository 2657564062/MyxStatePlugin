// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "MyxState.h"
#include "MyxStateMachine.generated.h"

/**
 * 
 */
UCLASS(Blueprintable,BlueprintType)
class MYXSTATE_API UMyxStateMachine : public UMyxState
{
	GENERATED_BODY()

private:

	TArray<UMyxState*> StackedStates;

	bool bIsRunning = false;

	UMyxState* EntryState;

protected:
	UPROPERTY(EditDefaultsOnly)
	int32 MaxStackDepth = 20;

	UFUNCTION(BlueprintCallable)
	UMyxState* AddState(TSubclassOf<UMyxState> StateClass);

public:
	UFUNCTION(BlueprintCallable)
	void SetEntryState(UMyxState* State);

	UFUNCTION(BlueprintCallable)
	void Start();

	UFUNCTION(BlueprintCallable)
	void Stop();

	UFUNCTION(BlueprintPure)
	bool IsRunning();

	UFUNCTION(BlueprintPure)
	UMyxState* GetActiveState();

	virtual void InitState_Implementation() override;

	virtual void TickState_Implementation(float DeltaTime) override;

	virtual void HandleInput_Implementation(uint8 Input) override;

	UFUNCTION(BlueprintCallable)
	void PushState(UMyxState* State);

	UFUNCTION(BlueprintCallable)
	void PopState();

};
