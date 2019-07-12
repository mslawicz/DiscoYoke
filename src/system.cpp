/*
 * system.cpp
 *
 *  Created on: 10.07.2019
 *      Author: Marcin
 */


#include "system.h"
#include "timer.h"
//#include "display.h"
#include "stm32f4xx_hal.h"
#include "stm32f411e_discovery.h"

System::System() :
    testPin(TEST_PORT, TEST_PIN, GPIO_MODE_OUTPUT_PP),
    systemLED(LED4_GPIO_PORT, LED4_PIN, GPIO_MODE_OUTPUT_PP),   //green LED
    systemPushbutton(KEY_BUTTON_GPIO_PORT, KEY_BUTTON_PIN, GPIO_MODE_INPUT, GPIO_PULLUP)

{
    /* Reset of all peripherals, Initializes the Flash interface and the Systick. */
    HAL_Init();


    HAL_NVIC_SetPriorityGrouping(NVIC_PRIORITYGROUP_2);

    /* Configure the system clock */
    configClock();

    //pSpi3 = nullptr;
    //pConsole = nullptr;
    //pDisplay = nullptr;
}

System::~System()
{

}

/*
 * get the singleton instance
 * object constructor is executed in the first call
 */
System& System::getInstance(void)
{
    static System singleton;
    return singleton;
}

/*
 * configuration of system clocks
 */
void System::configClock(void)
{
    RCC_OscInitTypeDef RCC_OscInitStruct = {0};
    RCC_ClkInitTypeDef RCC_ClkInitStruct = {0};

    /** Configure the main internal regulator output voltage
    */
    __HAL_RCC_PWR_CLK_ENABLE();
    //__HAL_RCC_SYSCFG_CLK_ENABLE();
    __HAL_PWR_VOLTAGESCALING_CONFIG(PWR_REGULATOR_VOLTAGE_SCALE1);

    /* -1- Select HSI as system clock source to allow modification of the PLL configuration */
//    RCC_ClkInitStruct.ClockType = RCC_CLOCKTYPE_SYSCLK;
//    RCC_ClkInitStruct.SYSCLKSource = RCC_SYSCLKSOURCE_HSI;
//    if(HAL_RCC_ClockConfig(&RCC_ClkInitStruct, FLASH_LATENCY_1) != HAL_OK)
//    {
//    /* Initialization Error */
//      errorHandler();
//    }
    /* -2- Enable HSE Oscillator, select it as PLL source and finally activate the PLL */
    RCC_OscInitStruct.OscillatorType = RCC_OSCILLATORTYPE_HSE;
    RCC_OscInitStruct.HSEState = RCC_HSE_ON;
    RCC_OscInitStruct.PLL.PLLState = RCC_PLL_ON;
    RCC_OscInitStruct.PLL.PLLSource = RCC_PLLSOURCE_HSE;
    RCC_OscInitStruct.PLL.PLLM = 4;
    RCC_OscInitStruct.PLL.PLLN = 96;
    RCC_OscInitStruct.PLL.PLLP = RCC_PLLP_DIV2;
    RCC_OscInitStruct.PLL.PLLQ = 4;
    if (HAL_RCC_OscConfig(&RCC_OscInitStruct) != HAL_OK)
    {
      errorHandler();
    }

//    RCC_OscInitStruct.OscillatorType = RCC_OSCILLATORTYPE_HSI;
//    RCC_OscInitStruct.HSIState = RCC_HSI_ON;
//    RCC_OscInitStruct.HSICalibrationValue = RCC_HSICALIBRATION_DEFAULT;
//    RCC_OscInitStruct.PLL.PLLState = RCC_PLL_ON;
//    RCC_OscInitStruct.PLL.PLLSource = RCC_PLLSOURCE_HSI;
//    RCC_OscInitStruct.PLL.PLLM = 8;
//    RCC_OscInitStruct.PLL.PLLN = 192;
//    RCC_OscInitStruct.PLL.PLLP = RCC_PLLP_DIV4;
//    RCC_OscInitStruct.PLL.PLLQ = 8;
//    if (HAL_RCC_OscConfig(&RCC_OscInitStruct) != HAL_OK)
//    {
//      errorHandler();
//    }

    /* -3- Select the PLL as system clock source and configure the HCLK, PCLK1 and PCLK2 clocks dividers */
    RCC_ClkInitStruct.ClockType = RCC_CLOCKTYPE_HCLK|RCC_CLOCKTYPE_SYSCLK
                                |RCC_CLOCKTYPE_PCLK1|RCC_CLOCKTYPE_PCLK2;
    RCC_ClkInitStruct.SYSCLKSource = RCC_SYSCLKSOURCE_PLLCLK;
    RCC_ClkInitStruct.AHBCLKDivider = RCC_SYSCLK_DIV1;
    RCC_ClkInitStruct.APB1CLKDivider = RCC_HCLK_DIV2;
    RCC_ClkInitStruct.APB2CLKDivider = RCC_HCLK_DIV1;
    if (HAL_RCC_ClockConfig(&RCC_ClkInitStruct, FLASH_LATENCY_3) != HAL_OK)
    {
        errorHandler();
    }
    HAL_RCC_EnableCSS();
    GPIO(GPIOA, GPIO_PIN_8, GPIO_MODE_OUTPUT_PP, GPIO_SPEED_FREQ_VERY_HIGH, GPIO_AF0_MCO);
    HAL_RCC_MCOConfig(RCC_MCO1, RCC_MCO1SOURCE_HSE, RCC_MCODIV_4);
}

/*
 * user configuration
 */
void System::config(void)
{
    Timer::config();
//    pConsole = new Console;
//    pConsole->sendMessage(Severity::Info,LogChannel::LC_SYSTEM, "3d yoke program start");
    // SPI3 is used for display
//    pSpi3 = new SpiBus(SPI3);
//    pDisplay = new Display(SpiBus::pSpi3, DISPLAY_CS_PORT, DISPLAY_CS_PIN);
}

/*
 * clean up system before exit
 */
void System::terminate(void)
{
//    delete pDisplay;
//    delete pConsole;
//    delete pSpi3;
}

/*
 * blinks the system LED in 1 second interval
 */
void System::blinkSystemLED(void)
{
    static Timer ledTimer;
    if(ledTimer.elapsed(100000))
    {
        ledTimer.reset();
        systemLED.toggle();
    }
}
