/**
 * Copyright (c) 2020 Raspberry Pi (Trading) Ltd.
 *
 * SPDX-License-Identifier: BSD-3-Clause
 */

#include <stdio.h>
#include "pico/stdlib.h"

#define IR_IN_PIN 8
#define BUFFER_SIZE 1024

int main()
{
    stdio_init_all();

    printf("initialize\r\n");

    gpio_init(IR_IN_PIN);
    gpio_set_dir(IR_IN_PIN, GPIO_IN);

    gpio_pull_up(IR_IN_PIN);

    while (true)
    {
        run();
    }
}

int run()
{

    u_int32_t buffer[BUFFER_SIZE];

    memset(buffer, 0, sizeof(buffer));

    printf("waiting next start...\r\n");

    u_int32_t prev = time_us_32();
    while (gpio_get(IR_IN_PIN) == 1)
    {
        u_int32_t now = time_us_32();
        if (now - prev > 1000000)
        {
            bool v = gpio_get(IR_IN_PIN);
            printf(".\n", v);
            prev = now;
        }
    }
    buffer[0] = time_us_32();
    bool running = true;

    for (int i = 1; i < BUFFER_SIZE && running; i++)
    {
        while (gpio_get(IR_IN_PIN) == 0)
            ;

        prev = time_us_32();
        buffer[i] = prev;
        i++;

        while (gpio_get(IR_IN_PIN) == 1)
        {
            if (time_us_32() - prev > 1000000)
            {
                printf("done\n");
                running = false;
                break;
            }
        }

        buffer[i] = time_us_32();
    }

    printf("pulse = [");
    for (int i = 1; i < BUFFER_SIZE; i++)
    {
        if (buffer[i] == 0)
        {
            break;
        }
        if (i > 1)
        {
            printf(",");
        }
        printf("%d", buffer[i] - buffer[i - 1]);
    }
    printf("]\r\n");
    sleep_ms(1000);
}