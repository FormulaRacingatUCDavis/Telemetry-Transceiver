void UnitTest(){
  message* message_test = new message();
  uint8_t frame_test[255];
  
  
  //Try to overload the linked list
  Serial.println("Tons of wifi data test");
  message_test->type = 0;
  message_test->dlc = 240;
  message_test->xcvrID = 0;
  message_test->msgNum = 0;
  for (uint8_t i = 0; i < 240; i++) {
    message_test->payload[i] = 1;
  }
  message_test->checkSum = 63 + 63;
  uint8_t len = msgToFrame(message_test, frame_test);

  time1 = micros();
  for (int i = 0; i < 10000; i++){
    while (LOOP_BUFFER < current_buffer){
        delayMicroseconds(2);
    }
    BroadcastData(frame_test, len);
    delayMicroseconds(2200);
  }
  time2 = micros();

  Serial.println();
  Serial.print("Sent Bits: ");
  Serial.print(sent * 8 * 245);
  Serial.println();
  Serial.print("Time: ");
  Serial.print(time2-time1);
  sent = 0;





  
}
