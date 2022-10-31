using UnrealBuildTool;
using System.Collections.Generic;

public class BehaviorTreeDesignEditorTarget : TargetRules
{
	public BehaviorTreeDesignEditorTarget(TargetInfo Target) : base(Target)
	{
		Type = TargetType.Editor;
		ExtraModuleNames.Add("BehaviorTreeDesign");
	}
}
