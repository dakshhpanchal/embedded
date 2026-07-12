import serial

# --- CONFIGURATION ---
SERIAL_PORT = '/dev/ttyACM0' 
BAUD_RATE = 115200

try:
    # Open the serial connection
    ser = serial.Serial(SERIAL_PORT, BAUD_RATE, timeout=1)
    print(f"Listening to Teensy on {SERIAL_PORT}...\n")
    
    # Run an infinite loop to constantly check for incoming data
    while True:
        # Check if there is data waiting in the buffer
        if ser.in_waiting > 0:
            # Read the incoming line, decode it, and clean up extra spacing
            incoming_data = ser.readline().decode('utf-8').strip()
            
            # If the data isn't empty, print it
            if incoming_data:
                print(f"Laptop received: {incoming_data}")

except serial.SerialException as e:
    print(f"\nError opening serial port: {e}")
    print("Make sure the port is correct and the Arduino Serial Monitor is closed.")
except KeyboardInterrupt:
    print("\nScript stopped by user.")
finally:
    if 'ser' in locals() and ser.is_open:
        ser.close()
        print("Serial port closed.")