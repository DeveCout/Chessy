#include <WiFi.h>
#include <HTTPClient.h>
#include <Arduino_JSON.h>
#include <Param.h>
#include <ChessAPI.h>

int get_seconds_since_start(){
  int seconds_elapsed = ((millis() - millis_startup) / 1000);
  return seconds_elapsed;
}


void setup_wifi(){
  Serial.println("[CONNEXION WIFI] Début connexion...");
  WiFi.begin(wifi_ssid, wifi_password);

  while(WiFi.status() != WL_CONNECTED && get_seconds_since_start() < maximal_timeout_seconds ){
  }
  if(WiFi.status() == WL_CONNECTED){
  Serial.print("[CONNEXION WIFI] CONNEXION AU RESEAU : ");
  Serial.print(wifi_ssid);
  Serial.println(" OK !");
  }else{
    Serial.print("[CONNEXION WIFI] /!\ Impossible de se connecter au réseau !");
  }
}


void setup() {
  Serial.begin(115200);

  pinMode(pin_motor_1_direction,OUTPUT);
  pinMode(pin_motor_1_step,OUTPUT);
  pinMode(pin_debug_led,OUTPUT);
  pinMode(pin_debug_touch,INPUT);


  int millis_startup = millis();

  int last_step_motor_1 = millis();
  startup_log_to_do = true;
  delay(100);
  setup_wifi();
  board = Board("rnbqkbnr/pppppppp/8/8/8/8/PPPPPPPP/RNBQKBNR");


  ChessAPI::init();
}

void data_log(){
  Serial.println("[--------------------DEBUG : ");
  Serial.print("Time since startup : ");
  Serial.print(get_seconds_since_start());
  Serial.println("s");

  if(WiFi.status() == WL_CONNECTED)
  {
    Serial.println("WiFi statut : OK");
    Serial.print("SSID : ");
    Serial.println(wifi_ssid);
  }else{
    Serial.println("WiFi statut : /!\ NOK /!\\");
    Serial.print("SSID : ");
    Serial.println(wifi_ssid);
  }

  board.print_board();

  ChessMove *move = new ChessMove();
  if(ChessAPI::get_next_move(move))
  {
    Serial.println(move->original_move);
    Serial.println(move->start_pos_x);
    Serial.println(move->start_pos_y);
    Serial.println(move->end_pos_x);
    Serial.println(move->end_pos_y);
  }
  delete move;
  Serial.println("--------------------]");
}

void manage_debug_touch(){
  if(touchRead(pin_debug_touch) < debug_touch_treshold){
    if(!flag_debug_touch){
      data_log();
    }
    flag_debug_touch = true;
  }else{
    flag_debug_touch = false;      
  }
}

void loop() {
  
  // if(micros() - last_step_motor_1 > duration_micro_between_step )
  // {
  //   last_step_motor_1 = micros();
  //   digitalWrite(pin_motor_1_step,HIGH);
  //   digitalWrite(pin_motor_1_step,LOW);
  //   debug_led = !debug_led;
  //   if (debug_led){
  //     digitalWrite(pin_debug_led,HIGH);
  //   }else{
  //     digitalWrite(pin_debug_led,LOW);
  //   }
  // }

  //Test changement direciton

  // digitalWrite(pin_motor_1_direction,get_seconds_since_start() % 2);

  vTaskDelay(pdMS_TO_TICKS(10));

  manage_debug_touch();
}

