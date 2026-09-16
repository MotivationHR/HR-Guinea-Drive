using UnrealBuildTool;
using System.Collections.Generic;

public class HRGuineaDriveEditorTarget : TargetRules
{
    public HRGuineaDriveEditorTarget(TargetInfo Target) : base(Target)
    {
        Type = TargetType.Editor;
        DefaultBuildSettings = BuildSettingsVersion.Latest;
        IncludeOrderVersion = EngineIncludeOrderVersion.Latest;
        ExtraModuleNames.Add("HRGuineaDrive");
    }
}