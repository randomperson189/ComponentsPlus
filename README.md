<img width="463" height="139" alt="ComponentsPlus_logo" src="https://github.com/user-attachments/assets/cc9e68ee-f795-4780-8762-2626969f22b2" />
<br>
Components+ is a plugin for CryEngine 5.7 that adds more functionality to it's ECS &amp; Schematyc system

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

## Credits
[RandomPerson189](https://github.com/randomperson189) - Creating the plugin and most the code

[PixelAZ](https://github.com/77pixelAZ) - Designing the plugin logo
