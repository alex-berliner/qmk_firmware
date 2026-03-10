# Custom ploopy build
This is a custom firmware build for the Ploopy touchpad that provides a "reboot to bootloader" feature along with an extended mouse sensitivity option. It currently uses VIA to control the settings.

## Setup
Install the via desktop app. When you open it you should see this screen.
![](assets/1%20-%20starts%20out%20like%20this.png)

Click the cog icon on the top right to go to the settings menu. Enable the toggle for "Show Design Tab".
![](assets/2%20-%20go%20to%20settings%20and%20click%20show%20design%20tab.png)

Go to the Design tab and click Load.
![](assets/3%20-%20go%20to%20design%20tab%20and%20click%20load.png)

Provide the included via_layout.json file. Current bug: You must load the json twice in a row or it will not work!
![](assets/4%20-%20load%20the%20included%20json%20twice.png)

Click on the Configure tab on the top, then click on the Display tab on the bottom left.

Here you you may change the sensitivity and reboot the device into bootloader.
![](assets/5%20-%20go%20back%20to%20configure%20and%20click%20display%20on%20the%20left.png)

When you reboot the device into bootloader, it will reboot and present itself as a mass storage device called RPI-RP2. To update the device, copy the included .uf2 firmware file to RPI-RP2. The device will reboot automatically with the new firmware installed.
![](assets/6%20-%20to%20reflash%2C%20copy%20uf2%20to%20the%20drive%20that%20appears.png)


## Compilation

