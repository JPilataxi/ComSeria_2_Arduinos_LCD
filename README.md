# Comunicación Serial entre dos Arduino UNO

## 1. Descripción del proyecto

Implementación de comunicación serial UART entre dos placas Arduino UNO.

El sistema está compuesto por dos dispositivos:

- **Arduino1 (Receptor):** recibe los datos mediante UART, procesa la trama y muestra las lecturas en un LCD de 16x2 con interfaz I2C.
- **Arduino2 (Transmisor):** realiza la lectura de dos canales del ADC (A0 y A1) y transmite los valores mediante comunicación serial UART.

## 2. Simulación en Tinkercad

La implementación del sistema puede visualizarse y ejecutarse mediante la siguiente simulación:

[**Abrir simulación en Tinkercad**](https://www.tinkercad.com/things/4BGgpZpLw8s-seriali2clcd?sharecode=4-LvlIxjnY1oO80tZ50gsSHgX_gXdf384XthgDhhlnw)

En la simulación se uso otra librería para controlar el LCD.
## 3. Estructura del proyecto

```text
ComSeria_2_Arduino/
│
├── Arduino1/
│   └── src/
│       └── main.cpp
│
├── Arduino2/
│   └── src/
│       └── main.cpp
│
├── include/
├── lib/
├── test/
│
├── platformio.ini
└── README.md
```

## 4. Configuración del entorno

El proyecto utiliza:

- Visual Studio Code.
- PlatformIO IDE.
- Framework Arduino.
- Dos placas Arduino UNO (ATmega328P).
- Biblioteca LiquidCrystal_I2C.

## 5. Configuración de la comunicación

| Parámetro | Configuración |
|---|---|
| Protocolo | UART |
| Velocidad | 9600 baudios |
| Formato | 8 bits, sin paridad, 1 bit de parada |
| Tipo de dato | Byte (`uint8_t`) |
| Rango transmitido | 0–200 |


Cada lectura ADC se convierte a un porcentaje entre 0 y 100 %. Los canales se identifican mediante un desplazamiento de 100 unidades:

- **ADC0:** se transmite directamente el porcentaje (0–100).
- **ADC1:** se transmite el porcentaje sumado a 100 (100–200).

Cada dato se transmite individualmente, sin separadores ni terminadores de trama adicionales.

Ejemplos:

| Canal | Porcentaje | Byte transmitido |
|---|---:|---:|
| ADC0 | 25 % | 25 |
| ADC0 | 80 % | 80 |
| ADC1 | 25 % | 125 |
| ADC1 | 80 % | 180 |

En el receptor, los valores entre 0 y 100 corresponden al ADC0, mientras que los valores entre 101 y 200 corresponden al ADC1. Para recuperar el porcentaje del segundo canal se resta 100 al dato recibido.



## 6. Conexiones

### Arduino1 – Receptor

| Elemento | Pin Arduino |
|---|---|
| RX | D0 |
| LCD SDA | A4 |
| LCD SCL | A5 |
| LCD VCC | 5V |
| LCD GND | GND |

### Arduino2 – Transmisor

| Elemento | Pin Arduino |
|---|---|
| Potenciómetro 1 (cursor) | A0 |
| Potenciómetro 2 (cursor) | A1 |
| TX | D1 |

### Comunicación entre placas

| Arduino1 (Receptor) | Arduino2 (Transmisor) |
|---|---|
| RX (D0) | TX (D1) |
| GND | GND |

**Importante:** las conexiones TX/RX deben realizarse de forma cruzada. Se debe desconectar temporalmente la comunicación UART entre las placas durante la carga de los programas mediante USB.

## 7. Compilación y programación

Desde la terminal integrada de VS Code:

### Compilar Arduino1 (Receptor)

```bash
pio run -e arduino1
```

### Compilar Arduino2 (Transmisor)

```bash
pio run -e arduino2
```

### Cargar programa en Arduino1

```bash
pio run -e arduino1 -t upload
```

### Cargar programa en Arduino2

```bash
pio run -e arduino2 -t upload
```

Si existen varias placas conectadas, se puede especificar el puerto:

```bash
pio run -e arduino1 -t upload --upload-port COM3
```

Reemplazar `COM3` por el puerto correspondiente.

## 8. Funcionamiento esperado

1. Arduino2 adquiere las lecturas de los canales ADC0 y ADC1.
2. Convierte cada lectura a un porcentaje entre 0 y 100 %.
3. Codifica los datos según el canal ADC.
4. Transmite individualmente cada byte mediante UART.
5. Arduino1 recibe e identifica el canal correspondiente.
6. Arduino1 actualiza la visualización en el LCD.

Ejemplo de visualización:

```text
ADC0: 50
ADC1: 45
```