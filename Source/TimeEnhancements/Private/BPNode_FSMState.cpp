// Copyright (C) 2019 Pedro Montoto García - All Rights Reserved

#include "BPNode_FSMState.h"
#include "BlueprintNodeSpawner.h"
#include "EditorCategoryUtils.h"
#include "BlueprintActionDatabaseRegistrar.h"
#include "BlueprintActionMenuItem.h"
#include "EdGraphSchema_K2.h"
#include "EdGraphSchema_K2_Actions.h"

UBPNode_FSMState::UBPNode_FSMState(const FObjectInitializer& ObjectInitializer)
	: Super(ObjectInitializer)
{
}

void UBPNode_FSMState::AllocateDefaultPins()
{
	CreatePin(EGPD_Output, UEdGraphSchema_K2::PC_Delegate, DelegateOutputName);
	CreatePin(EGPD_Output, UEdGraphSchema_K2::PC_Exec, EventEnterPin);
	CreatePin(EGPD_Output, UEdGraphSchema_K2::PC_Exec, EventTickPin);
	CreatePin(EGPD_Output, UEdGraphSchema_K2::PC_Exec, EventExitPin);

	UEdGraphPin* StateName = CreatePin(EGPD_Input, UEdGraphSchema_K2::PC_Name, StateNamePin);
	UEdGraphPin* FSMName = CreatePin(EGPD_Input, UEdGraphSchema_K2::PC_Name, FSMNamePin);
	StateName->bNotConnectable = false;
	FSMName->bNotConnectable = false;
}

void UBPNode_FSMState::ExpandNode(FKismetCompilerContext & CompilerContext, UEdGraph * SourceGraph)
{
}

void UBPNode_FSMState::GetMenuActions(FBlueprintActionDatabaseRegistrar& ActionRegistrar) const
{
	UBPNode_FSMState* TemplateNode = NewObject<UBPNode_FSMState>(GetTransientPackage(), GetClass());
	UBlueprintNodeSpawner* Spawner = UBlueprintNodeSpawner::Create<UBPNode_FSMState>();

	ActionRegistrar.AddBlueprintAction(Spawner);
}
