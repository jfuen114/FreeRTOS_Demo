#include <stdio.h>
#include "esp_log.h"
#include "freertos/FreeRTOS.h"
#include "freertos/timers.h"
#include "freertos/task.h"
#include "driver/gpio.h"

#include "esp_log.h"

void task() {
    for(size_t i = 0; i < 5; i++) {
        printf("task %d: %lu\n", i, xTaskGetTickCount() * portTICK_PERIOD_MS);
        vTaskDelay(20 / portTICK_PERIOD_MS);
    }
    vTaskDelete(NULL);
}
    //test
void app_main() {
    // char *ourTaskName = pcTaskGetName;
    // ESP_LOGI(ourTaskName, "Hello, World!");

    
    // int count = 0;
    // while(true) {
    //     ESP_LOGI("QEMU", "running on QEMU count %d", count++);
    //     vTaskDelay(pdMS_TO_TICKS(1000));
    // }
    printf("\nTimer output in milliseconds program initiation: %lu\n\n", xTaskGetTickCount()* portTICK_PERIOD_MS);

    xTaskCreate(task, "mytask", 2048, NULL, 1, NULL);

    printf("\nProgram completion: %lu\n", xTaskGetTickCount()* portTICK_PERIOD_MS);
}