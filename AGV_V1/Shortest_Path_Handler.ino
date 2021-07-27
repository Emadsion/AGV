void calculateGraph(void){
  u8 i, j, k, m;
  for(u8 x = 0; x < 48; x++){
    for(u8 y = 0; y < 48; y++){
      i = x % 6;
      j = x / 6;
      k = y % 6;
      m = y / 6;
      if((abs(k - i) == 1 && m == j) || (abs(m - j) == 1 && k == i)){
        Graph[x][y] = 5;
      }else if((abs(m - j) == 1 && abs(k - i == 1)) || (abs(j - m) == 1 && abs(i - k == 1))){
        Graph[x][y] = 7;
      }
    }
  }
}

//Dijkstra Algoritm for finding the shortest path between starting point & ending point
void VidDijkstra(u8 StartNode, u8 EndNode){

  // The output array. Distance[i] will hold the shortest Distances from Source to i
  u16 Distance[NO_NODES];

  /*SptSet[i] will true if vertex
    is included in shortest path tree
    or shortest Distances*/
  u8 SptSet[NO_NODES];

  // Parent array to store
  // shortest path tree
  s8 Parent[NO_NODES];

  // Initialize all Distances as
  // INFINITE and stpSet[] as false
  for(u8 LOC_Count = 0; LOC_Count < NO_NODES; LOC_Count++){
    Parent[LOC_Count] = -1;
    Distance[LOC_Count] = INT_MAX;
    SptSet[LOC_Count] = false;
  }
  
  // Distanc of source vertex from itself is always 0
  Distance[StartNode] = 0;

  // Find shortest path
  // for all vertices

  /*first loop: finding the vertex with shortest path to it
    Second loop:updating distace value if:
        - it's not yet included at sptset tree which contain done vertices
        - there is an actual path between it and the previous vetex
        - the total distance covered from pervious vertices is less than the current distance calcuated from any previous path (at the first iteration less than infinity) 
  */
  
  for (u8 LOC_Count = 0; LOC_Count < NO_NODES - 1; LOC_Count++){
    // Pick the minimum Distances vertex from the set of vertices not yet processed. u is always equal to Source in first iteration.
    u8 INT_MinDistanceVertex = IntMinDistances(Distance, SptSet);

    // Mark the picked vertex
    SptSet[INT_MinDistanceVertex] = true;

    // Update Distance value
    for(u8 LOC_UpdateCount = 0; LOC_UpdateCount < NO_NODES; LOC_UpdateCount++){

      if (!SptSet[LOC_UpdateCount] && Graph[INT_MinDistanceVertex][LOC_UpdateCount] &&
          Distance[INT_MinDistanceVertex] + Graph[INT_MinDistanceVertex][LOC_UpdateCount] < Distance[LOC_UpdateCount]){
        Parent[LOC_UpdateCount] = INT_MinDistanceVertex;
        Distance[LOC_UpdateCount] = Distance[INT_MinDistanceVertex] + Graph[INT_MinDistanceVertex][LOC_UpdateCount];
      }
    }
    
  }

  for(u8 i = 0; i < NO_NODES; i++) shortest_path_nodes[i] = -1;
  shortest_path_nodes_index = 0;
  
  //finding the path from startig point to end point   
  VidPath(Parent, EndNode);
  DEBUG_PRINT("\nDEBUG: Shortest Path from [");  DEBUG_PRINT(StartNode);  DEBUG_PRINT("] to [");  DEBUG_PRINTLN(EndNode);
  DEBUG_PRINT("DEBUG: ");
  for(u8 i = 0; i < shortest_path_nodes_index; i++){
    if(shortest_path_nodes[i] == -1) break;
    DEBUG_PRINT(" -> ");
    DEBUG_PRINT(shortest_path_nodes[i]);
  }
  DEBUG_PRINTLN("\n");
}

/*
Function to find the next minimum point index.
*/
u8 IntMinDistances(u16 Distance[], u8 SptSet[]){
  u16 Min = INT_MAX;
  u8 MinIndex;

  for(u8 LOC_CheckDistance = 0; LOC_CheckDistance < NO_NODES; LOC_CheckDistance++){
    if(SptSet[LOC_CheckDistance] == false && Distance[LOC_CheckDistance] <= Min){
      Min = Distance[LOC_CheckDistance];
      MinIndex = LOC_CheckDistance;
    }
  }

  return MinIndex;
}


/*
  Recurssion function which return the path from Starting point(source) to Ending point
  throught recursuion as it start from ending point and goes down tha path in every recursion 
  all the way to start point (source) 

   Inputs : - Parent array which contain paths from start point to any point
            - Ending point
            
   Outputs: -Array of required path 
  
*/
void VidPath(s8 Parent[], u8 Node){

  // Base Case : If Node is source
  if(Parent[Node] == -1) return;

  VidPath(Parent, Parent[Node]);
  shortest_path_nodes[shortest_path_nodes_index++] = Node;
}
