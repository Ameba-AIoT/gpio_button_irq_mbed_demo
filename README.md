* [中文版](./README_CN.md)

### RTL8721Dx GPIO Input (Button) Interrupt Controlling LED Example — mbed API(FreeRTOS)

🔹 This is an example demonstrating how to use the RTL8721Dx series SoC for LED control and button input interrupts.

- 📎 [Development Board Purchase Link](https://item.taobao.com/item.htm?id=904981157046)   |[📦 Amazon](https://www.amazon.com/-/zh/dp/B0FB33DT2C/)
- 📄 [Chip Details](https://aiot.realmcu.com/module/index.html)
- 📚 [GPIO Document](https://aiot.realmcu.com/latest/rtos/peripherals/gpio/index.html)

### Features

✅ Initialize GPIOs — PA14/PA15/PA16/PA30  
✅ After initialization, configure the GPIO ports to make the LEDs blink at fixed intervals.  
✅ When a button is pressed, all LEDs will illuminate until you release the button.  
✅ Added dual level-triggered interrupt on the gpio_button_demo basis, responding instantly to button press commands for more intuitive feedback.
✅ use mbed API

### set up the hardware environment
1️⃣ **Requirement Components**
   - 3 LEDs
    ⚠️ The EVB board has built-in LEDs, you can directly observe the effect.
   - a push button

2️⃣ **Connect wires**
   - Connect a push button to 
   ` BUTTON_PIN (_PA_30)` and  ⚠️ `VDD33`
   - Connect LEDs to 
      - `LED1_PIN(_PA_14)//Green`   
      - `LED2_PIN(_PA_15)//Red` 
      - `LED3_PIN(_PA_16)//Blue` 
      - and `GND`

### Quick Start

1️⃣ **Select SDK Env**
   - Set `env.sh` (`env.bat`) path: `source {sdk}/env.sh`
   - Replace `{sdk}` with the absolute path to the [ameba-rtos SDK](https://github.com/Ameba-AIoT/ameba-rtos) root directory.

2️⃣ **Build**
   ```bash
   source env.sh
   ameba.py build
   ```

3️⃣ **Flash**
   ```bash
   ameba.py flash --p COMx --image km4_boot_all.bin 0x08000000 0x8014000 --image km0_km4_app.bin 0x08014000 0x8200000
   ```
   ⚠️ Note: Pre-compiled bin files provided in the project directory can also be flashed as follows:
   ```bash
   ameba.py flash --p COMx --image ../km4_boot_all.bin 0x08000000 0x8014000 --image ../km0_km4_app.bin 0x08014000 0x8200000
   ```

4️⃣ **Monitor**
   -  `ameba.py monitor --port COMx --b 1500000`

5️⃣ **Press RESET Button on the EVB Board and observe log output**


---

### Log Example

```bash
log：
15:43:48.736  ROM:[V1.1]
15:43:48.736  FLASH RATE:1, Pinmux:1
15:43:48.736  IMG1(OTA1) VALID, ret: 0
15:43:48.752  IMG1 ENTRY[f80078d:0]
15:43:48.752  [BOOT-I] KM4 BOOT REASON 0: Initial Power on
15:43:48.752  [BOOT-I] KM4 CPU CLK: 240000000 Hz
15:43:48.752  [BOOT-I] KM0 CPU CLK: 96000000 Hz
15:43:48.752  [BOOT-I] PSRAM Ctrl CLK: 240000000 Hz 
15:43:48.754  [BOOT-I] IMG1 ENTER MSP:[30009FDC]
15:43:48.754  [BOOT-I] Build Time: Jan 23 2026 11:08:33
15:43:48.754  [BOOT-I] IMG1 SECURE STATE: 1
15:43:48.754  [FLASH-I] FLASH CLK: 80000000 Hz
15:43:48.754  [FLASH-I] Flash ID: 85-20-16 (Capacity: 32M-bit)
15:43:48.754  [FLASH-I] Flash Read 4IO
15:43:48.754  [FLASH-I] FLASH HandShake[0x2 OK]
15:43:48.754  [BOOT-I] KM0 XIP IMG[0c000000:79e0]
15:43:48.754  [BOOT-I] KM0 SRAM[20068000:860]
15:43:48.754  [BOOT-I] KM0 PSRAM[0c008240:20]
15:43:48.754  [BOOT-I] KM0 ENTRY[20004d00:60]
15:43:48.754  [BOOT-I] KM4 XIP IMG[0e000000:18040]
15:43:48.754  [BOOT-I] KM4 SRAM[2000b000:480]
15:43:48.754  [BOOT-I] KM4 PSRAM[0e0184c0:20]
15:43:48.754  [BOOT-I] KM4 ENTRY[20004d80:40]
15:43:48.754  [BOOT-I] IMG2 BOOT from OTA 1, Version: 1.1 
15:43:48.768  [BOOT-I] Image2Entry @ 0xe0078ad ...
15:43:48.768  [APP-I] [KM4 APLOCKS-I]P START  KM0 ini
15:43:48.768  [APP-It_retarg] VTOR: et_locks30007000, VTOR_N
15:43:48.768  S:30007000
15:43:48.768  [APP-I] VTOR: 30007000, VTOR_NS:30007000
15:43:48.768  [APP-I] IMG2 [SECURE SMAIN-I] TATE: 1
15:43:48.768  IWDG refresh on!
15:43:48.768  [MAIN-I] KM0 OS START [
15:43:48.768  CLK-I] [CAL4M]: delta:0 target:320 PPM: 0 PPM_Limit:30000 
15:43:48.768  [CLK-I] [CAL131K]: delta:7 target:2441 PPM: 2867 PPM_Limit:30000 
15:43:48.768  [LOCKS-I] KM4 init_retarget_locks
15:43:48.768  [APP-I] BOR arises when supply voltage decreases under 2.57V and recovers above 2.7V.
15:43:48.768  [MAIN-I] KM4 MAIN 
15:43:48.768  [VER-I] AMEBA-RTOS SDK VERSION: 1.2.0
15:43:48.768  [MAIN-I] File System Init Success 
15:43:48.792  [app_main-I] gpio_led_demo start!
15:43:49.283  gpio_led_setup ready!
15:43:49.283  [app_main-I] gpio_button_init start!
15:43:49.283  SWD PAD Port0_Pin30 is configured to funcID [MAIN-I] KM4 START SCHEDULER 
15:43:51.819  The button_30 is pressed.
15:43:51.819  interupt #3
15:43:52.163  The button_30 is released.
15:43:52.163  ==> Button pressed count:1
15:43:55.157  The button_30 is pressed.
15:43:55.157  interupt #3
15:43:55.425  The button_30 is released.
15:43:55.425  ==> Button pressed count:2
15:43:57.924  The button_30 is pressed.
15:43:57.924  interupt #2
15:43:58.085  The button_30 is released.
15:43:58.085  ==> Button pressed count:3
15:44:02.026  ==> LED toggle count:1
15:44:05.048  ==> LED toggle count:2
15:44:05.709  The button_30 is pressed.
15:44:05.709  interrupt #1
15:44:05.940  The button_30 is released.
15:44:05.940  ==> Button pressed count:4
15:44:09.812  ==> LED toggle count:3
15:44:11.464  The button_30 is pressed.
15:44:11.464  interupt #2
15:44:11.733  The button_30 is released.
15:44:11.733  ==> Button pressed count:5
15:44:14.499  The button_30 is pressed.
15:44:14.499  interupt #2
15:44:15.610  ==>Button30 is pressed and not released!
15:44:16.611  ==>Button30 is pressed and not released!
15:44:17.611  ==>Button30 is pressed and not released!
15:44:18.612  ==>Button30 is pressed and not released!
15:44:19.054  The button_30 is released.
15:44:19.054  ==> Button pressed count:6
15:44:21.644  The button_30 is pressed.
15:44:21.644  interupt #3
15:44:22.743  ==>Button30 is pressed and not released!
15:44:23.745  ==>Button30 is pressed and not released!
15:44:24.745  ==>Button30 is pressed and not released!
15:44:25.736  ==>Button30 is pressed and not released!
15:44:25.924  The button_30 is released.
15:44:25.924  ==> Button pressed count:7
15:44:29.735  ==> LED toggle count:4


```# gpio_button_irq_mbed_demo
