#pragma once
#include <Board.h>

// ----- Wifi

const char* wifi_ssid = "ssid";
const char* wifi_password = "password";
int maximal_timeout_seconds = 10;

// ----- PIN OUT

const int pin_motor_1_direction=12;
const int pin_motor_1_step=14;
const int pin_debug_led=2;
const int pin_debug_touch=13;

const float motor_step_deg = 1.8;
//Number of sub-step used by the driver 
const float driver_step_divide = 16; 

const float true_step_angle = motor_step_deg / driver_step_divide;
const float step_number_full_circle = 360 / true_step_angle;

// ----- Board management

QueueHandle_t chessMove_list;
const int chessMove_list_max_size = 50;
const char* api_lichess = "https://lichess.org/api/tv/bullet/feed";

// ----- DEBUG LED api

const bool use_debug_led_api = true;
int duration_led_milli = 1000;

Board board;

// --- DEBUG TOUCH ----

bool flag_debug_touch = false;
int debug_touch_treshold = 100;

// --- LOGIC ---


// ---------TEST-------

int rps = 1;

float duration_sec_between_step = 1.0 / (rps * step_number_full_circle);
float duration_milli_between_step = duration_sec_between_step * 1000 ;
float duration_micro_between_step = duration_milli_between_step * 1000 ;

int last_step_motor_1 = 0;
bool debug_led = false;
bool startup_log_to_do = true;
int millis_startup = millis();