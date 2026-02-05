#include "gpio_button_demo.h"


//定义一个支持内部中断的button gpio
gpio_irq_t button_gpio;
//定义三个gpio给LED使用
gpio_t led1_gpio;
gpio_t led2_gpio;
gpio_t led3_gpio;
rtos_sema_t xButtonSemaphore = NULL;

uint button_press_cnt = 0;
int current_level = IRQ_HIGH;   //button按下为high


void gpio_led_init()
{    
     //初始化LED 对应的GPIO io   
    gpio_init(&led1_gpio, LED1_PIN);
    gpio_init(&led2_gpio, LED2_PIN);
    gpio_init(&led3_gpio, LED3_PIN);

    //GPIO mode == out
    gpio_dir(&led1_gpio, PIN_OUTPUT); 
    gpio_dir(&led2_gpio, PIN_OUTPUT); 
    gpio_dir(&led3_gpio, PIN_OUTPUT);    

    // No pull
    gpio_mode(&led1_gpio, PullNone);
    gpio_mode(&led2_gpio, PullNone);
    gpio_mode(&led3_gpio, PullNone);
    
    //LED 全部亮一次后再全灭
    gpio_direct_write(&led1_gpio, 1);
    gpio_direct_write(&led2_gpio, 1);
    gpio_direct_write(&led3_gpio, 1);
    rtos_time_delay_ms(500);
    gpio_direct_write(&led1_gpio, 0);
    gpio_direct_write(&led2_gpio, 0);
    gpio_direct_write(&led3_gpio, 0); 
    printf("gpio_led_setup ready!\r\n");
    return;
}


void gpio_level_irq_handler(uint32_t id, uint32_t event)
{
    UNUSED(event);
	uint32_t *level = (uint32_t *) id;
    rtos_sema_take(xButtonSemaphore, 0xFFFFFFFF);   

	// Disable level irq because the irq will keep triggered when it keeps in same level.
	gpio_irq_disable(&button_gpio);

	// make some software de-bounce here if the signal source is not stable.

	if (*level == IRQ_LOW) {        
		printf("The button_%lu is released.\r\n", (uint32_t)BUTTON_PIN);

		// Change to listen to high level event
		*level = IRQ_HIGH;
		gpio_irq_set(&button_gpio, IRQ_HIGH, 1);		
        //rtos_sema_take(xButtonSemaphore, 0xFFFFFFFF);        
    
        button_press_cnt ++;        
        printf("==> Button pressed count:%d\r\n", button_press_cnt); 
	} 
    else if (*level == IRQ_HIGH) {
		printf("The button_%lu is pressed.\r\n", (uint32_t)BUTTON_PIN);

		// Change to listen to low level event
		*level = IRQ_LOW;
		gpio_irq_set(&button_gpio, IRQ_LOW, 1);	
        rtos_sema_give(xButtonSemaphore);
	}
	gpio_irq_enable(&button_gpio);
}


/**
  * @brief  Initialize the GPIO device's interrupt mode, including mode, trigger and polarity registers.
  * @param  obj: GPIO irq object defined in application software.
  * @param  pin: PinName according to pinmux spec.
  * @param  handler: Interrupt handler to be assigned to the specified pin.
  * @param  id: Handler parameter.
  * @return 0 if initialization is ok.

int gpio_irq_init(gpio_irq_t *obj, PinName pin, gpio_irq_handler handler, uint32_t id)
  */

void gpio_button_init()
{
     // 创建二值信号量  
    rtos_sema_create_binary(&xButtonSemaphore);	
	if (xButtonSemaphore == NULL ) {
		printf("Create Semaphore failed.\n");
        return;
	}
    
    // configure level trigger handler
	gpio_irq_init(&button_gpio, BUTTON_PIN, gpio_level_irq_handler, (uint32_t)&current_level);
	gpio_irq_pull_ctrl(&button_gpio, GPIO_PuPd_UP); //*		@arg  PullNone: HighZ, user can input high or low with this pin. GPIO_PuPd_NOPULL
                                                    //  *		@arg  PullDown: Pull down. GPIO_PuPd_DOWN
                                                    //   *		@arg  PullUp: Pull up. GPIO_PuPd_UP
	gpio_irq_set(&button_gpio, IRQ_FALL_RISE, 1); //for dual-edge trigger irq interrupt

	gpio_irq_enable(&button_gpio); 
    return;
}

void button_pressed()
{       
    gpio_direct_write(&led1_gpio, 0);
    gpio_direct_write(&led2_gpio, 0);
    gpio_direct_write(&led3_gpio, 0);
    rtos_time_delay_ms(100);   //亮灭一次，显示区分
    gpio_direct_write(&led1_gpio, 1);
    gpio_direct_write(&led2_gpio, 1);
    gpio_direct_write(&led3_gpio, 1); 
    //rtos_time_delay_ms(1000);   
    return;
}

void gpio_led_toggle()
{    
    uint i = 0;
    uint tmp = 0; 
    while (1)
    {        
        //默认无按键输入，led toggle显示
        while (1)
        {                        
            //led toggle，间隔1s切换一次gpio
            gpio_direct_write(&led1_gpio, 1);
            if (rtos_sema_take(xButtonSemaphore, LED_delay_time_ms) == 0)
            {
                printf("interrupt #1\r\n");
                break;
            }         

            gpio_direct_write(&led1_gpio, 0);
            gpio_direct_write(&led2_gpio, 1);
            if (rtos_sema_take(xButtonSemaphore, LED_delay_time_ms) == 0)
            {
                printf("interupt #2\r\n");
                break;
            }


            gpio_direct_write(&led2_gpio, 0);
            gpio_direct_write(&led3_gpio, 1);
            if (rtos_sema_take(xButtonSemaphore, LED_delay_time_ms) == 0)
            {
                printf("interupt #3\r\n");
                break;
            }

            gpio_direct_write(&led3_gpio, 0);
            printf("==> LED toggle count:%d\r\n", ++i);   
        }
        //监测到button irq后，进入button循环，直到button release
        while (1)
        {        
            if (tmp == button_press_cnt)
            {
                button_pressed(); 
                tmp ++;        
            }
            while (1)//button按住不放
            {
                rtos_time_delay_ms(LED_delay_time_ms);       //button 控制LED 至少亮1s
                if (tmp != button_press_cnt)
                {   
                    printf("==>Button%lu is pressed and not released!\r\n", (uint32_t)BUTTON_PIN);                   
                }                
                else
                    break;                         
            }
            break;         
        }    
    }
    rtos_task_delete(NULL);
}