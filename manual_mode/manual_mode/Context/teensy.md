int counter = 1; // Start counting from 1

void setup() {
  // Initialize the USB serial communication
  Serial.begin(115200); 
}

void loop() {
  // Only send if we haven't reached 100 yet
  if (counter <= 100) {
    // Send the number to the laptop
    Serial.println(counter);
    
    // Increase the counter by 1 for the next loop
    counter++;
    
    // Wait for 1 second (1000 milliseconds)
    delay(1000); 
  }
}