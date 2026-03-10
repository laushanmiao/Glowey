# Glowey: Proximity-Aware Smart Lighting System 🌟

**Glowey** is an automated lighting and digital signage solution designed to eliminate the "dark-or-glare" paradox. By using proximity-aware sensors, the system dynamically adjusts lighting based on a person’s precise distance, improving pedestrian safety while significantly reducing energy waste and light pollution.

---

### 🚀 Problem Statement

Traditional lighting systems often suffer from being dangerously under-lit to save costs or aggressively over-lit $24/7$, leading to visual glare for commuters and massive electricity waste. Glowey replaces these static systems with a responsive environment that ensures a safe, comfortable journey for every step.

---

### ✨ Key Features

* **Sequential Distance Detection**: LEDs activate consequently as a person approaches.


* **Long-Range Sensing**: Utilizes an **HC-SR04 Ultrasonic sensor** to detect approaching individuals from a distance.


* **Precision Activation**: An **IR sensor** confirms close-range presence for precise activation of components like advertisement boards.


* **Energy Efficiency**: Automated control ensures lights are only "on" when needed, saving power.

---

### 🛠️ Technical Specifications

#### Hardware Components

* **Microcontroller**: Arduino Nano (ATmega328P).
* Operating Voltage: 5V DC.
* Clock Speed: 16 MHz.

* **Ultrasonic Sensor (HC-SR04)**:
* Detection Range: 2–400 cm.
* Accuracy: $\pm3$ mm.
  
* **IR Sensor**: Used for precise close-range presence detection.
  
* **LEDs + Resistors**: Provide safe lighting without overloading the circuit.


#### 📌 Pin Configuration

Based on the `Glowey.ino` source code:

| Component | Pin | Function |
| --- | --- | --- |
| **IR Sensor** | D2 | Input signal 


| **LED (IR)** | D7 | Close-range indicator 


| **Ultrasonic TRIG** | D6 | Trigger pulse 


| **Ultrasonic ECHO** | D4 | Echo pulse 


| **LED Range 1** | D9 | Activation for 0–15 cm 


| **LED Range 2** | D11 | Activation for 7–23 cm 


| **LED Range 3** | D12 | Activation for 15–30 cm 



---

### ⚙️ How It Works

1. **Detection**: The HC-SR04 sends ultrasonic waves and measures the echo time to calculate the distance of an approaching person.


2. **Processing**: The Arduino Nano processes these signals using the formula:



$$Distance = \frac{duration \times 0.0343}{2}$$


3. **Activation**:
* As the person moves through specific distance ranges (0–30 cm), corresponding LEDs trigger sequentially to light the path.
* When an object is detected by the IR sensor, the IR LED activates for a set duration of 3 seconds.





---

### 💻 Installation & Usage

1. **Clone the repository**:
```bash
git clone https://github.com/yourusername/Glowey.git

```


2. **Hardware Setup**: Follow the circuit design to connect your sensors and LEDs to the Arduino Nano.


3. **Upload Code**: Open `Glowey.ino` in the Arduino IDE and upload it to your board.


4. **Monitor**: Open the Serial Monitor (9600 baud) to view real-time distance data for debugging.



---

### 👥 About the Team

Presented by **Photon Engineers**.
