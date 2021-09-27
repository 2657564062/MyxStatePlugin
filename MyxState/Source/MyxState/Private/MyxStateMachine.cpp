// Fill out your copyright notice in the Description page of Project Settings.


#include "MyxStateMachine.h"

UMyxState* UMyxStateMachine::AddState(TSubclassOf<UMyxState> StateClass)
{
    UMyxState* NewState = NewObject<UMyxState>(this, StateClass);
    NewState->InitState();
    return NewState;
}

void UMyxStateMachine::SetEntryState(UMyxState* State)
{
    EntryState = State;
}

void UMyxStateMachine::Start()
{
    if (EntryState)
    {
        StackedStates.Push(EntryState);
        EntryState->EnterState();
        bIsRunning = true;
    }
}

void UMyxStateMachine::Stop()
{
    bIsRunning = false;
    StackedStates.Empty();
}

bool UMyxStateMachine::IsRunning()
{
    return bIsRunning;
}

UMyxState* UMyxStateMachine::GetActiveState()
{
    return StackedStates.Top();
}

void UMyxStateMachine::InitState_Implementation()
{
    Super::InitState_Implementation();
    //UMyxState* NullState = NewObject<UMyxState>(this);
    //NamedStates.Add(FName("NullState"), NullState);
}

void UMyxStateMachine::TickState_Implementation(float DeltaTime)
{
    if (IsRunning())
    {
        Super::TickState_Implementation(DeltaTime);
        StackedStates.Top()->TickState(DeltaTime);
    }
}

void UMyxStateMachine::HandleInput_Implementation(uint8 Input)
{
    
    if (IsRunning())
    {
        Super::HandleInput_Implementation(Input);
        Super::HandleInput(Input);
        GetActiveState()->HandleInput(Input);
    }

}

void UMyxStateMachine::PushState(UMyxState* State)
{
    if (IsRunning())
    {
        if (State)
        {
            GetActiveState()->ExitState();
            StackedStates.Push(State);
            GetActiveState()->EnterState();
            if (StackedStates.Num() > MaxStackDepth)
            {
                StackedStates.RemoveAt(0);
            }
        }
    }
}

void UMyxStateMachine::PopState()
{
    if (IsRunning())
    {
        if (StackedStates.Num() > 0)
        {
            StackedStates.Pop()->ExitState();
            GetActiveState()->EnterState();
        }
    }
}
