
#include QMK_KEYBOARD_H

// Layer names
enum {
  // - Base layer:
  _BASE,
  // - Symbols, numbers, and functions:
  _FN,
  // - Alternate Function layer:
  _LN
};

enum {
  TD_CTRL_SUPER_ALT = 0,
  TD_SCLN_ENTER,
  TD_RESET
};

void ctrl_super_alt_finished (qk_tap_dance_state_t *state, void *user_date) {
  switch (state->count) {
    case 1:
      register_code (KC_LCTRL);
      break;
    case 2:
      register_code (KC_LCTRL);
      register_code (KC_LGUI);
      break;
    case 3:
      register_code (KC_LCTRL);
      register_code (KC_LALT);
      break;
    default:
      break;
  }
}

void ctrl_super_alt_reset (qk_tap_dance_state_t *state, void *user_date) {
  switch (state->count) {
    case 1:
      unregister_code (KC_LCTRL);
      break;
    case 2:
      unregister_code (KC_LCTRL);
      unregister_code (KC_LGUI);
      break;
    case 3:
      unregister_code (KC_LCTRL);
      unregister_code (KC_LALT);
      break;
    default:
      break;
  }
}

qk_tap_dance_action_t tap_dance_actions[] = {
  [TD_CTRL_SUPER_ALT] = ACTION_TAP_DANCE_FN_ADVANCED(NULL, ctrl_super_alt_finished, ctrl_super_alt_reset),
  [TD_SCLN_ENTER] = ACTION_TAP_DANCE_DOUBLE(KC_SCLN, KC_ENT),
  [TD_RESET] = ACTION_TAP_DANCE_DOUBLE(KC_TRNS, RESET)
};

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {

  [_BASE] = LAYOUT_split_space_base(
    KC_1,   KC_2,    KC_3,    KC_4,    KC_5,    KC_6,    KC_7,    KC_8,    KC_9,             KC_0,
    KC_Q,   KC_W,    KC_E,    KC_R,    KC_T,    KC_Y,    KC_U,    KC_I,    KC_O,             KC_P,
    KC_A,   KC_S,    KC_D,    KC_F,    KC_G,    KC_H,    KC_J,    KC_K,    KC_L,          TD(TD_SCLN_ENTER),
    KC_Z,   KC_X,    KC_C,    KC_V,    KC_B,    KC_N,    KC_M,    KC_COMM, KC_DOT,         KC_SLSH,
          TD(TD_CTRL_SUPER_ALT),  KC_LSHIFT,  LT(_FN, KC_SPACE),   KC_BSPC
  ),

  [_FN] = LAYOUT_split_space_base(
    KC_F1,   KC_F2,   KC_F3,   KC_F4,    KC_F5,   KC_F6,   KC_F7,        KC_F8,   KC_F9,       KC_F10,
    KC_ESC,  KC_HOME, KC_UP,   KC_END,   KC_PGUP, KC_TRNS, TD(TD_RESET), KC_TRNS, KC_TRNS,     KC_BSLS,
    KC_TAB,  KC_LEFT, KC_DOWN, KC_RIGHT, KC_PGDN, KC_TRNS, KC_GRV,  KC_LBRC, KC_RBRC,          KC_QUOT,
    KC_TRNS, KC_TRNS, KC_CAPS, KC_TRNS,  KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_MINS,          KC_EQL,
          TD(TD_CTRL_SUPER_ALT),  KC_LSHIFT,  LT(_FN, KC_SPACE),   KC_DEL
  ), 

  [_LN] = LAYOUT_split_space_base(
    KC_TRNS,   KC_F1,   KC_F2,  KC_F3,    KC_TRNS,    KC_TRNS,   KC_TRNS,    KC_7,    KC_8,    KC_9,
    KC_TRNS,   KC_F4,   KC_F5,  KC_F6,    KC_TRNS,    KC_TRNS,   KC_TRNS,    KC_4,    KC_5,    KC_6,
    KC_TRNS,   KC_F7,   KC_F8,  KC_F9,    KC_TRNS,    KC_TRNS,   KC_TRNS,    KC_1,    KC_2,    KC_3,
    KC_TRNS,   KC_F10,  KC_F11, KC_F12,   KC_TRNS,    KC_TRNS,   KC_TRNS,    KC_TRNS, KC_0,    KC_TRNS,
          TD(TD_CTRL_SUPER_ALT),  KC_LSHIFT,  LT(_FN, KC_SPACE),   KC_DEL
  )
};
