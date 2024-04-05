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
    //testSS
void app_main() {
    
    
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