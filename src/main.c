#include <stdio.h>
#include "esp_log.h"
#include "freertos/FreeRTOS.h"
#include "freertos/timers.h"
#include "freertos/task.h"
#include "driver/gpio.h"
#include "driver/uart.h"
#include "driver/twai.h"

#include "esp_log.h"

//These pins will be used to interface to the car's can bus
#define PIN_CAN_HIGH 5


void task() {
    for(size_t i = 0; i < 5; i++) {
        printf("task %d: %lu\n", i, xTaskGetTickCount() * portTICK_PERIOD_MS);
        vTaskDelay(20 / portTICK_PERIOD_MS);
    }
    vTaskDelete(NULL);
}

//In this task, we will attempt listening to a CAN signal and perhaps demodding it.
void can_listen() {
    

}

void app_main() {
    //Here we will use the document specific TWAI driver initialization to begin a driver for CAN communciation.
    twai_general_config_t g_config = TWAI_GENERAL_CONFIG_DEFAULT(GPIO_NUM_10, GPIO_NUM_9, TWAI_MODE_LISTEN_ONLY);
    twai_timing_config_t t_config = TWAI_TIMING_CONFIG_500KBITS();
    twai_filter_config_t f_config = TWAI_FILTER_CONFIG_ACCEPT_ALL();

    printf("Attempting TWAI driver, install code :%x\n", twai_driver_install(&g_config, &t_config, &f_config));
    printf("Attempting to start TWAI driver, start code :%x\n",   twai_start()); 
    
    gpio_set_direction(PIN_CAN_HIGH, GPIO_MODE_INPUT);
    // int count = 0;
    // while(true) {
    //     ESP_LOGI("QEMU", "running on QEMU count %d", count++);
    //     vTaskDelay(pdMS_TO_TICKS(1000));
    // }
    printf("\nTimer output in milliseconds program initiation: %lu\n\n", xTaskGetTickCount()* portTICK_PERIOD_MS);
    xTaskCreate(task, "mytask", 2048, NULL, 1, NULL);

    printf("\nProgram completion: %lu\n", xTaskGetTickCount()* portTICK_PERIOD_MS);
}