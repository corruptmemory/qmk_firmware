#include QMK_KEYBOARD_H

enum tap_dance_codes {
  DANCE_COMMA, // Comma
  DANCE_PERIOD, // Period
  DANCE_SLASH, // Slash
};

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
	[0] = LAYOUT_split_3x5_2(
      KC_Q,         KC_W,         KC_E,             KC_R,            KC_T,                   /*|*/  KC_Y,         KC_U,         KC_I,          KC_O,         KC_P,
      LSFT_T(KC_A), LCTL_T(KC_S), LALT_T(KC_D),     LWIN_T(KC_F),    KC_G,                   /*|*/  KC_H,         LWIN_T(KC_J), LALT_T(KC_K),  RCTL_T(KC_L), RSFT_T(KC_SCLN),
      KC_Z,         KC_X,         LT(4,KC_C),       LT(2,KC_V),      KC_B,                   /*|*/  KC_N,         KC_M,         TD(DANCE_COMMA),   TD(DANCE_PERIOD),  TD(DANCE_SLASH),
                                                    TG(1),           KC_BSPC,                /*|*/  KC_SPC,       LT(3,KC_ENT)),

	[1] = LAYOUT_split_3x5_2(
      KC_NO,      KC_NO,          KC_NO,            KC_NO,           KC_NO,                  /*|*/  KC_NO,        KC_HOME,      KC_PGDN,       KC_PGUP,      KC_END,
      KC_LSHIFT,  KC_LCTRL,       KC_LALT,          KC_LWIN,         KC_NO,                  /*|*/  KC_NO,        KC_LEFT,      KC_DOWN,       KC_UP,        KC_RGHT,
      KC_NO,      KC_NO,          KC_NO,            KC_NO,           KC_NO,                  /*|*/  KC_NO,        KC_HOME,      KC_PGDN,       KC_PGUP,      KC_END,
                                                    KC_TRNS,         KC_TRNS,                /*|*/  KC_TRNS,      KC_NO),

  [2] = LAYOUT_split_3x5_2(
      KC_NO,      KC_NO,          KC_NO,            KC_NO,           KC_NO,                  /*|*/  KC_GRV,       KC_UNDS,      KC_EXLM,       KC_PERC,      KC_GRV,
      KC_LSHIFT,  KC_LCTRL,       KC_LALT,          KC_LWIN,         KC_NO,                  /*|*/  KC_HASH,      KC_MINS,      KC_PLUS,       KC_ASTR,      KC_QUOT,
      KC_NO,      KC_NO,          KC_ESC,           KC_TRNS,         KC_NO,                  /*|*/  KC_CIRC,      KC_TILD,      KC_PIPE,       KC_AMPR,      KC_BSLS,
                                                    KC_NO,           KC_AT,                  /*|*/  KC_EQL,       KC_DLR),

  [3] = LAYOUT_split_3x5_2(
      KC_LBRC,    KC_RBRC,        KC_LPRN,          KC_RPRN,         KC_MUTE,                /*|*/  KC_PLUS,      KC_7,         KC_8,          KC_9,         KC_DOT,
      KC_LSHIFT,  KC_LCTRL,       KC_LALT,          KC_LWIN,         KC_MSTP,                /*|*/  KC_MINS,      KC_4,         KC_5,          KC_6,         KC_EQL,
      KC_LCBR,    KC_RCBR,        KC_ASTR,          KC_SLSH,         KC_TAB,                 /*|*/  KC_0,         KC_1,         KC_2,          KC_3,         KC_COMM,
                                                    KC_VOLU,         KC_VOLD,                /*|*/  RESET,        KC_TRNS),

  [4] = LAYOUT_split_3x5_2(
      KC_NO,      KC_NO,          KC_NO,            KC_NO,           LALT(LSFT(KC_INSERT)),  /*|*/  LCTL(KC_F9),  KC_F7,        KC_F8,         KC_F9,        KC_F10,
      KC_LSHIFT,  KC_LCTRL,       KC_LALT,          KC_LWIN,         KC_INSERT,              /*|*/  LCTL(KC_F10), KC_F4,        KC_F5,         KC_F6,        KC_F11,
      KC_PSCREEN, KC_NO,          KC_TRNS,          KC_CAPSLOCK,     KC_NO,                  /*|*/  LCTL(KC_F11), KC_F1,        KC_F2,         KC_F3,        KC_F12,
                                                    KC_LALT,         KC_DEL,                 /*|*/  KC_NO,        LCTL(KC_F12))
};

