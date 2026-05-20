# 🌤️ WeatherStation

A full-stack IoT weather monitoring system — collect real-time temperature and pressure data from a BMP280 sensor via ESP32 and visualize it through a live web dashboard.

Built with Java & Spring Boot on the backend, vanilla HTML/CSS/JavaScript on the frontend, and C++ on the ESP32 microcontroller.

🌐 Live Demo: https://narcis47.github.io/WeatherStation/
---

## 📸 Dashboard Preview

<!-- Replace the line below with your actual screenshot -->
![WeatherStation Dashboard](https://i.imgur.com/aYtnQc8.png)

> *Live dashboard showing real-time temperature and pressure readings from a BMP280 sensor connected to an ESP32. The spike visible in the temperature graph was caused by placing a hand on the sensor.*

---

## 🚧 Project Status

| Component | Status |
|---|---|
| Backend (Spring Boot) | ✅ Complete |
| Frontend (Dashboard) | ✅ Complete |
| ESP32 + BMP280 Integration | ✅ Complete |
| Multi-sensor Support | 📅 Planned |

---

## ✨ Features

- 📡 REST API to receive sensor data from ESP32
- 🌡️ Store temperature and pressure readings in PostgreSQL
- 🕐 Retrieve the most recent reading
- 📊 Retrieve all historical readings
- 📖 Swagger UI for API documentation and testing
- 📈 Live dashboard with temperature and pressure charts
- 🔄 Auto-refresh every 30 seconds
- 📋 Recent readings table with daily min/max stats
- 🔌 ESP32 auto-connects to predefined WiFi or scans for open networks

---

## 🛠️ Tech Stack

| Layer | Technology |
|---|---|
| Language | Java 21 |
| Framework | Spring Boot 3.2.5 |
| Database | PostgreSQL |
| Database Mapper | Spring Data JDBC |
| API Docs | Swagger UI (SpringDoc OpenAPI) |
| Sensor | BMP280 (temperature + pressure) |
| Microcontroller | ESP32 |
| Firmware | Arduino IDE (C++) |
| Frontend | HTML, CSS, JavaScript + Chart.js |
| Build Tool | Maven |

---

## 📁 Project Structure

```
WeatherStation/
├── src/main/java/narcis/weatherStation/
│   ├── controller/
│   │   └── DataController.java    ← /api/data
│   ├── service/
│   │   └── DataService.java
│   ├── repository/
│   │   └── DataRepository.java
│   ├── model/
│   │   └── Data.java
│   ├── SecurityConfig.java        ← CORS configuration
│   └── WeatherStationApplication.java
├── src/main/resources/
│   └── application.properties
├── esp32/
│   └── esp32.ino         ← ESP32 firmware
└── docs/
    └── index.html                 ← Dashboard frontend
```

---

## 🔌 API Endpoints

| Method | Endpoint | Description |
|---|---|---|
| POST | `/api/data/add` | Add a new sensor reading |
| GET | `/api/data/getLast` | Get the most recent reading |
| GET | `/api/data/getAll` | Get all historical readings |

---

## 📖 API Documentation

Swagger UI available at:
```
http://localhost:8082/swagger-ui/index.html
```

---

## 🗄️ Database Schema

```sql
CREATE TABLE weatherdata (
    id SERIAL PRIMARY KEY,
    temp FLOAT NOT NULL,
    pressure FLOAT NOT NULL,
    updated_at TIMESTAMP DEFAULT CURRENT_TIMESTAMP
);
```

---

## 🔧 Hardware

| Component | Details |
|---|---|
| Microcontroller | ESP32 (any variant) |
| Sensor | BMP280 — temperature + pressure |
| Connection | I2C (address `0x76` or `0x77`) |
| Power | USB power bank or 5V adapter |

### Wiring

```
BMP280  →  ESP32
VCC     →  3.3V
GND     →  GND
SDA     →  GPIO 21
SCL     →  GPIO 22
```

---

## 🚀 Setup & Installation

### Prerequisites
- Java 21
- PostgreSQL
- Maven
- Arduino IDE with ESP32 board support
- Adafruit BMP280 library

### Backend Setup

**1. Clone the repository**
```bash
git clone https://github.com/Narcis47/WeatherStation.git
cd WeatherStation
```

**2. Create the PostgreSQL database**
```sql
CREATE DATABASE weather_station;
```

**3. Run the schema**
```sql
CREATE TABLE weatherdata (
    id SERIAL PRIMARY KEY,
    temp FLOAT NOT NULL,
    pressure FLOAT NOT NULL,
    updated_at TIMESTAMP DEFAULT CURRENT_TIMESTAMP
);
```

**4. Set environment variables**
```
DB_USERNAME=your_postgres_username
DB_PASSWORD=your_postgres_password
```

**5. Run the backend**
```bash
./mvnw spring-boot:run
```

### ESP32 Setup

**1.** Open `esp32/esp32.ino` in Arduino IDE

**2.** Configure your credentials at the top of the file:
```cpp
const String WIFI_SSID     = "your_wifi_name";
const String WIFI_PASSWORD = "your_wifi_password";
const String BACKEND_URL   = "http://YOUR_IP:8082/api/data/add";
```

**3.** Upload to your ESP32

**4.** Open Serial Monitor at **115200 baud** to see debug output

### Frontend Setup

Open `docs/index.html` with Live Server — the dashboard connects automatically to the backend.

---

## 📝 Example API Requests

**Add sensor reading**
```json
POST /api/data/add
{
    "temp": 23.5,
    "pressure": 1013.2
}
```

**Get latest reading**
```
GET /api/data/getLast
```

**Get all readings**
```
GET /api/data/getAll
```

---

## 🔮 Roadmap

### Phase 4 — Multi-sensor Support
- Support for multiple ESP32 devices
- Each sensor has a unique ID and location name
- Filter data by sensor
- Compare readings across locations
- Support for additional sensors (DHT22 for humidity, etc.)

---

## 🤖 AI Assistance

The frontend dashboard (`docs/index.html`) was built with the assistance of Claude AI (Anthropic). The backend, database schema, and ESP32 firmware were designed and implemented manually.

---

## 👤 Author

**Narcis** — [@Narcis47](https://github.com/Narcis47)