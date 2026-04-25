# XboxPlayground

Minimal Xbox 360 application I use as a test playground.

## Why?

While doing Xbox 360 development (especially on [Hayzen](https://github.com/ClementDreptin/Hayzen)), the workflow is a little bit tedious. I have to compile the code, deploy it to the console, unload then reload the module, and restart the game I'm currently working on.
Having a standalone playground test allows me to quickly iterate, I can just launch the build and the binary will be deployed to the console and launched automatically.
Not having to rely on a separate game also allows me launch the playground in an emulator ([Xenia](https://xenia.jp)), so I don't even need to have my console with me!

## Building

### Requirements

- Having the Xbox 360 Software Development Kit (XDK) installed.
- Xbox 360 Neighborhood set up with your RGH/Jtag/Devkit registered as the default console (only necessary if you wan't to deploy to your console automatically).

### Visual Studio 2010

Open `XboxPlayground.sln` in Visual Studio.

### Any other environment

Xbox 360 projects can't be built with the 64-bit version of MSBuild, you need to run the 32-bit version. You can make yourself an alias for convenience:

```PS1
# Create an alias to the 32-bit version of MSBuild named msbuild
# The default installation path of VS2026 is C:\Program Files\Microsoft Visual Studio\18\Community
Set-Alias msbuild "<path_vs2026>\MSBuild\Current\Bin\MSBuild.exe"
```

To debug XboxPlayground, you need to build and run the debugger from Visual Studio 2010.

To build XboxPlayground in release mode, deploy it to the console and launch it there, start a release build, either through the Visual Studio interface or with the following command:

```PS1
msbuild /p:Configuration=Release
```

To build XboxPlayground and run it in Xenia, start a build with the `Xenia` configuration, either through the Visual Studio interface or with the following command (Xenia will be downloaded automatically the first time you run the command):

```PS1
msbuild /p:Configuration=Xenia
```
