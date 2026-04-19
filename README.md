# ComponentsPlus
Components+ is a plugin for CryEngine 5.7 that exposes more functions to it's ECS &amp; Schematyc system

## How to install the plugin to your project:

1. Download the files in this repository (either by cloing or via zip download)
2. Open the **bin** folder and then inside that, move the two folders called **win_x64** and **win_x64_release** into your CryEngine 5 project's **bin** folder (don't replace if prompted)
3. Open your CryEngine 5 project's **Game.cryproject** in a text editor and look for this line
```
{
  "guid": "",
  "type": "EType::Native",
  "path": "bin/win_x64/Game.dll"
}
```
4. Add a new entry underneath so that it now looks like this
```
{
  "guid": "",
  "type": "EType::Native",
  "path": "bin/win_x64/Game.dll"
},
{
  "guid": "",
  "type": "EType::Native",
  "path": "bin/win_x64/ComponentsPlus.dll"
}
```
