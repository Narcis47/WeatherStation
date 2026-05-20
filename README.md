# 🌤️ WeatherStation

A full-stack IoT weather monitoring system — collect real-time temperature and pressure data from a BMP280 sensor via ESP32 and visualize it through a web dashboard.

🌐 Live Demo: https://narcis47.github.io/WeatherStation/
---

## 🚧 Project Status

| Component | Status |
|---|---|
| Backend (Spring Boot) | ✅ Complete |
| Frontend (Dashboard) | ✅ Complete |
| ESP32 + BMP280 Integration | 📅 Planned |
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
| Frontend | HTML, CSS, JavaScript + Chart.js |
| Build Tool | Maven |

---

## 📁 Project Structure

```
weatherStation/
├── src/main/java/narcis/weatherStation/
│   ├── controller/
│   │   └── DataController.java    ← /api/data
│   ├── service/
│   │   └── DataService.java
│   ├── repository/
│   │   └── DataRepository.java
│   ├── model/
│   │   └── Data.java
│   ├── CorsConfig.java
│   └── WeatherStationApplication.java
├── src/main/resources/
│   └── application.properties
└── frontend/
    └── index.html                 ← Dashboard
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

## 🚀 Setup & Installation

### Prerequisites
- Java 21
- PostgreSQL
- Maven

### Steps

**1. Clone the repository**
```bash
git clone https://github.com/Narcis47/WeatherStation.git
cd WeatherStation
```

**2. Create the PostgreSQL database**
```sql
CREATE DATABASE weather_station;
```

**3. Run the schema** (copy SQL from above into DataGrip or psql)

**4. Set environment variables**

IntelliJ → Run/Debug Configurations → Environment Variables:
```
DB_USERNAME=your_postgres_username
DB_PASSWORD=your_postgres_password
```

**5. Run the backend**
```bash
./mvnw spring-boot:run
```

**6. Open the frontend**

Open `frontend/index.html` with Live Server — the dashboard connects automatically to `http://localhost:8082`.

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

### Phase 3 — ESP32 + BMP280 Integration
- ESP32 reads BMP280 data via I2C
- Sends POST request to backend every N seconds
- WiFi configuration
- Error handling and retry logic

### Phase 4 — Multi-sensor Support
- Support for multiple ESP32 devices
- Each sensor has a unique ID and location name
- Filter data by sensor
- Compare readings across locations
- Support for additional sensors (DHT22 for humidity, etc.)

---

## 🤖 AI Assistance

The frontend dashboard (`frontend/index.html`) was built with the assistance of Claude AI (Anthropic). The backend, database schema, and ESP32 integration were designed and implemented manually.

---

## 👤 Author

**Narcis** — [@Narcis47](https://github.com/Narcis47)