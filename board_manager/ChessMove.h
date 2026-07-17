class ChessMove{

  public:

  char* original_move;

  int start_pos_x;
  int start_pos_y;

  int end_pos_x;
  int end_pos_y;

  bool new_game = false;
  char promotion_to;
  char* fen = "";

  ChessMove(){
    this->start_pos_x = 0;
    this->start_pos_y = 0;
    this->end_pos_x = 0;
    this->end_pos_y = 0;    
    this->original_move = new char(' ');
    this->promotion_to = ' ';
    this->fen = "";
};

  ChessMove(int start_pos_x,int start_pos_y,int end_pos_x,int end_pos_y){
    ChessMove();    
    this->start_pos_x = start_pos_x;
    this->start_pos_y = start_pos_y;
    this->end_pos_x = end_pos_x;
    this->end_pos_y = end_pos_y;
  };

  ChessMove(bool new_game){
    ChessMove();    
    this->new_game = new_game;
  };

  ChessMove(char* const& move){
    ChessMove();    
    if(strlen(move)<4){
      return;
    }
    this->original_move = move;
    this->start_pos_x = get_coord_from_text(move,0);
    this->start_pos_y = get_coord_from_text(move,1);
    this->end_pos_x = get_coord_from_text(move,2);
    this->end_pos_y = get_coord_from_text(move,3);
    if(strlen(move) > 4){
      this->promotion_to = move[4];
    }
  };

  int get_coord_from_text(char* const& coord,int const& index){
    char coord_char = coord[index];
    Serial.println("gget_coord_text");
    Serial.print("coord : ");
    Serial.println(coord);

    Serial.print("coord_char : ");
    Serial.println(coord_char);


    Serial.print("index : ");
    Serial.println(index);

    switch(coord_char){
      case 'a':
        return 1;
      case 'b':
        return 2;
      case 'c':
        return 3;
      case 'd':
        return 4;
      case 'e':
        return 5;
      case 'f':
        return 6;
      case 'g':
        return 7;
      case 'h':
        return 8;
    }

    //Default
    int result_coord = coord_char - '0';
    return result_coord;
  };
};
