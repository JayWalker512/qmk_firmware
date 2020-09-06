
#include QMK_KEYBOARD_H

// Layer names
enum {
  // - Base layer:
  _BASE,
  // - Symbols, numbers, and functions:
  _FN
};

enum tapdance_codes {
  TD_CTRL_SUPER_ALT = 0,
  TD_SCLN_ENTER,
  TD_RESET,
  TD_SHIFT_ALT
};

enum custom_keycodes {
  KC_STATS = SAFE_RANGE,
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
  [TD_RESET] = ACTION_TAP_DANCE_DOUBLE(KC_TRNS, RESET),
  [TD_SHIFT_ALT] = ACTION_TAP_DANCE_DOUBLE(KC_LSHIFT, KC_LALT)
};

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {

  [_BASE] = LAYOUT_split_space_base(
    KC_1,   KC_2,    KC_3,    KC_4,    KC_5,    KC_6,    KC_7,    KC_8,    KC_9,           KC_0,
    KC_Q,   KC_W,    KC_E,    KC_R,    KC_T,    KC_Y,    KC_U,    KC_I,    KC_O,           KC_P,
    KC_A,   KC_S,    KC_D,    KC_F,    KC_G,    KC_H,    KC_J,    KC_K,    KC_L,           TD(TD_SCLN_ENTER),
    KC_Z,   KC_X,    KC_C,    KC_V,    KC_B,    KC_N,    KC_M,    KC_COMM, KC_DOT,         KC_SLSH,
          TD(TD_CTRL_SUPER_ALT),  TD(TD_SHIFT_ALT),  LT(_FN, KC_SPACE),   KC_BSPC
  ),

  [_FN] = LAYOUT_split_space_base(
    KC_F1,   KC_F2,   KC_F3,   KC_F4,    KC_F5,   KC_F6,   KC_F7,        KC_F8,   KC_F9,       KC_F10,
    KC_ESC,  KC_HOME, KC_UP,   KC_END,   KC_PGUP, KC_TRNS, TD(TD_RESET), KC_MINS, KC_EQL,      KC_BSLS,
    KC_TAB,  KC_LEFT, KC_DOWN, KC_RIGHT, KC_PGDN, KC_TRNS, KC_GRV,  KC_LBRC, KC_RBRC,          KC_QUOT,
    KC_CAPS, KC_TRNS, KC_TRNS, KC_TRNS,  KC_STATS, KC_TRNS, KC_TRNS, KC_LALT, KC_LGUI,         KC_LCTRL,
          TD(TD_CTRL_SUPER_ALT),  TD(TD_SHIFT_ALT),  LT(_FN, KC_SPACE),   KC_DEL
  )
};

/** TODO want to add some kind of toggleable game-mode layer. Playing games
with the multiple-functionality space/shift keys is frustrating. Being able
to temporarily disable that and have a basic game layout would be great. */

typedef struct stats_s {
    uint64_t total = 0;
    uint32_t count = 0;
    uint16_t min = 65535;
    uint16_t max = 0;
} stats_t;
static stats_t stats;

#define STRING_CONTAINER_SIZE = 16;
bool process_record_user(uint16_t keycode, keyrecord_t *record) {

  if (record->event.pressed && keycode == KC_STATS) {
    // Print out the keypress statistics
    SEND_STRING("Keypress duration statistics:\n");

    // TODO print the stats
    char numberStr[STRING_CONTAINER_SIZE] = "";
    SEND_STRING("Min: ");
    // TODO convert stats.min to ascii in numberStr and print it
    SEND_STRING("\n");
    SEND_STRING("Max: ");
    // TODO convert stats.max to ascii in numberStr and print it
    SEND_STRING("\n");
    SEND_STRING("Average: ");
    // TODO convert (stats.total / stats.count_ to ascii in numberStr and print it
    SEND_STRING("\n");
  }


  /* This section tracks the average key press duration. It watches one key at a time, and
   * logs the duration in the stats struct. This information is useful for tuning variables such as
   * TAPPING_TERM. */
  static uint16_t keydown_timer = 0;
  static uint16_t keycode_down = 0;
  static bool keydown = false;
  if (record->event.pressed && keycode != KC_STATS) {
    // start the timer
    if (!keydown) {
        keycode_down = keycode;
        keydown = true;
        keydown_timer = timer_read();
    }
  } else {
    // finish the timer, log stats
    if (keydown && keycode == keycode_down) {
        uint16_t duration = timer_elapse(keydown_timer);
        stats.total += duration;
        stats.count += 1;
        if (duration < stats.min) { stats.min = duration; }
        if (duratino > stats.max) { stats.max = duration; }
        keydown = false;
    }
  }

  return true;
}
