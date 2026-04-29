# 🚗 ARM-Based Real-Time Digital Automotive Instrument Cluster with CAN Protocol Integration

## 📌 Overview

This project implements a **real-time automotive instrument cluster system** using the **LPC2129 ARM7 microcontroller** with **CAN (Controller Area Network) protocol**.

The system consists of **two nodes**:

* **Node A (Transmitter)** → Reads sensor data and sends via CAN
* **Node B (Receiver)** → Receives data, displays it on LCD, and controls indicators

This project demonstrates how modern automotive systems use CAN to reduce wiring complexity, improve reliability, and enable real-time communication.

---

## 🧠 System Architecture

```text
Node A (Sensor Node)  --->  CAN Bus  --->  Node B (Instrument Cluster)
```

---

## ⚙️ Node A – Transmitter (Sensor Unit)

### 🔹 Functionality:

* Reads analog inputs using ADC:

  * Temperature sensor
  * Speed input
* Detects user inputs:

  * Headlight toggle
  * Left/Right indicators
* Sends CAN messages with different IDs

### 🔹 Key Operations:

* ADC-based sensor reading
* Interrupt-based switch handling
* CAN transmission using `can2_tx()`

### 🔹 Example:

```c
M1.ID = SPEED_ID;
M1.BYTEA = adc_read(2);
can2_tx(M1);
```

👉 Continuously transmits:

* Temperature
* Speed
* Headlight status
* Indicator status

---

## 📟 Node B – Receiver (Instrument Cluster)

### 🔹 Functionality:

* Receives CAN messages using interrupt
* Displays:

  * Speed on LCD
  * Temperature on LCD
* Controls LEDs:

  * Headlights
  * Left indicator
  * Right indicator

### 🔹 Key Operations:

* Interrupt-driven CAN reception
* Data conversion from ADC to real values

### 🔹 Example:

```c
spd = (M1.BYTEA * 280) / 1023;
```

```c
temp = (M1.BYTEA * 3.3) / 1023;
result = (temp - 0.5) / 0.01;
```

---

## 🔌 Pin Configuration (LPC2129)

### 🧩 Node A (Transmitter)

| Peripheral       | LPC2129 Pin        | Description                 |
| ---------------- | ------------------ | --------------------------- |
| Temperature ADC  | P0.28 (AD0.1)      | Temperature sensor input    |
| Speed ADC        | P0.29 (AD0.2)      | Speed input (potentiometer) |
| Headlight Switch | External Interrupt | Toggle headlight            |
| Indicator Switch | External Interrupt | Left/Right indicator        |
| CAN TX           | P0.10 (TXD2)       | CAN transmit                |
| CAN RX           | P0.11 (RXD2)       | CAN receive                 |

---

### 🧩 Node B (Receiver)

| Peripheral       | LPC2129 Pin | Description                |
| ---------------- | ----------- | -------------------------- |
| LCD Data Pins    | P0.xx       | LCD interface (4-bit mode) |
| LCD Control Pins | P0.xx       | RS, EN control             |
| Headlight LED    | P0.18       | Indicates headlight status |
| Left Indicator   | P0.17       | Left indicator LED         |
| Right Indicator  | P0.19       | Right indicator LED        |
| CAN TX           | P0.10       | CAN transmit               |
| CAN RX           | P0.11       | CAN receive                |

---

## 🔗 CAN Bus Connection

```text
Node A ---- CAN Transceiver ---- CAN Bus ---- CAN Transceiver ---- Node B
```

* CANH → CANH
* CANL → CANL
* Common GND required

---

## 🛠️ Technologies Used

* **Microcontroller:** LPC2129 (ARM7)
* **Language:** Embedded C
* **Protocol:** CAN (Controller Area Network)
* **Peripherals:**

  * ADC
  * GPIO (LEDs, switches)
  * LCD (16x2)
  * CAN Controller + Transceiver

---

## 🔄 CAN Message IDs

| Parameter   | CAN ID         |
| ----------- | -------------- |
| Temperature | TEMPERATURE_ID |
| Speed       | SPEED_ID       |
| Headlight   | HEADLIGHT_ID   |
| Indicators  | INDICATOR_ID   |

---

## 🚀 Features

* Real-time CAN communication
* Multi-node architecture (Node A & Node B)
* Interrupt-driven data handling
* Live display of vehicle parameters
* LED-based indicator system
* Reduced wiring using CAN bus

---

## 📂 Project Structure

```text
├── node_A_main.c
├── node_B_main.c
├── can_driver.c
├── adc_driver.c
├── lcd_driver.c
├── interrupt.c
├── header.h
├── README.md
```

---

## ▶️ How to Run

### 🔧 Hardware Required:

* 2 × LPC2129 boards
* CAN Transceiver (e.g., MCP2551)
* 16x2 LCD
* LEDs & switches
* Potentiometer (for ADC simulation)

### ⚙️ Steps:

1. Flash Node A code into transmitter board
2. Flash Node B code into receiver board
3. Connect CANH and CANL between nodes
4. Provide common ground
5. Power ON both systems
6. Observe real-time output on LCD

---

## 📈 Advantages

* Reduced wiring complexity
* High reliability communication
* Real-time monitoring
* Scalable architecture

---

## 🔮 Future Enhancements

* Add TFT graphical display
* Integrate RTOS (FreeRTOS)
* Add more sensors (fuel, RPM, etc.)
* Wireless monitoring using ESP32

---

## 👨‍💻 Author

**Rohit Sanjay Jagdale**
Embedded Systems Engineer (Aspiring)

---

## ⭐ Key Learning Outcomes

* CAN protocol implementation
* ARM7 (LPC2129) programming
* Interrupt handling
* ADC interfacing and data conversion
* Multi-node embedded system design

---
