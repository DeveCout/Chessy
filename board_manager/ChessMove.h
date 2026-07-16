class ChessMove{

  public:

  int start_pos_x;
  int start_pos_y;

  int end_pos_x;
  int end_pos_y;

  ChessMove(char* value_json){
    
  };
  ChessMove(int start_pos_x,int start_pos_y,int end_pos_x,int end_pos_y){
    this->start_pos_x = start_pos_x;
    this->start_pos_y = start_pos_y;
    this->end_pos_x = end_pos_x;
    this->end_pos_y = end_pos_y;
  };
};
