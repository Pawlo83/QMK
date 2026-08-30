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

TAP_DANCE_ENABLE = yes

*/

#include QMK_KEYBOARD_H
#include "keymap_polish.h"
#include "local_functions.h"

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
    [0] = LAYOUT_ortho_3x10_6(
        TD(TD_Q_ESC), PL_W,         PL_E,    PL_R,    PL_T,       PL_Y,          PL_U,          PL_I,    PL_O,   PL_P,
        PL_A,         PL_S,         PL_D,    PL_F,    PL_G,       PL_H,          PL_J,          PL_K,    PL_L,   KC_BSPC,
        LSFT_T(PL_Z), LALT_T(PL_X), PL_C,    PL_V,    PL_B,       PL_N,          PL_M,          PL_COMM, PL_DOT, RSFT_T(PL_SLSH),
                                    KC_LCTL, KC_LGUI, KC_SPC,     LT(1, KC_ENT), LT(2, KC_TAB), KC_RALT
    ),
    [1] = LAYOUT_ortho_3x10_6(
        KC_1,    KC_2,     KC_3,     KC_4,    KC_5,        KC_6,    KC_7,    KC_8,    KC_9,    KC_0,
        KC_LBRC, KC_QUOT,  KC_DQUO,  KC_RBRC, KC_SCLN,     KC_CAPS, KC_LEFT, KC_UP,   KC_DOWN, KC_RGHT,
        KC_LSFT, MO(3),    KC_GRAVE, PL_MINS, PL_EQL,      KC_PAUS, KC_VOLD, KC_MUTE, KC_VOLU, RSFT_T(KC_BSLS),
                           KC_LCTL,  KC_LGUI, KC_TRNS,     KC_TRNS, KC_TRNS, KC_DEL
    ),
    [2] = LAYOUT_ortho_3x10_6(
        KC_F1,   KC_F2,   KC_F3,   KC_F4,      KC_F5,           KC_F6,   KC_F7,   KC_F8,   KC_F9,   KC_F10,
        KC_LCBR, KC_LPRN, KC_RPRN, KC_RCBR,    PL_PIPE,         KC_PSCR, KC_HOME, KC_PGUP, KC_PGDN, KC_END,
        KC_LSFT, KC_F11,  KC_F12,  TD(TD_NOO), TD(TD_NOO),      KC_PAUS, KC_MPRV, KC_MPLY, KC_MNXT, KC_RSFT,
                          KC_LCTL, KC_LGUI,    KC_SPC,          KC_TRNS, KC_TRNS, KC_DEL
    ),
    [3] = LAYOUT_ortho_3x10_6(
        KC_ESC,  TD(TD_NOO), TD(TD_NOO),  TD(TD_NOO),   TD(TD_NOO),      TD(TD_NOO), TD(TD_NOO),     TD(TD_NOO),     TD(TD_NOO),     TD(TD_NOO),
        KC_LSFT, TD(TD_NOO), TD(TD_NOO),  TD(TD_NOO),   TD(TD_NOO),      TD(TD_NOO), TD(TD_NOO),     TD(TD_NOO),     TD(TD_NOO),     TD(TD_NOO),
        KC_LCTL, TD(TD_NOO), TD(TD_NOO),  TD(TD_NOO),   TD(TD_NOO),      TD(TD_NOO), TD(TD_AUDIO_S), TD(TD_AUDIO_H), TD(TD_AUDIO_G), KC_RSFT,
                             KC_TAB,      KC_LGUI,      KC_SPC,          TG(1),      TG(1),          TG(1)
    ),
    [4] = LAYOUT_ortho_3x10_6(
        KC_ESC,  PL_Q, PL_W,   PL_E,    PL_R,                     PL_Y,          PL_U,  PL_I,    PL_O,   PL_P,
        KC_LSFT, PL_A, PL_S,   PL_D,    PL_F,                     PL_H,          PL_J,  PL_K,    PL_L,   KC_BSPC,
        KC_LCTL, PL_Z, PL_X,   PL_C,    PL_V,                     PL_B,          PL_M,  PL_COMM, PL_DOT, RSFT_T(PL_SLSH),
                       KC_TAB, KC_LGUI, KC_SPC,                   LT(1, KC_ENT), TG(3), KC_PAUS
    )
};