#include "JSONVar.h"
#include <queue>
#include <ChessMove.h>
#include <Param.h>
#include <Arduino_JSON.h>

class ChessAPI{
  public:

  static QueueHandle_t list_move;
  static int led_duration;

  static bool add_move(ChessMove *move){
    if(xQueueSend(list_move,move,10) == pdPASS)
      return true;
    return false;
  };

  static bool get_next_move(ChessMove *move){
    if (xQueueReceive(list_move, move, 10) == pdPASS)
      return true;
    return false;
  };

  static void manage_json(String const& line){
    JSONVar data = JSON.parse(line);
    
    if (JSON.typeof(data) == "undefined") {
      return;
    }

    if(data.hasOwnProperty("t") && (String)data["t"] == "fen"){
      //Casting necessary, otherwise the wrong constructor is called ("new game" instead of "move")
      const char* coords = (const char*)data["d"]["lm"];
      if(coords != nullptr)
        add_move(new ChessMove((char*)coords));
    }else if(data.hasOwnProperty("t") && (String)data["t"] == "featured"){
      add_move(new ChessMove(true));
    }
  };

  static void start_debug_led(){
    led_duration = millis();
    digitalWrite(pin_debug_led,HIGH);
    Serial.println("Receive line...");
  }

  static void update_debug_led(){
    if(millis() - led_duration > duration_led_milli){
      digitalWrite(pin_debug_led,LOW);
    }
  };

  static void start(void* parameter){
    Serial.println("[API] Start reception...");
    //Waiting for the Wifi to be Connected
    while(WiFi.status() != WL_CONNECTED)
    {
      vTaskDelay(pdMS_TO_TICKS(100));
    }

    //Starting the TV API
    HTTPClient http;
    while(1){  
      http.begin(api_lichess);
      int httpCode = http.GET();
      if (httpCode == HTTP_CODE_OK) {
        WiFiClient* stream = http.getStreamPtr();
        stream->setTimeout(600);
        while (http.connected() && (stream->available() || stream->connected())) {
          if (stream->available()) {
            //Get the nd-json line
            String line = stream->readStringUntil('\n');
            line.trim(); 
            
            //Filtering the useless lines
            if (line.length() > 10) {
              // Traitement de la ligne reçue
              ChessAPI::manage_json(line);
              if(use_debug_led_api)
              {
                start_debug_led();
              }
            }
          }
        update_debug_led();
        }
      }
      vTaskDelay(pdMS_TO_TICKS(100));
    }
  };

  static void init(){
    list_move = xQueueCreate(chessMove_list_max_size, sizeof(ChessMove*));
    xTaskCreate(
      ChessAPI::start,       /* Function that implements the task. */
      "CHESS_API",          /* Text name for the task. */
      16000,      /* Stack size in words, not bytes. */
      NULL,    /* Parameter passed into the task. */
      tskIDLE_PRIORITY,/* Priority at which the task is created. */
      NULL );      /* Used to pass out the created task's handle. */
    };

};

QueueHandle_t ChessAPI::list_move;
int ChessAPI::led_duration;