# Teensy Telemetry Listener Script

This is a Python script using `pyserial` to connect to your Teensy and print the exact telemetry data that it publishes over Serial.

### Prerequisites

Make sure you have the `pyserial` library installed on your laptop:
```bash
pip install pyserial
```

### Python Script (`listener.py`)

Save the following code as `listener.py` and run it with `python3 listener.py`:

```python
import serial
import time

# --- CONFIGURATION ---
SERIAL_PORT = '/dev/ttyACM0'  # Make sure this matches your Teensy's port
BAUD_RATE = 115200

def main():
    try:
        # Open the serial connection
        ser = serial.Serial(SERIAL_PORT, BAUD_RATE, timeout=1)
        print(f"Connected to Teensy on {SERIAL_PORT} at {BAUD_RATE} baud.\n")
        print("Listening for telemetry data...\n")
        print("-" * 50)
        
        # Continuously read and print data
        while True:
            if ser.in_waiting > 0:
                # Read line, decode, and strip extra whitespace/newlines
                incoming_data = ser.readline().decode('utf-8', errors='ignore').strip()
                
                if incoming_data:
                    print(f"Teensy: {incoming_data}")
                    
            # Small sleep to prevent 100% CPU usage
            time.sleep(0.01)

    except serial.SerialException as e:
        print(f"\nError opening serial port: {e}")
        print("Please ensure:")
        print("1. The Teensy is plugged in.")
        print("2. The port name is correct.")
        print("3. The Arduino Serial Monitor is closed.")
    except KeyboardInterrupt:
        print("\n\nStopped listening. Exiting...")
    finally:
        if 'ser' in locals() and ser.is_open:
            ser.close()
            print("Serial connection closed.")

if __name__ == '__main__':
    main()
```
