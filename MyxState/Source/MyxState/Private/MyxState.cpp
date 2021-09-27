// Fill out your copyright notice in the Description page of Project Settings.


#include "MyxState.h"
#include "MyxStateMachine.h"

void UMyxState::EnterTransition(FName TransitionName)
{
	UMyxState* State = Transitions.FindRef(TransitionName);
	if (State)
	{
		StateMachine->PushState(State);
	}
}

void UMyxState::InitState_Implementation()
{
	bool bFoundRoot = false;
	UObject* Root = (UObject*)(this);
	while (!bFoundRoot)
	{
		if (Root->GetOuter()->IsA<UMyxStateMachine>())
		{
			if (Root == this)
			{
				StateMachine = Cast<UMyxStateMachine>(GetOuter());
			}
			Root = Root->GetOuter();
		}
		else
		{
			bFoundRoot = true;
			StateContext = Root->GetOuter();
		}
	}
}

void UMyxState::EnterState_Implementation()
{
	ElapsedTime = 0.f;
	TickFrames = 0;
}

void UMyxState::TickState_Implementation(float DeltaTime)
{
	ElapsedTime += DeltaTime;
	TickFrames++;
}

void UMyxState::ExitState_Implementation()
{
}

void UMyxState::HandleInput_Implementation(uint8 Input)
{
}

void UMyxState::AddTransition(FName TransitionName, UMyxState* TargetState)
{
	Transitions.Add(TransitionName, TargetState);
}

float UMyxState::GetElapsedTime()
{
	return ElapsedTime;
}

int32 UMyxState::GetTickFrames()
{
	return TickFrames;
}

UMyxStateMachine* UMyxState::GetStateMachine() const
{
	return StateMachine;
}

UObject* UMyxState::GetStateContext() const
{
	return StateContext;
}
