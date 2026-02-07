/*
Copyright 2022 Joe Scotto
Copyright 2026 Pawlo83

This program is free software: you can redistribute it and/or modify
it under the terms of the GNU General Public License as published by
the Free Software Foundation, either version 2 of the License, or
(at your option) any later version.

This program is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the
GNU General Public License for more details.

You should have received a copy of the GNU General Public License
along with this program.  If not, see <http://www.gnu.org/licenses/>.
*/
#include QMK_KEYBOARD_H
#include "keymap_polish.h"

enum macro_keycodes {
    KC_ALT_TAB
};
bool process_record_user(uint16_t keycode, keyrecord_t *record){
    if (record->event.pressed){
        switch(keycode){
            case KC_ALT_TAB:
                register_code(KC_LALT);
                register_code(KC_TAB);
                unregister_code(KC_TAB);
                unregister_code(KC_LALT);
                break;
        }
    }
    return true;
}
void noo(tap_dance_state_t *state, void *user_data){
}
void run_nircmd_audio(const char *device_name) {
    SEND_STRING(SS_DOWN(X_LGUI) "r" SS_UP(X_LGUI));
    wait_ms(100);
    SEND_STRING("\"C:\\nircmd.exe\" setdefaultsounddevice \"");
    send_string(device_name);
    SEND_STRING("\" 1");
    SEND_STRING(SS_TAP(X_ENTER));
    wait_ms(200);
    SEND_STRING(SS_DOWN(X_LGUI) "r" SS_UP(X_LGUI));
    wait_ms(100);
    SEND_STRING("\"C:\\nircmd.exe\" setdefaultsounddevice \"");
    send_string(device_name);
    SEND_STRING("\" 2");
    SEND_STRING(SS_TAP(X_ENTER));
}
void audio_h(tap_dance_state_t *state, void *user_data) {
    run_nircmd_audio("Headset"); 
}
void audio_s(tap_dance_state_t *state, void *user_data) {
    run_nircmd_audio("Headphones"); 
}
void audio_g(tap_dance_state_t *state, void *user_data) {
    run_nircmd_audio("Speaker"); 
}
enum tapdances{
    TD_NOO,
    TD_Q_ESC,
    TD_AUDIO_H,
    TD_AUDIO_S,
    TD_AUDIO_G,
};
tap_dance_action_t tap_dance_actions[] = {
    [TD_NOO]=ACTION_TAP_DANCE_FN(noo),
    [TD_Q_ESC] = ACTION_TAP_DANCE_DOUBLE(PL_Q, KC_ESC),
    [TD_AUDIO_S] = ACTION_TAP_DANCE_FN(audio_s),
    [TD_AUDIO_H] = ACTION_TAP_DANCE_FN(audio_h),
    [TD_AUDIO_G] = ACTION_TAP_DANCE_FN(audio_g),
};

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
    [0] = LAYOUT_ortho_5x12(
        KC_ESC,     KC_1,    KC_2,       KC_3,     KC_4,    KC_5,    KC_6,    KC_7,           KC_8,           KC_9,           KC_0,    TD(TD_NOO),
        KC_TAB,     PL_Q,    PL_W,       PL_E,     PL_R,    PL_T,    PL_Y,    PL_U,           PL_I,           PL_O,           PL_P,    PL_QUOT,
        KC_CAPS,    PL_A,    PL_S,       PL_D,     PL_F,    PL_G,    PL_H,    PL_J,           PL_K,           PL_L,           PL_SCLN, KC_BSPC,
        KC_LSFT,    PL_Z,    PL_X,       PL_C,     PL_V,    PL_B,    PL_N,    PL_M,           PL_COMM,        PL_DOT,         PL_SLSH, KC_RSFT,
        KC_LCTL,    KC_LGUI, KC_LALT,    MO(2),    MO(1),   KC_SPC,  KC_SPC,  LT(1, KC_ENT),  LT(2, KC_TAB),  KC_RALT,        KC_RGUI, KC_RCTL
    ), 
    [1] = LAYOUT_ortho_5x12( 
        KC_ESC,     KC_F1,   KC_F2,      KC_F3,    KC_F4,   KC_F5,   KC_F6,   KC_F7,          KC_F8,          KC_F9,          KC_F10,  KC_F11,
        KC_TAB,     KC_LCBR, KC_LPRN,    KC_RPRN,  KC_RCBR, PL_PIPE, KC_PSCR, KC_MPRV,        KC_MPLY,        KC_MNXT,        KC_F12,  KC_DEL,
        TD(TD_NOO), KC_LBRC, KC_QUOT,    KC_DQUO,  KC_RBRC, KC_SCLN, KC_CAPS, KC_LEFT,        KC_UP,          KC_DOWN,        KC_RGHT, KC_BSPC,
        KC_LSFT,    TG(3),   TD(TD_NOO), KC_GRAVE, PL_MINS, PL_EQL,  KC_PAUS, KC_VOLD,        KC_MUTE,        KC_VOLU,        KC_BSLS, KC_LSFT,
        KC_LCTL,    KC_LGUI, KC_LALT,    KC_TRNS,  KC_TRNS, KC_SPC,  KC_SPC,  KC_TRNS,        KC_TRNS,        KC_RALT,        KC_RGUI, KC_RCTL
    ), 
    [2] = LAYOUT_ortho_5x12(
        KC_ESC,     KC_F1,   KC_F2,      KC_F3,    KC_F4,   KC_F5,   KC_F6,   KC_F7,          KC_F8,          KC_F9,          KC_F10,  KC_F11,
        KC_TAB,     KC_LCBR, KC_LPRN,    KC_RPRN,  KC_RCBR, PL_PIPE, KC_PSCR, TD(TD_AUDIO_S), TD(TD_AUDIO_H), TD(TD_AUDIO_G), KC_F12,  KC_DEL,
        TD(TD_NOO), KC_LBRC, KC_QUOT,    KC_DQUO,  KC_RBRC, KC_SCLN, KC_CAPS, KC_HOME,        KC_PAGE_UP,     KC_PAGE_DOWN,   KC_END,  KC_BSPC,
        KC_LSFT,    TG(3),   TD(TD_NOO), KC_GRAVE, PL_MINS, PL_EQL,  KC_PAUS, KC_VOLD,        KC_MUTE,        KC_VOLU,        KC_BSLS, KC_LSFT,
        KC_LCTL,    KC_LGUI, KC_LALT,    KC_TRNS,  KC_TRNS, KC_SPC,  KC_SPC,  KC_TRNS,        KC_TRNS,        KC_RALT,        KC_RGUI, KC_RCTL
    ), 
    [3] = LAYOUT_ortho_5x12( 
        KC_ESC,     KC_F1,   KC_F2,      KC_F3,    KC_F4,   KC_F5,   KC_F6,   KC_F7,          KC_F8,          KC_F9,          KC_PAUS, TG(3),
        KC_TAB,     PL_Q,    PL_W,       PL_E,     PL_R,    PL_T,    PL_Y,    PL_U,           PL_I,           PL_O,           PL_P,    PL_QUOT,
        KC_CAPS,    PL_A,    PL_S,       PL_D,     PL_F,    PL_G,    PL_H,    PL_J,           PL_K,           PL_L,           PL_SCLN, KC_BSPC,
        KC_LSFT,    PL_Z,    PL_X,       PL_C,     PL_V,    PL_B,    PL_N,    PL_M,           PL_COMM,        PL_DOT,         KC_UP,   KC_RSFT,
        KC_LCTL,    KC_LGUI, KC_LALT,    MO(1),    MO(1),   KC_SPC,  KC_SPC,  KC_ENT,         KC_TAB,         KC_LEFT,        KC_DOWN, KC_RIGHT
    )
};

