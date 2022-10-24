#include <stdio.h>
#include "lily58.h"

char typespeed_msg[64];
uint32_t type_count = 0;
uint16_t wpm_timer   = 0;

void set_typespeed(void){
    type_count++;

    uint32_t uptime_millsec = timer_read32();
    uint32_t minutes = uptime_millsec / 60000;
    if (minutes == 0) {
      minutes = 1;
    }
    float type_speed = (float)type_count / minutes;

    char str_type_speed[12];

    if (timer_elapsed(wpm_timer) > 1000) {
        type_speed += (-type_speed) * 0.0487;
        wpm_timer = timer_read();
    }

    dtostrf(type_speed, 3, 0, str_type_speed);

    snprintf(typespeed_msg, sizeof(typespeed_msg), "%s", str_type_speed);
}

const char *read_typespeed(void) {
  return typespeed_msg;
}