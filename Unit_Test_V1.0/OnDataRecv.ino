// Possible problems: Dont recall, but I am assuming this is only called on successful recieves.
// Not sure if there are ownership problems wen the temp node is transfered into the linkedlist

// Description: Callback function when the esp32 recieves data. It converts the 
// recieved message in to the message structure. It then adds it to the end of
// the linked list.



/*
void OnDataRecv(const uint8_t * mac, const uint8_t *incomingData, int len) {
  uint8_t transferredData[255];
  for (int i = 0; i < len ; i++) {
    Serial.write(incomingData[i]);
  }
  rec++;
}
*/
