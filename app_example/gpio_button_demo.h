#ifndef _GPIO_BUTTON_DEMO_H_
#define _GPIO_BUTTON_DEMO_H_

#include "gpio_api.h"   // mbed
#include "gpio_irq_api.h"  
#include "ameba_soc.h"
#include "device.h"
#include "os_wrapper.h"
#include <stdio.h>
#include "platform_autoconf.h"
#include "FreeRTOS.h"
#include "task.h"
#include <semphr.h>


#ifndef NULL
#define NULL 0
#endif

//定义三个gpio对应的evb pin idex
#define LED1_PIN _PA_14
#define LED2_PIN _PA_15
#define LED3_PIN _PA_16

//定义一个按钮，实现对LED的手动控制
#define BUTTON_PIN _PA_30

#define LED_delay_time_ms               1000    //LED 闪烁间隔

void gpio_led_init(void);
void gpio_led_toggle(void);
void gpio_button_init(void);
void button_pressed(void);
void vButtonInterruptHandler(void);
void gpio_level_irq_handler(uint32_t id, uint32_t event);

#endif
