# 🤖 Ardubots – EcoLink (Environmental Monitoring Bot, LoRaWAN-Enabled)

A smart Arduino-based environmental monitoring bot that detects **smoke**, measures **temperature**, and calculates **PM2.5 dust density**, with **LoRaWAN** communication for long-range, low-power data transmission. Also supports **Bluetooth debugging** and a **buzzer alarm** for local alerts. Built for Hackathons, rapid IoT prototyping, and real-world deployment in smart cities, agriculture, and industry.

---

## 🚀 Features

- 🔥 **Smoke Detection** using MQ-2 Sensor  
- 🌡️ **Temperature Measurement** using LM35  
- 🌫️ **Air Quality Monitoring (PM2.5)** using GP2Y1010AU0F Dust Sensor  
- 📡 **LoRaWAN Data Transmission** (via RA-02/SX1278 or compatible modules)  
- 🌐 Compatible with **The Things Network (TTN)**  
- 🔊 **Buzzer Alert** for smoke events  
- 📲 Optional **Bluetooth Debugging** via HC-05/HC-06  
- 🖥️ **Serial Monitoring** for live feedback

---

## 🧰 Hardware Required

| Component                    | Quantity |
|------------------------------|----------|
| Arduino UNO / Nano / MKR     | 1        |
| MQ-2 Gas Sensor              | 1        |
| LM35 Temperature Sensor      | 1        |
| GP2Y1010AU0F Dust Sensor     | 1        |
| RA-02 / SX1276/8 LoRa Module | 1        |
| HC-05 Bluetooth Module (Optional) | 1   |
| Buzzer (5V)                  | 1        |
| 220Ω Resistor                | 1        |
| Breadboard + Jumper Wires    | As needed |

---

## ⚡ Circuit Diagram

'Ardubots/Circuit Diagram.png'

**Wiring Highlights:**

| Arduino Pin | Connected To           |
|-------------|------------------------|
| A0          | MQ-2 Analog Output     |
| A4          | Dust Sensor Output     |
| D2          | Dust Sensor LED Driver |
| A1 / A2     | LM35 Output (Analog)   |
| D10         | HC-05 RX (via divider) |
| D11         | HC-05 TX               |
| D13         | Buzzer                 |
| D5          | LoRa NSS (CS)          |
| D6          | LoRa RESET             |
| D7          | LoRa DIO0              |
| D11         | LoRa MOSI (SPI)        |
| D12         | LoRa MISO (SPI)        |
| D13         | LoRa SCK (SPI)         |

---

## 🌐 LoRaWAN Integration

- Uses **MCCI LoRaWAN LMIC** library (OTAA or ABP)
- Compatible with **The Things Network (TTN)**
- Sends periodic sensor data (encoded as bytes or JSON)
- Power-efficient communication ideal for remote sensing

### 🛠 LoRaWAN Settings Example

```cpp
static const u1_t PROGMEM APPEUI[8] = { ... };
static const u1_t PROGMEM DEVEUI[8] = { ... };
static const u1_t PROGMEM APPKEY[16] = { ... };