typedef struct {
    bool is_press_action;
    uint8_t step;
} tap;

enum {
    SINGLE_TAP = 1,
    SINGLE_HOLD,
    DOUBLE_TAP,
    DOUBLE_HOLD,
    DOUBLE_SINGLE_TAP,
    MORE_TAPS
};

static tap dance_state = {
    .is_press_action = true,
    .step = 0
};


void dance_comma_finished(qk_tap_dance_state_t *state, void *user_data);
void dance_comma_reset(qk_tap_dance_state_t *state, void *user_data);

uint8_t cur_dance(qk_tap_dance_state_t *state) {
  if (state->count == 1) {
    if (state->interrupted || !state->pressed) return SINGLE_TAP;
    else return SINGLE_HOLD;
  } else if (state->count == 2) {
    if (state->interrupted) return DOUBLE_SINGLE_TAP;
    else if (state->pressed) return DOUBLE_HOLD;
    else return DOUBLE_TAP;
  }
  return MORE_TAPS;
}

void dance_comma_finished(qk_tap_dance_state_t *state, void *user_data) {
  dance_state.step = cur_dance(state);
  switch (dance_state.step) {
    case SINGLE_TAP: register_code16(KC_COMM); break;
    case SINGLE_HOLD: register_code16(KC_UNDS); break;
    case DOUBLE_TAP: register_code16(KC_COMM); register_code16(KC_COMM); break;
    case DOUBLE_SINGLE_TAP: tap_code16(KC_COMM); register_code16(KC_COMM); break;
    default:
      register_code16(KC_COMM);
  }
}

void dance_comma_reset(qk_tap_dance_state_t *state, void *user_data) {
  // wait_ms(10);
  switch (dance_state.step) {
    case SINGLE_HOLD: unregister_code16(KC_UNDS); break;
    default:
      unregister_code16(KC_COMM);
  }
  dance_state.step = 0;
}

void dance_period_finished(qk_tap_dance_state_t *state, void *user_data);
void dance_period_reset(qk_tap_dance_state_t *state, void *user_data);

void dance_period_finished(qk_tap_dance_state_t *state, void *user_data) {
  dance_state.step = cur_dance(state);
  switch (dance_state.step) {
    case SINGLE_TAP: register_code16(KC_DOT); break;
    case SINGLE_HOLD: register_code16(KC_MINS); break;
    case DOUBLE_TAP: register_code16(KC_DOT); register_code16(KC_DOT); break;
    case DOUBLE_SINGLE_TAP: tap_code16(KC_DOT); register_code16(KC_DOT); break;
    default:
      register_code16(KC_DOT);
  }
}

void dance_period_reset(qk_tap_dance_state_t *state, void *user_data) {
  // wait_ms(10);
  switch (dance_state.step) {
    case SINGLE_HOLD: unregister_code16(KC_MINS); break;
    default:
      unregister_code16(KC_DOT);
  }
  dance_state.step = 0;
}

void dance_slash_finished(qk_tap_dance_state_t *state, void *user_data);
void dance_slash_reset(qk_tap_dance_state_t *state, void *user_data);

void dance_slash_finished(qk_tap_dance_state_t *state, void *user_data) {
  dance_state.step = cur_dance(state);
  switch (dance_state.step) {
    case SINGLE_TAP: register_code16(KC_SLSH); break;
    case SINGLE_HOLD: register_code16(KC_DQUO); break;
    case DOUBLE_TAP: register_code16(KC_SLSH); register_code16(KC_SLSH); break;
    case DOUBLE_SINGLE_TAP: tap_code16(KC_SLSH); register_code16(KC_SLSH); break;
    default:
      register_code16(KC_SLSH);
  }
}

void dance_slash_reset(qk_tap_dance_state_t *state, void *user_data) {
  // wait_ms(10);
  switch (dance_state.step) {
    case SINGLE_HOLD: unregister_code16(KC_DQUO); break;
    default:
      unregister_code16(KC_SLSH);
  }
  dance_state.step = 0;
}

qk_tap_dance_action_t tap_dance_actions[] = {
        [DANCE_COMMA] = ACTION_TAP_DANCE_FN_ADVANCED(NULL, dance_comma_finished, dance_comma_reset),
        [DANCE_PERIOD] = ACTION_TAP_DANCE_FN_ADVANCED(NULL, dance_period_finished, dance_period_reset),
        [DANCE_SLASH] = ACTION_TAP_DANCE_FN_ADVANCED(NULL, dance_slash_finished, dance_slash_reset),
  };