// two functions, return node or type. 

//function 1
u8 return_node_obj(){
  u8 node; 
  digitalWrite(SS_OBJ, HIGH);
  SPI.begin();
  delay(500);  //less than that it gets buggy idk why.
  //ss 
  digitalWrite(SS_OBJ, LOW);
  if(!rfid_obj.PICC_IsNewCardPresent() || ! rfid_obj.PICC_ReadCardSerial()){
    return 0;
  }
  DEBUG_PRINT(F("Card ID:"));
  dump_byte_array(rfid_obj.uid.uidByte, rfid_obj.uid.size);  //DEBUG_PRINTLN();
 
  u8 sector         = 1;
  u8 blockAddr      = 4;
  u8 trailerBlock   = 7;
  MFRC522::StatusCode status;   //instance to trouble shoot after each step.
  u8 buffer[18];
  u8 size = sizeof(buffer);

  //read access using key A
  DEBUG_PRINTLN(F("Authenticating using key A..."));
  status = (MFRC522::StatusCode) rfid_obj.PCD_Authenticate(MFRC522::PICC_CMD_MF_AUTH_KEY_A, trailerBlock, &key, &(rfid_obj.uid));
  if(status != MFRC522::STATUS_OK){
    //for serial testing 
    DEBUG_PRINT(F("PCD_Authenticate() failed: "));
    DEBUG_PRINTLN(rfid_obj.GetStatusCodeName(status));
    //send a flag to the main mc if it can.
    problem_rfid_obj = 1;
    return 0;
  }

  // Read data from the block 
  DEBUG_PRINT(F("Reading what we have ")); 
  status = (MFRC522::StatusCode) rfid_obj.MIFARE_Read(blockAddr, buffer, &size);
  if(status != MFRC522::STATUS_OK){
    DEBUG_PRINT(F("MIFARE_Read() failed: "));
    DEBUG_PRINTLN(rfid_obj.GetStatusCodeName(status));
    //send a flag to the main mc if it can.
    problem_rfid_obj = 1;
    return 0;
  }
  
  dump_byte_array(buffer, 16); // DEBUG_PRINTLN();
  node = buffer[0];

  // Halt PICC
  rfid_obj.PICC_HaltA();
  rfid_obj.PCD_StopCrypto1();

  digitalWrite(SS, HIGH);
  SPI.end();
  return node;
}

//func 2  in case i need the object type not the node , stored in 2nd byte in block.
//function 1
u8 return_type_obj(){
  u8 type; 
  digitalWrite(SS_OBJ, HIGH);
  SPI.begin();
  delay(500);  //less than that it gets buggy idk why.
  //ss 
  digitalWrite(SS_OBJ, LOW);
  //remove 2nd condition after testing. 
  if(!rfid_obj.PICC_IsNewCardPresent() || !rfid_obj.PICC_ReadCardSerial()){
    return 0;
  }
  DEBUG_PRINT(F("Card ID:"));
  dump_byte_array(rfid_obj.uid.uidByte, rfid_obj.uid.size);  //DEBUG_PRINTLN();
 
  u8 sector         = 1;
  u8 blockAddr      = 4;
  u8 trailerBlock   = 7;
  MFRC522::StatusCode status;   //instance to trouble shoot after each step.
  u8 buffer[18];
  u8 size = sizeof(buffer);

  //read access using key A
  DEBUG_PRINTLN(F("Authenticating using key A..."));
  status = (MFRC522::StatusCode) rfid_obj.PCD_Authenticate(MFRC522::PICC_CMD_MF_AUTH_KEY_A, trailerBlock, &key, &(rfid_obj.uid));
  if(status != MFRC522::STATUS_OK){
  //for serial testing 
    DEBUG_PRINT(F("PCD_Authenticate() failed: "));
    DEBUG_PRINTLN(rfid_obj.GetStatusCodeName(status));
    //send a flag to the main mc if it can.
    problem_rfid_obj = 1;
    return 0;
  }

  // Read data from the block 
  DEBUG_PRINT(F("Reading what we have ")); 
  status = (MFRC522::StatusCode) rfid_obj.MIFARE_Read(blockAddr, buffer, &size);
  if(status != MFRC522::STATUS_OK){
    DEBUG_PRINT(F("MIFARE_Read() failed: "));
    DEBUG_PRINTLN(rfid_obj.GetStatusCodeName(status));
    //send a flag to the main mc if it can.
    problem_rfid_obj = 1;
    return 0;
  }
  
  dump_byte_array(buffer, 16); // DEBUG_PRINTLN();
  type = buffer[1];

  // Halt PICC
  rfid_obj.PICC_HaltA();
  rfid_obj.PCD_StopCrypto1();

  digitalWrite(SS, HIGH);
  SPI.end();
  return type;
}




  
