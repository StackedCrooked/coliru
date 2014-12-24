for(auto& a_client: clients)
  {
    if(entities[a_client.second.id]->update) //if there is an update(moved)
    {
      client& Moved_Client = a_client.second; //for convenience

      { //in scope so we can reuse "ss"
        std::stringstream ss;
        unsigned char byte_array[7]; //the bytes
        byte_array[0] = (int)((entities[Moved_Client.id]->id & 0xFF00) >> 8); //short, id
        byte_array[1] = (int)(entities[Moved_Client.id]->id & 0x00FF);

        byte_array[2] = (int)((entities[Moved_Client.id]->xpos & 0xFF00) >> 8); //short, x coord
        byte_array[3] = (int)(entities[Moved_Client.id]->xpos & 0x00FF);

        byte_array[4] = (int)((entities[Moved_Client.id]->ypos & 0xFF00) >> 8); //short, y coord
        byte_array[5] = (int)(entities[Moved_Client.id]->ypos & 0x00FF);

        byte_array[6] = (int)(entities[Moved_Client.id]->dir);

        for(int i = 0; i < 7; ++i)
          ss<<byte_array[i];  //pack it up.

        msg a_msg //the message
        {
          player_info,
          ss.str()
        };

        //Send update to clients that are in the clients view( because we see in a circle )
        for(auto& InView_ID: Moved_Client.in_view_entities)
          if(entities[InView_ID]->type == entity_client) 
            for(auto& an_client: clients)
              if(InView_ID == an_client.second.id)
                an_client.second.unrel_msgblk.emplace_back(a_msg); //queue it
      }

      //check if we even moved a tile
      if(entities[Moved_Client.id]->xpos/20 != entities[Moved_Client.id]->last_tile_x
         || entities[Moved_Client.id]->ypos/20 != entities[Moved_Client.id]->last_tile_y)
      {
        entities[Moved_Client.id]->last_tile_x = entities[Moved_Client.id]->xpos/20;
        entities[Moved_Client.id]->last_tile_y = entities[Moved_Client.id]->ypos/20;

        std::vector<int> Not_InView_Clients; //we put in clients here, then knock them off, leftovers are used to delete entities from their list.

        //put only clients into the list.
        for(auto& Maybe_Client: Moved_Client.in_view_entities)
          if(entities[Maybe_Client]->type == entity_client)
            Not_InView_Clients.emplace_back(Maybe_Client);

        //loop through view field
        for(int i = 0, x = 0, y = 0 ; i!=225/*15*15*/; ++i, ++x )
        {
          if(x >= 15)
          {
            x = 0;
            ++y ;
          }

          //this is the spot of where the array of bools 'view_field', is currently scanning (x & y) & it removes the remainder of 2, so its the topleft corner of a 4x4 block
          int xpos = (entities[Moved_Client.id]->xpos/20) - 7 + x-(((entities[Moved_Client.id]->xpos/20) - 7 + x)%2);
          int ypos = (entities[Moved_Client.id]->ypos/20) - 7 + y-(((entities[Moved_Client.id]->ypos/20) - 7 + y)%2);

          //basically if it is inside our view and map.
          if( xpos >= 0 && xpos >= 0
             && view_field[x][y] == 0 )
          {
            //Look if there is an entity found here-----------------------
            for(auto& Maybe_InView_Client: clients)
            {
              client& InView_Client = Maybe_InView_Client.second; //For convenience

              //if an entity collides with the tile
              if(InView_Client.id != Moved_Client.id
                 && entities[InView_Client.id]->xpos/20 == (entities[Moved_Client.id]->xpos/20) - 7 + x
                 && entities[InView_Client.id]->ypos/20 == (entities[Moved_Client.id]->ypos/20) - 7 + y)
              {
                //erase
                for(auto it = Not_InView_Clients.begin(); it!=Not_InView_Clients.end(); ++it)
                  if(*it == InView_Client.id)
                  {
                    Not_InView_Clients.erase(it);
                    break;
                  }

                //Send to both clients their positions.
                bool if_already = false; //if this entity already exists.

                for(auto& Moved_Client_InView_Entity: Moved_Client.in_view_entities)
                {
                  if(entities[Moved_Client_InView_Entity]->type == entity_client && Moved_Client_InView_Entity == InView_Client.id)
                  {
                    if_already = true;
                    break; //there should be only 1.
                  }
                }

                /*for(auto& InView_Client_InView_Entity: InView_Client.in_view_entities)
                {
                  if(entities[InView_Client_InView_Entity]->type == entity_client && InView_Client_InView_Entity == Moved_Client.id)
                  {
                    if_already = true;
                    break; //there should be only 1.
                  }
                }*/

                if(!if_already) //Send to both client a "New_Client" packet
                {
                  { //send inview_client to moved client
                    //data of msg----------------
                    unsigned char byte_array[8]; //the format of the entity msg
                    byte_array[0] = (int)((InView_Client.id & 0xFF00) >> 8); //short
                    byte_array[1] = (int)(InView_Client.id & 0x00FF);
                    byte_array[2] = (int)(entities[InView_Client.id]->flags);
                    byte_array[3] = (int)((entities[InView_Client.id]->xpos & 0xFF00) >> 8); //short
                    byte_array[4] = (int)(entities[InView_Client.id]->xpos & 0x00FF);
                    byte_array[5] = (int)((entities[InView_Client.id]->ypos & 0xFF00) >> 8); //short
                    byte_array[6] = (int)(entities[InView_Client.id]->ypos & 0x00FF);
                    byte_array[7] = (int)(entities[InView_Client.id]->dir);

                    std::stringstream ss;
                    for(int i = 0; i < 8; ++i)
                      ss<<byte_array[i];  //pack it up.

                    ss<<entities[InView_Client.id]->name; //don't forget the name :>

                    msg a_msg
                    {
                      new_player,
                      ss.str()
                    };

                    Moved_Client.cur_msgblk.emplace_back(a_msg);

                    //into entity list
                    Moved_Client.in_view_entities.emplace_back(InView_Client.id);
                  }
                  //Send moved_client to inview client.

                  //data of msg----------------
                  unsigned char byte_array[8]; //the format of the entity msg
                  byte_array[0] = (int)((Moved_Client.id & 0xFF00) >> 8); //short
                  byte_array[1] = (int)(Moved_Client.id & 0x00FF);
                  byte_array[2] = (int)(entities[Moved_Client.id]->flags);
                  byte_array[3] = (int)((entities[Moved_Client.id]->xpos & 0xFF00) >> 8); //short
                  byte_array[4] = (int)(entities[Moved_Client.id]->xpos & 0x00FF);
                  byte_array[5] = (int)((entities[Moved_Client.id]->ypos & 0xFF00) >> 8); //short
                  byte_array[6] = (int)(entities[Moved_Client.id]->ypos & 0x00FF);
                  byte_array[7] = (int)(entities[Moved_Client.id]->dir);

                  std::stringstream ss;
                  for(int i = 0; i < 8; ++i)
                    ss<<byte_array[i];  //pack it up.

                  ss<<entities[Moved_Client.id]->name; //don't forget the name :>

                  msg a_msg
                  {
                    new_player,
                    ss.str()
                  };

                  InView_Client.cur_msgblk.emplace_back(a_msg);

                  //into entity list
                  InView_Client.in_view_entities.emplace_back(Moved_Client.id);

                }
              }
            }

            //SENDING TILE PART-----------------------------------------------------------
            if(Moved_Client.tile_field[xpos][ypos] == false)
            {
              Moved_Client.tile_field[xpos][ypos] = true; //field to true

              unsigned char byte_array[8]; //the bytes to send.

              //position, the position is based off the topleft tile(first).
              byte_array[0] = (int)(( xpos & 0x00FF) >> 8); //x
              byte_array[1] = (int)( xpos & 0x00FF);
              byte_array[2] = (int)(( ypos & 0xFF00) >> 8); //y
              byte_array[3] = (int)( ypos & 0x00FF);

              byte_array[4] = (int)(tileset[xpos][ypos]); //tile 1 type
              byte_array[5] = (int)(tileset[xpos+1][ypos]); //tile 2 type
              byte_array[6] = (int)(tileset[xpos][ypos+1]); //tile 3 type
              byte_array[7] = (int)(tileset[xpos+1][ypos+1]); //tile 4 type

              std::stringstream ss;
              for(int i = 0; i < 8; ++i)
                ss<<byte_array[i];

              msg a_msg
              {
                tile_data,
                ss.str()
              };

              Moved_Client.cur_msgblk.emplace_back(a_msg);
            }
          } //if in view
        } //looping through view field

        //Check if there are any clients that are not in the view
        for(auto& Not_InView_ID: Not_InView_Clients)
          for(auto it = clients.begin(); it!=clients.end(); it++)
            if(Not_InView_ID == (*it).second.id)
            {
              {
                //Send to Not_InView client
                std::stringstream ss;
                unsigned char byte_array[2];
                byte_array[0] = (int)((Moved_Client.id) >> 8); //the id to delete
                byte_array[1] = (int)(Moved_Client.id);

                ss<<byte_array[0]<<byte_array[1];

                msg a_msg
                {
                  delete_entity,
                  ss.str()
                };

                (*it).second.cur_msgblk.emplace_back(a_msg);
              }

              //Send to moved client
              std::stringstream ss;
              unsigned char byte_array[2];
              byte_array[0] = (int)(((*it).second.id) >> 8); //the id to delete
              byte_array[1] = (int)((*it).second.id);

              ss<<byte_array[0]<<byte_array[1];

              msg a_msg
              {
                delete_entity,
                ss.str()
              };

              Moved_Client.cur_msgblk.emplace_back(a_msg);

              //Remove the ID's from their list
              for(auto a_id = (*it).second.in_view_entities.begin(); a_id!=(*it).second.in_view_entities.end(); ++a_id)
                if(*a_id == Moved_Client.id)
                {
                  (*it).second.in_view_entities.erase(a_id);
                  break;
                }

              for(auto a_id = Moved_Client.in_view_entities.begin(); a_id!=Moved_Client.in_view_entities.end(); ++a_id)
                if(*a_id == (*it).second.id)
                {
                  Moved_Client.in_view_entities.erase(a_id);
                  break;
                }

            }

      } //if the client even moved a tile
      entities[Moved_Client.id]->update = false; //udpate is over.
    } //if client is updated
  } //loop though clients