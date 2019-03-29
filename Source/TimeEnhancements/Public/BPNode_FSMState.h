// Copyright (C) 2019 Pedro Montoto García - All Rights Reserved

#pragma once

#include "CoreMinimal.h"
#include "K2Node_Event.h"
#include "BPNode_FSMState.generated.h"

#define LOCTEXT_NAMESPACE "FSMOnline"

/**
 * 
 */
UCLASS()
class TIMEENHANCEMENTS_API UBPNode_FSMState : public UK2Node_Event
{
	GENERATED_BODY()
public: 
	UBPNode_FSMState(const FObjectInitializer& ObjectInitializer);

	const FName EventEnterPin = FName("Event Enter");
	const FName EventTickPin = FName("Event Tick");
	const FName EventExitPin = FName("Event Exit");

	const FName StateNamePin = FName("State Name");
	const FName FSMNamePin = FName("FSM Name");

	// Begin UEdGraphNode interface.
	virtual void AllocateDefaultPins() override;
	virtual FLinearColor GetNodeTitleColor() const override
	{
		return FLinearColor::Green;
	}
	virtual void ExpandNode(class FKismetCompilerContext& CompilerContext, UEdGraph* SourceGraph) override;
	// End UEdGraphNode interface.

	// Begin UK2Node interface
	virtual void GetMenuActions(FBlueprintActionDatabaseRegistrar& ActionRegistrar) const override;
	virtual FText GetMenuCategory() const override
	{
		return FText::FromString("FSMOnline");
	}
	/** Gets the default node title when no class is selected */
	virtual FText GetNodeTitle(ENodeTitleType::Type TitleType) const override
	{
		const UEdGraphPin* OutNamePin = FindPin(StateNamePin, EGPD_Input);
		const UEdGraphPin* OutFSMPin = FindPin(FSMNamePin, EGPD_Input);
		switch (TitleType)
		{
		case ENodeTitleType::Type::FullTitle: return LOCTEXT("UBPNode_FSMState.NodeFullTitle", "FSM State Full Title");
		case ENodeTitleType::Type::ListView: return LOCTEXT("UBPNode_FSMState.NodeListViewTitle", "Create New FSM State...");
		case ENodeTitleType::Type::EditableTitle: return LOCTEXT("UBPNode_FSMState.NodeEditableTitle", "FSM State Editable Title");
		case ENodeTitleType::Type::MenuTitle: return LOCTEXT("UBPNode_FSMState.NodeMenuTitle", "Create New FSM State...");
		}
		return LOCTEXT("UBPNode_FSMState.NodeDefaultTitle", "FSM State Default Node Title");
	}
	// End UK2Node interface.

protected:
	/** Gets base class to use for the 'class' pin.  UObject by default. */
	virtual UClass* GetClassPinBaseClass() const
	{
		return UObject::StaticClass();
	}
};
