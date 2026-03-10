// Copyright 2024 George Norton (@george-norton)
// SPDX-License-Identifier: GPL-2.0-or-later

#include QMK_KEYBOARD_H

#ifdef VIA_ENABLE
#    include "via.h"
#    include "bootloader.h"
#    include "digitizer.h"

// Custom values (Display → Pavonis). Channel 0.
#define PAVONIS_CUSTOM_CHANNEL        0
#define PAVONIS_CUSTOM_VALUE_DUMMY    1
#define PAVONIS_CUSTOM_VALUE_SENSITIVITY 2

static uint8_t pavonis_dummy_setting;

// Handle custom get/set/save for Pavonis menu (dummy toggle, sensitivity slider).
void via_custom_value_command_kb(uint8_t *data, uint8_t length) {
    uint8_t *command_id   = &(data[0]);
    uint8_t  channel_id   = data[1];
    uint8_t  value_id     = data[2];
    uint8_t *value_data   = &(data[3]);

    if (channel_id != PAVONIS_CUSTOM_CHANNEL) {
        *command_id = id_unhandled;
        return;
    }

    // SAVE (9) is sent per channel with no value_id; accept and no-op.
    if (*command_id == id_custom_save) {
        return;
    }

    if (value_id == PAVONIS_CUSTOM_VALUE_SENSITIVITY) {
        switch (*command_id) {
            case id_custom_get_value:
                value_data[0] = digitizer_get_sensitivity();
                break;
            case id_custom_set_value:
                digitizer_set_sensitivity(value_data[0]);
                break;
            default:
                *command_id = id_unhandled;
                break;
        }
        return;
    }

    if (value_id != PAVONIS_CUSTOM_VALUE_DUMMY) {
        *command_id = id_unhandled;
        return;
    }

    switch (*command_id) {
        case id_custom_get_value:
            value_data[0] = pavonis_dummy_setting;
            break;
        case id_custom_set_value:
            pavonis_dummy_setting = value_data[0];
            bootloader_jump(); // Toggle = "user wants to flash" → reboot to bootloader
            return;
        default:
            *command_id = id_unhandled;
            break;
    }
}

// Pavonis has no physical keys; treat any VIA keymap write as "user wants to flash" → reboot to bootloader.
bool via_command_kb(uint8_t *data, uint8_t length) {
    uint8_t command_id = data[0];
    if (command_id == id_dynamic_keymap_set_keycode || command_id == id_dynamic_keymap_reset || command_id == id_dynamic_keymap_set_buffer) {
        bootloader_jump();
        return true;
    }
    return false;
}
#endif

bool shutdown_kb(bool jump_to_bootloader) {
    if (!shutdown_user(jump_to_bootloader)) {
        return false;
    }

    if (jump_to_bootloader) {
        // Buzz to indicate the reboot to bootloader gesture was detected
        gpio_set_pin_output_push_pull(HAPTICS_PIN);
        gpio_write_pin_high(HAPTICS_PIN);
        wait_ms(50);
        gpio_write_pin_low(HAPTICS_PIN);
    }

    return true;
}
