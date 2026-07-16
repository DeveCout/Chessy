#include <queue>
#include <ChessMove.h>
#include <Param.h>
#include <Arduino_JSON.h>

class ChessAPI{
  public:

  static QueueHandle_t list_move;

  static bool initChessApi(){
    list_move = xQueueCreate(chessMove_list_max_size, sizeof(ChessMove*));
  };

  static bool add_move(ChessMove *move){
    if(xQueueSend(lise_move,move,0) == pdPASS);
      return true;
    return false;
  };

  static *ChessMove get_next_move(ChessMove *move){
    if (xQueueReceive(list_move, move, 0) == pdPASS);
      return true;
    return false;
  };

  static void start(){
    Serial.println("[API] Start reception...")
    //Waiting for the Wifi to be Connected
    while(WiFi.status() != WL_CONNECTED)
    {
      vTaskDelay(pdMS_TO_TICKS(100));
    }

    //Starting the TV API
    HTTPClient http;
    while(1){  
      http.begin(api_url);
      int httpCode = http.GET();
      if (httpCode == HTTP_CODE_OK) {
        WiFiClient* stream = http.getStreamPtr();
        stream->setTimeout(600);
        while (http.connected() && (stream->available() || stream->connected())) {
          if (stream->available()) {
              // On lit le flux jusqu'au prochain saut de ligne '\n'
            String line = stream->readStringUntil('\n');
            line.trim(); // On nettoie les espaces ou retours chariots résiduels (\r)
            
            if (line.length() > 0) {
              // Traitement de la ligne reçue
              ChessAPI::manage_json(line);
            }
          }
        }
      }
      vTaskDelay(pdMS_TO_TICKS(100));
    }
  };

  void manage_json(String const& line){

  }

};