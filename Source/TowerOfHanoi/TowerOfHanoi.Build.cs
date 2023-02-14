using UnrealBuildTool;

public class TowerOfHanoi : ModuleRules {
	public TowerOfHanoi(ReadOnlyTargetRules Target) : base(Target) {
		PCHUsage = PCHUsageMode.UseExplicitOrSharedPCHs;
	
		PublicDependencyModuleNames.AddRange(new string[] { "Core", "CoreUObject", "Engine", "InputCore", "EnhancedInput", "AIModule", "NavigationSystem", "UMG", "Niagara" });

		PrivateDependencyModuleNames.AddRange(new string[] {  });
	}
}
