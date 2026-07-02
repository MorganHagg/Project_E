using UnrealBuildTool;

public class Project_EEditor : ModuleRules
{
    public Project_EEditor(ReadOnlyTargetRules Target) : base(Target)
    {
        PCHUsage = PCHUsageMode.UseExplicitOrSharedPCHs;

        PublicDependencyModuleNames.AddRange(new string[]
            {
                "Core",
                "CoreUObject",
                "Engine",
                "UnrealEd",
                "PropertyEditor",
                "SlateCore",
                "Slate",
                "InputCore",
                "Project_E"
            });
    }
}