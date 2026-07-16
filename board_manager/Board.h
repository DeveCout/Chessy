class Board{
  public :
  char board_pieces[8][8];

  Board(){
    empty_board();
  };
  Board(String fen_string){
    empty_board();
    load_fen(fen_string);
  };

  void empty_board(){
    for(int y=0;y<8;y++){
      for(int x=0;x<8;x++){
        this->board_pieces[y][x] = ' ';
      }
    }
  }

  void print_board(){
    for(int y=0;y<8;y++){
      for(int x=0;x<8;x++){
        Serial.print(this->board_pieces[y][x]);
      }
      Serial.println("");
    }
  }

  void load_fen(String fen_string){

    Serial.println("Loading fen...");
    int x = 0;
    int y = 0;
    bool end_filling = false;
    char fen_char;
     for(int i=0;i<fen_string.length() && !end_filling;i++){
    //for(int i=0;i<5;i++){
      fen_char = fen_string.charAt(i);
      switch(fen_char){
        case ' ':
          end_filling = true;
          return;
        break;
        case '/':
          if (x < 8 && y < 8){
            for(;x<8;x++){
              this->board_pieces[y][x] = ' ';
            }
          }
          y++;
          x=0;
        break;
        case 'R':
        case 'N':
        case 'B':
        case 'Q':
        case 'K':
        case 'P':

        case 'r':
        case 'n':
        case 'b':
        case 'q':
        case 'k':
        case 'p':
          if (x < 8 && y < 8)
            this->board_pieces[y][x] = fen_char;
          x++;
        break;
        default:
          int hole_count = fen_char - '0';          
          for(int j=0;j<hole_count;j++){
            if(x < 8 && y < 8)
            {
              this->board_pieces[y][x] = ' ';
            }
            x++;
          }
      }
    }
  }
};