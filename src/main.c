//TODO: find logic analyzer wtf, gotta analyze my signals G.
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

//TODO: UART send task has to be completed before executing. this is not done yet.
void task_uart_send() {
    while(1) {

    }
}

//In this task, we will attempt listening to a CAN signal and perhaps demodding it.
void can_listen() {
    twai_message_t message;
    while(1) {
        if(twai_receive(&message, pdMS_TO_TICKS(10000)) == ESP_OK) {
            printf("Message recieved\n");
        }
        else {
            printf("Message not received (probably not plugged in yet)\n");
        }

        printf("ID is %lu\n", message.identifier);
        if(!(message.rtr)) {
            for(int i = 0; i < message.data_length_code; i++) {
                printf("Data byte %d = %d\n", i, message.data[i]);
            }
        }
   vTaskDelay(pdMS_TO_TICKS(100));
   }
} //FIXME: This does not work with the current setup (Should not be CAN listen but instead OBD2 listen)

void app_main() {
    //Here we will use the document specific TWAI driver initialization to begin a driver for CAN communciation.
    twai_general_config_t g_config = TWAI_GENERAL_CONFIG_DEFAULT(GPIO_NUM_21, GPIO_NUM_22, TWAI_MODE_NO_ACK);
    twai_timing_config_t t_config = TWAI_TIMING_CONFIG_500KBITS();
    twai_filter_config_t f_config = TWAI_FILTER_CONFIG_ACCEPT_ALL();

    printf("Attempting TWAI driver, install code :%x\n", twai_driver_install(&g_config, &t_config, &f_config));
    printf("Attempting to start TWAI driver, start code :%x\n",   twai_start()); 

    //After reading more about the issue, I realized that the sparkfun board literally converts UART signals INTO OBD2 signals not CAN signals.
    //On that note, I will use the serial terminal to send and receive information from OBD2 until I can use CAN.
    
    //UART CONFIG
    const uart_port_t uart_num = UART_NUM_2; // TODO: gotta finish configuring UART driver and actually testing the UART to OBD2.

    uart_config_t uart_config = {
        .baud_rate = 115200,
    };


    xTaskCreate(can_listen, "can_listen", 2048, NULL, 1, NULL);
}