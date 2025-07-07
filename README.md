# 🔐 UltiLock Smart Door Security System

An advanced Arduino-based smart door security system that combines password authentication, ultrasonic motion detection, and servo-controlled door locking mechanisms for comprehensive home and office security.

![UltiLock System](https://img.shields.io/badge/Arduino-Compatible-brightgreen)
![License](https://img.shields.io/badge/License-MIT-blue)
![Version](https://img.shields.io/badge/Version-1.0-orange)

## 🚀 Features

- **🔐 Password Authentication**: 4-digit PIN code system with visual feedback
- **📱 Keypad Interface**: 4x4 matrix keypad for secure password entry
- **📺 LCD Display**: Real-time status updates and user feedback
- **🔊 Audio Alerts**: Buzzer notifications for various security events
- **🛡️ Motion Detection**: Ultrasonic sensor for intruder detection
- **⚙️ Servo Control**: Automated door locking/unlocking mechanism
- **🔄 Dual Servo Support**: Primary lock + secondary mechanism capability
- **🛠️ Manual Override**: Testing and emergency access controls

## 🛠️ Hardware Requirements

### Components List
- **Arduino Board** (Uno/Nano/Mega compatible)
- **4x4 Matrix Keypad** for password input
- **16x2 I2C LCD Display** for status messages
- **HC-SR04 Ultrasonic Sensor** for motion detection
- **2x Servo Motors** (SG90 or similar) for door locking mechanisms
- **Buzzer** for audio alerts
- **Breadboard** for prototyping
- **Jumper Wires** for connections
- **Power Supply** (5V/2A recommended)

### Pin Configuration

| Component | Pin | Description |
|-----------|-----|-------------|
| **Servo 1** | A0 | Main door lock mechanism |
| **Servo 2** | A1 | Secondary mechanism |
| **Buzzer** | 13 | Audio alerts |
| **Ultrasonic Trig** | 12 | Trigger pin |
| **Ultrasonic Echo** | 11 | Echo pin |
| **Keypad Rows** | 2,3,4,5 | Row pins |
| **Keypad Cols** | 6,7,8,9 | Column pins |
| **LCD** | I2C | Address: 0x27 |

## 📋 Installation & Setup

### 1. Hardware Assembly

1. **Connect the Keypad**:
   - Connect row pins to Arduino pins 2, 3, 4, 5
   - Connect column pins to Arduino pins 6, 7, 8, 9

2. **Connect the LCD Display**:
   - VCC → 5V
   - GND → GND
   - SDA → A4 (or SDA pin)
   - SCL → A5 (or SCL pin)

3. **Connect the Ultrasonic Sensor**:
   - VCC → 5V
   - GND → GND
   - Trig → Pin 12
   - Echo → Pin 11

4. **Connect the Servos**:
   - Servo 1: Signal → A0, VCC → 5V, GND → GND
   - Servo 2: Signal → A1, VCC → 5V, GND → GND

5. **Connect the Buzzer**:
   - Positive → Pin 13
   - Negative → GND

### 2. Software Setup

1. **Install Required Libraries**:
   ```bash
   # In Arduino IDE: Tools → Manage Libraries
   - Servo
   - LiquidCrystal_I2C
   - Keypad
   - Password
   ```

2. **Upload the Code**:
   - Open `UltiLock.ino` in Arduino IDE
   - Select your board and port
   - Click Upload

## 🎯 Usage Instructions

### Default Settings
- **Default Password**: `1234`
- **Lock Distance**: 10cm (ultrasonic trigger)
- **Max Password Length**: 6 digits

### System Operation

1. **Power On**: System displays "WELCOME TO DOOR LOCK SYSTEM"

2. **Unlocked State**:
   - LCD shows "D to locked" and "Door is unlocked"
   - Press 'D' to manually lock the door

3. **Locked State**:
   - LCD prompts "ENTER PASSWORD"
   - Enter 4-digit password using keypad
   - '*' characters show password entry progress

4. **Password Entry**:
   - Enter digits 0-9 for password
   - Press 'C' to clear/reset password
   - Press 'D' for manual lock/unlock toggle

5. **Motion Detection**:
   - Ultrasonic sensor monitors for movement
   - Automatically locks door when motion detected within 10cm
   - Triggers intruder alert with buzzer and LCD message

### Keypad Layout
```
┌─────────┐
│ D │ C │ B │ A │
├─────────┤
│ # │ 9 │ 6 │ 3 │
├─────────┤
│ 0 │ 8 │ 5 │ 2 │
├─────────┤
│ * │ 7 │ 4 │ 1 │
└─────────┘
```

## 🔧 Customization

### Change Default Password
```cpp
// Line 25 in UltiLock.ino
Password password = Password("1234"); // Change "1234" to your desired password
```

### Adjust Motion Sensitivity
```cpp
// Line 8 in UltiLock.ino
#define lockDistance 10 // Change 10 to desired distance in cm
```

### Modify Servo Positions
```cpp
// Lock position (line ~100)
servo1.write(0); // Adjust angle for locked position

// Unlock position (line ~120)
servo1.write(95); // Adjust angle for unlocked position
```

### Customize Alert Patterns
```cpp
// Modify buzzer patterns in intruderAlert() function
digitalWrite(buzzer, HIGH);
delay(1000); // Adjust duration
digitalWrite(buzzer, LOW);
```

## 🛡️ Security Features

### Authentication System
- **4-digit PIN protection**
- **Visual password masking** with '*' characters
- **Automatic lockout** after failed attempts
- **Password reset** functionality

### Motion Detection
- **Real-time monitoring** with ultrasonic sensor
- **Configurable detection distance**
- **Automatic door locking** on motion detection
- **Intruder alert system**

### System States
- **Locked**: Requires password for access
- **Unlocked**: Door accessible, motion monitoring active
- **Alert**: Intruder detected, audio/visual warnings

## 🔍 Troubleshooting

### Common Issues

1. **LCD Not Displaying**:
   - Check I2C address (default: 0x27)
   - Verify wiring connections
   - Ensure proper power supply

2. **Keypad Not Responding**:
   - Verify row/column pin connections
   - Check for loose wires
   - Test individual keys

3. **Servo Not Moving**:
   - Check power supply (servos need adequate current)
   - Verify signal pin connections
   - Test servo angles in code

4. **Ultrasonic Sensor Issues**:
   - Ensure proper trig/echo pin connections
   - Check for obstructions in sensor path
   - Verify sensor orientation

### Debug Information
The system outputs distance readings to Serial Monitor:
```
Distance: 15
Distance: 12
Object detected: Triggering lock!
```

## 📚 Dependencies

| Library | Purpose | Installation |
|---------|---------|--------------|
| `Servo.h` | Servo motor control | Built-in Arduino library |
| `LiquidCrystal_I2C.h` | LCD display interface | Arduino Library Manager |
| `Keypad.h` | Matrix keypad handling | Arduino Library Manager |
| `Password.h` | Password management | Arduino Library Manager |

## 🎓 Educational Value

This project demonstrates:
- **IoT Security Concepts**
- **Sensor Integration**
- **User Interface Design**
- **Real-time System Programming**
- **Hardware-Software Integration**

Perfect for:
- **Arduino Learning Projects**
- **IoT Security Demonstrations**
- **Home Automation Studies**
- **Embedded Systems Education**

## 🤝 Contributing

Contributions are welcome! Please feel free to submit a Pull Request. For major changes, please open an issue first to discuss what you would like to change.

### Development Setup
1. Fork the repository
2. Create a feature branch (`git checkout -b feature/AmazingFeature`)
3. Commit your changes (`git commit -m 'Add some AmazingFeature'`)
4. Push to the branch (`git push origin feature/AmazingFeature`)
5. Open a Pull Request

## 🙏 Acknowledgments

- Arduino community for excellent documentation
- Open-source library developers
- Makers and DIY enthusiasts worldwide

## 📞 Support

If you encounter any issues or have questions:
- Open an issue on GitHub
- Check the troubleshooting section above
- Review Arduino documentation for component-specific help

---

**Made with ❤️ for the Arduino community**

*UltiLock - Smart Security for Smart Homes* 🔐✨ 
