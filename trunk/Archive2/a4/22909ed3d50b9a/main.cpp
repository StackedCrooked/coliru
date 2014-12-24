class client //the object for every client that is connected.
{
private:
  // edp_; //client endpoint
  steady_clock::time_point Timeout;

public:

  int id = -1; //this clients entity

  std::vector<int> in_view_entities;

  //a seen tile of 4x4
  bool tile_field[1000][1000];

  unsigned int clients_pak_num = 0; //the pack num we send.
  unsigned int servers_pak_num = 0; //the pack num we receive
  unsigned int ack_pak_num = 0;     //to drop old reliable data.

  std::vector<msg> cur_msgblk;                                         //unsent data
  std::vector< std::pair<unsigned int,std::vector<msg>> > old_msgblks; //list of unacked reliable packets. we pair them with their pak_nums.
  std::vector<msg> unrel_msgblk;                                       //Unreliable data like player positions.

  std::vector< std::pair<unsigned int,std::string> > ext_buffer;  //For multiple packet handling, instead of msgs, it holds the serialized strings, and paired up with their pak_num.
  std::vector<msg> last_ext_msgblk;                               //Hold in the last ext_msgblk msgs, so we can add on new data.

  unsigned int last_ext_num = 0; //the last sent ext msgblk

  client(int _id )
  {
    servers_pak_num = 0; clients_pak_num = 0; ack_pak_num = 0; last_ext_num = 0; id = _id;
    Timeout = steady_clock::now();
    //initialize the update feild as false.
    for(int i = 0, x = 0, y = 0; i < (MAP_WIDTH*MAP_HEIGHT)/4; ++i, ++x) //a tile_field is 4x4 spot, so we divide it by 4.
    {
      if(x >= MAP_WIDTH/4)
      {
        x = 0;
        ++y;
      }
      tile_field[x][y] = false;
    }
  }

  void delayTimeout()
  {
    Timeout = steady_clock::now();
  }

  //udp::endpoint getEndpoint(){return edp_;}

  bool timed_out(){Timeout = steady_clock::now();
    return duration_cast<seconds>(steady_clock::now() - Timeout).count() >= 5; }

  ~client(){}

};