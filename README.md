# XboxPlayground
XboxPlayground is a minimal Xbox 360 application I use as a test playground.

## Why?
While doing Xbox 360 development (especially on [Hayzen](https://github.com/ClementDreptin/Hayzen)), the workflow is a little bit tedious. I have to compile the code, deploy it to the console, unload then reload the module, and restart the game I'm currently working on.
Having a standalone playground test allows me to quickly iterate, I can just launch the build and the binary will be deployed to the console and launched automatically.
Not having to rely on a separate game also allows me launch the playground in an emulator ([Xenia](https://xenia.jp)), so I don't even need to have my console with me!

## Installation

### Requirements
- Having the Xbox 360 Software Development Kit installed
- Having a Powershell execution policy that allows to run scripts. Check the [Microsoft documentation](https://learn.microsoft.com/en-us/powershell/module/microsoft.powershell.core/about/about_execution_policies) for details.

### Building
- Visual Studio 2019 and prior: Open `XboxPlayground.sln` in Visual Studio and build it.
- Visual Studio 2022: You can't build with the 64-bit version of MSBuild so you'll need to run the 32-bit version manually. Open a developer powershell in Visual Studio (`View > Terminal`) and run the following commands:
    ```PS1
    # Create an alias to the 32-bit version of MSBuild named msbuild
    Set-Alias msbuild <path_vs2022>\MSBuild\Current\Bin\MSBuild.exe
    ```

To build XboxPlayground, deploy it to the console and launch it there, start a build with the `Release` configuration, either through the Visual Studio interface or with the following command:
```PS1
# Equivalent to msbuild /p:Configuration=Release
msbuild
```
To build XboxPlayground and run it in Xenia, start a build with the `Xenia` configuration, either through the Visual Studio interface or with the following command (Xenia will be downloaded automatically the first time you run the command):
```PS1
msbuild /p:Configuration=Xenia
```
