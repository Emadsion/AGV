#include "def.h"

s16 target_coordinates[][3] = {{300, 0, 0},
                               {0, 0, 0},
                               {0, 300, 0},
                               {0, 0, 0},
                               {300, 300, 0},
                               {0, 600, 0},
                               {300, 300, 0},
                               {0, 0, 0},
                               {0, 0, 180},
                               {0, 0, -90},
                               {0, 0, 0}
                              };

void setup(){
  #ifdef DEBUG
    Serial.begin(115200);
  #endif

  calculateGraph();
  //IMU_vidInit();
  //rfid_config();
  //while(!Serial.available());
  config_motors_pins();
  cofig_lift_mechanism();
  //VidDijkstra(0, 47);

//  KINEMATICS_vidGoAbsCoordinates(750, 0, 0);
//  delay(1500);
//  KINEMATICS_vidGoAbsCoordinates(-750, 0, 0);
//  delay(1500);
//  KINEMATICS_vidGoAbsCoordinates(0, 750, 0);
//  delay(1500);
//  KINEMATICS_vidGoAbsCoordinates(0, -750, 0);
//  delay(1500);
//
//  KINEMATICS_vidGoAbsCoordinates(750, 750, 0);
//  delay(1500);
//  KINEMATICS_vidGoAbsCoordinates(-750, -750, 0);
//  delay(1500);
//  KINEMATICS_vidGoAbsCoordinates(-750, 750, 0);
//  delay(1500);
//  KINEMATICS_vidGoAbsCoordinates(750, -750, 0);
//  delay(1500);
//  
  //while(1);
  delay(5000);
  

}

void loop(){
  
  //start_node = return_node_map();
  start_node = 0;
  end_node = 6;                   // loading place
  VidDijkstra(start_node, end_node);
  
  for(u8 i = 0; i < shortest_path_nodes_index; i++){
    u8 rank = shortest_path_nodes[i] / 6;
    u8 file = shortest_path_nodes[i] % 6;
    DEBUG_PRINT("DEBUG: -> node:");
    DEBUG_PRINTLN(shortest_path_nodes[i]);
    KINEMATICS_vidGoAbsCoordinates(file * MAP_PITCH_mm, rank * MAP_PITCH_mm, 0);

//    if(shortest_path_nodes[i] == return_node_map()) DEBUG_PRINTLN("DEBUG: Robot is on RFID tag");
//    else{
//      DEBUG_PRINTLN("DEBUG: ERROR! --> Robot is not on RFID tag");
//      problem_rfid_map = 1;
//    }
  }

  // lift the mechanism for loadong
  lift_object_mm(15);

  //start_node = return_node_map();
  start_node = shortest_path_nodes[shortest_path_nodes_index - 1];
  end_node = A;                   // unloading place
  VidDijkstra(start_node, end_node);
  for(u8 i = 0; i < shortest_path_nodes_index; i++){
    u8 rank = shortest_path_nodes[i] / 6;
    u8 file = shortest_path_nodes[i] % 6;
    DEBUG_PRINT("DEBUG: -> node:");
    DEBUG_PRINTLN(shortest_path_nodes[i]);
    KINEMATICS_vidGoAbsCoordinates(file * MAP_PITCH_mm, rank * MAP_PITCH_mm, 0);

//    if(shortest_path_nodes[i] == return_node_map()) DEBUG_PRINTLN("DEBUG: Robot is on RFID tag");
//    else{
//      DEBUG_PRINTLN("DEBUG: ERROR! --> Robot is not on RFID tag");
//      problem_rfid_map = 1;
//    }
  }

  // descend the mechanism for unloadong
  lift_object_mm(-15);

  
  
  
}
