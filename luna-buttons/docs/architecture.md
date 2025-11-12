# System Architecture

## Software Architecture
- **Firmware:** PlatformIO + Arduino framework
- **Button Detection:** Multiplexer-based input scanning
- **Audio Playback:** I2S audio output to MAX amplifier
- **Network:** WiFi connectivity for webhook calls
- **Event Logging:** HTTP POST to n8n webhook endpoint

## Workflow
1. Dog presses button (e.g., "potty")
2. ESP32 detects button press via multiplexer
3. Corresponding audio file plays through speaker
4. Event sent to n8n webhook on local Raspberry Pi
5. n8n logs event to DataTable
6. Telegram notification sent to owner
