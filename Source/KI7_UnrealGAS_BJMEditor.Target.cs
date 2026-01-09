// Fill out your copyright notice in the Description page of Project Settings.

using UnrealBuildTool;
using System.Collections.Generic;

public class KI7_UnrealGAS_BJMEditorTarget : TargetRules
{
	public KI7_UnrealGAS_BJMEditorTarget(TargetInfo Target) : base(Target)
	{
		Type = TargetType.Editor;
		DefaultBuildSettings = BuildSettingsVersion.V5;

		ExtraModuleNames.AddRange( new string[] { "KI7_UnrealGAS_BJM" } );
	}
}
