/*
	Copyright (C) 2024 Vizrt NDI AB. All rights reserved.

	This file and its use within a Product is bound by the terms of NDI SDK license that was provided 
	as part of the NDI SDK. For more information, please review the license and the NDI SDK documentation.
*/

using UnrealBuildTool;      // Required for all Build.cs files (provides 'ModuleRules', 'Target', etc.)
using System;               // Basic .NET system functionality (e.g., strings, IO)
using System.IO;            // For file path and file checking

public class NDI : ModuleRules
{
    public NDI(ReadOnlyTargetRules Target) : base(Target)
    {
        Type = ModuleType.External;

        if (Target.Platform == UnrealTargetPlatform.Win64)
        {
            PublicIncludePaths.Add(Path.Combine(ModuleDirectory, "Includes"));

            PublicAdditionalLibraries.Add(Path.Combine(ModuleDirectory, "Libraries/Win64", "Processing.NDI.Lib.x64.lib"));

            // Delay-load the DLL from the runtime directory (determined at runtime)
            PublicDelayLoadDLLs.Add("Processing.NDI.Lib.x64.dll");

            // Ensure that we define our c++ define
            PublicDefinitions.Add("NDI_SDK_ENABLED");
        }
        else if (Target.Platform == UnrealTargetPlatform.Android)
        {
           

            PrivateDependencyModuleNames.Add("Launch");

            string IncludePath = Path.Combine(ModuleDirectory, "Includes");
            PublicIncludePaths.Add(IncludePath);

            string LibPath = Path.Combine(ModuleDirectory, "Libraries", "Android");

            PublicAdditionalLibraries.Add(Path.Combine(LibPath, "arm64-v8a", "libndi.so"));
            PublicAdditionalLibraries.Add(Path.Combine(LibPath, "armeabi-v7a", "libndi.so"));

            RuntimeDependencies.Add(Path.Combine(LibPath, "arm64-v8a", "libndi.so"));
            RuntimeDependencies.Add(Path.Combine(LibPath, "armeabi-v7a", "libndi.so"));
            string PluginRoot = Path.GetFullPath(ModuleDirectory);
            string Arm64Path = Path.Combine(PluginRoot, "Libraries/Android/arm64-v8a/libndi.so");
            string Armv7Path = Path.Combine(PluginRoot, "Libraries/Android/armeabi-v7a/libndi.so");
            PublicDelayLoadDLLs.Add("libndi.so");
            AdditionalPropertiesForReceipt.Add("AndroidPlugin", Path.Combine(ModuleDirectory, "NDI_APL.xml"));
            PublicDefinitions.Add("NDI_SDK_ENABLED");
        }
        else if ((Target.Platform == UnrealTargetPlatform.Linux)
            || ((Target.Version.MajorVersion == 4) && (Target.Platform.ToString() == "LinuxAArch64"))
            || ((Target.Version.MajorVersion == 5) && (Target.Platform.ToString() == "LinuxArm64"))
            )
        {
            PublicIncludePaths.Add(Path.Combine(ModuleDirectory, "Includes"));

            PublicAdditionalLibraries.Add(Path.Combine(ModuleDirectory, "Libraries/Linux", "libndi.so"));
            RuntimeDependencies.Add(Path.Combine("$(BinaryOutputDir)", "libndi.so.6"), Path.Combine(ModuleDirectory, "Libraries/Linux", "libndi.so.6"));

            // Ensure that we define our c++ define
            PublicDefinitions.Add("NDI_SDK_ENABLED");
        }
    }
}
