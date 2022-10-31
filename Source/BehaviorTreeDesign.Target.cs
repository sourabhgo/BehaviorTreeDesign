using UnrealBuildTool;
using System.Collections.Generic;

public class BehaviorTreeDesignTarget : TargetRules
{
	public BehaviorTreeDesignTarget(TargetInfo Target) : base(Target)
	{
		Type = TargetType.Game;
		ExtraModuleNames.Add("BehaviorTreeDesign");
	}
}
