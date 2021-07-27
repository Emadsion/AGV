// map rfid returns a node. 

u8 return_node_map(void){
  u8 node; 
  digitalWrite(SS_MAP, HIGH);
  SPI.begin();
  delay(500);  //less than that it gets buggy idk why.
  //ss 
  digitalWrite(SS_MAP, LOW);

  if(!rfid_map.PICC_IsNewCardPresent() || !rfid_map.PICC_ReadCardSerial()){
    return 0;
  }
  
  //nxt 3 lines for serial testing only
  DEBUG_PRINT(F("Card ID:"));
  dump_byte_array(rfid_map.uid.uidByte, rfid_map.uid.size);
  DEBUG_PRINTLN();
 
  u8 sector         = 1;
  u8 blockAddr      = 4;
  u8 trailerBlock   = 7;
  MFRC522::StatusCode status;   //instance to trouble shoot after each step on serial / com in case of reading problems.
  u8 buffer[18];
  u8 size = sizeof(buffer);

  //read using key A
  DEBUG_PRINTLN(F("Authenticating using key A..."));
  status = (MFRC522::StatusCode) rfid_map.PCD_Authenticate(MFRC522::PICC_CMD_MF_AUTH_KEY_A, trailerBlock, &key, &(rfid_map.uid));
  if(status != MFRC522::STATUS_OK){
    //for serial testing 
    DEBUG_PRINT(F("PCD_Authenticate() failed: "));
    DEBUG_PRINTLN(rfid_map.GetStatusCodeName(status));
    //send a flag to the main mc if it can.
    problem_rfid_map = 1;
    return 0;
  }

  // Read data from the block 
  DEBUG_PRINT(F("Reading what we have ")); 
  status = (MFRC522::StatusCode) rfid_map.MIFARE_Read(blockAddr, buffer, &size);
  if(status != MFRC522::STATUS_OK){
    DEBUG_PRINT(F("MIFARE_Read() failed: "));
    DEBUG_PRINTLN(rfid_map.GetStatusCodeName(status));
    //send a flag to the main mc if it can.
    problem_rfid_map = 1;
    return 0;
  }
  
  dump_byte_array(buffer, 16); 
  node = buffer[0];

  // Halt PICC
  rfid_map.PICC_HaltA();
  rfid_map.PCD_StopCrypto1();

  digitalWrite(SS_MAP, HIGH);
  SPI.end();
  return node;
}

//helper for rfid on serial
void dump_byte_array(u8 *buffer, u8 bufferSize) {
  for(u8 i = 0; i < bufferSize; i++){
    DEBUG_PRINT(buffer[i] < 0x10 ? " 0" : " ");
    DEBUG_PRINT(buffer[i], HEX);
  }
}

void rfid_config(void){
  SPI.begin();
  pinMode(SS_MAP, OUTPUT);
  pinMode(SS_OBJ, OUTPUT);    
  rfid_map.PCD_Init();    
  rfid_obj.PCD_Init();

  //the global key value
  for (u8 i = 0; i < 6; i++){
   key.keyByte[i] = 0xFF;
  }
  
  delay(4);   
}
