// Copyright 2023 QMK
// SPDX-License-Identifier: GPL-2.0-or-later

#include QMK_KEYBOARD_H

//layer names for each layer
enum layer_names{
    _DEFAULT,
    _CODE,
    _FUNCTION
};

//for layer switching
enum custom_keycodes{
    CYCLE_LAYER = SAFE_RANGE
}

bool process_record_user(uint16_t keycode, keyrecord_t *record) {
    if (!record->event.pressed) return true;

    switch (keycode) {
        case CYCLE_LAYER:
            switch (get_highest_layer(layer_state)) {
                case _DEFAULT:
                    layer_move(_CODE);
                    break;
                case _CODE:
                    layer_move(_FUNCTION);
                    break;
                case _FUNCTION:
                default:
                    layer_move(_DEFAULT);
                    break;
            }
            return false;
    }
    return true;
}

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
    /*
     * ┌───┬───┬───┬
     * │ 7 │ 8 │ 9 │
     * ├───┼───┼───┼
     * │ 4 │ 5 │ 6 │
     * ├───┼───┼───┼
     * │ 1 │ 2 │ 3 │
     * ├───┼───┼───┼
     * │ 0 │ . │   │
     * └───┴───┴───┴
     */
    [0] = LAYOUT(
        KC_P7,   KC_P8,   KC_P9,
        KC_P4,   KC_P5,   KC_P6,
        KC_P1,   KC_P2,   KC_P3,
        KC_P0,   KC_PDOT, CYCLE_LAYER
    ),
    [1] = LAYOUT(
        _______,   _______,   _______,
        _______,   _______,   _______,
        _______,   _______,   _______,
        _______,   _______,   _______
    ),
    [2] = LAYOUT(
        KC_F1,   KC_F2,   KC_F3,
        KC_F4,   KC_F5,   KC_F6,
        KC_F7,   KC_F8,   KC_F9,
        KC_F10,  KC_F11,  CYCLE_LAYER
    ),
};

//encoder stuff
const uint16_t PROGMEM encoder_map[][1][2] = {
    [0] = { ENCODER_CCW_CW(KC_VOLU, KC_VOLD) },
    [1] = { ENCODER_CCW_CW(KC_VOLU, KC_VOLD) },
    [2] = { ENCODER_CCW_CW(KC_VOLU, KC_VOLD) },
};


#ifdef OLED_ENABLE
oled_rotation_t oled_init_user(oled_rotation_t rotation){
    return OLED_ROTATION_90;
}

//draw to oled
bool oled_task_user(void){
    //SET CURSOR POSITION
    oled_set_cursor(0,1);

    //keyboard layer status
    oled_write_P(PSTR("Layer: "),false);

    //switch on current active layer
    switch(get_highest_layer(layer_state)){
        case _DEFAULT:
            oled_write("Main Layer", false);
            break;
        case _CODE:
            oled_write("Code Layer", false);
            break;
        case _FUNCTION:
            oled_write("Function Layer", false);
            break;
    }

    return false;
}

#endif