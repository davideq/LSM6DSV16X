#include "I3C.h"
#include "LSM6DSV16XSensor.h"

LSM6DSV16XSensor sensor(&I3C);

void setup() {
  Serial.begin(115200);
  while (!Serial) {}
  delay(1000);

  Serial.println("=== LSM6DSV16X DAA ===");

  if (!I3C.begin(I3C_SDA, I3C_SCL, 1000000U)) {
    Serial.println("begin() failed");
    while (1) {}
  }

  if (!I3C.resetDynamicAddresses()) {
    Serial.println("resetDynamicAddresses() failed");
    while (1) {}
  }

  I3CDiscoveredDevice devices[8] = {};
  size_t found = 0;

  if (I3C.discover(devices, 8, &found)) {
    Serial.println("discover() failed");
    while (1) {}
  }

  Serial.print("Devices found: ");
  Serial.println(found);

  uint8_t lsmDynAddr = 0U;

  for (size_t i = 0; i < found; ++i) {
    Serial.print("[");
    Serial.print(i);
    Serial.print("] PID=0x");
    Serial.print((uint32_t)(devices[i].pid >> 32), HEX);
    Serial.print((uint32_t)(devices[i].pid & 0xFFFFFFFFULL), HEX);
    Serial.print(" DYN=0x");
    Serial.println(devices[i].dynAddr, HEX);

    if ((devices[i].pid == LSM6DSV16X_I3C_PID_H) || (devices[i].pid == LSM6DSV16X_I3C_PID_L)) {
      lsmDynAddr = devices[i].dynAddr;
    }
  }

  if (lsmDynAddr == 0U) {
    Serial.println("Sensor not found");
    while (1) {}
  }

  if (sensor.set_address(lsmDynAddr) != LSM6DSV16X_OK) {
    Serial.println("set_address() failed");
    while (1) {}
  }

  if (sensor.begin() != LSM6DSV16X_OK) {
    Serial.println("sensor.begin() failed");
    while (1) {}
  }

  if (!I3C.setClock(12500000)) {
    Serial.println("setClock() failed");
    while (1) {}
  }

  if (sensor.Enable_X() != LSM6DSV16X_OK) {
    Serial.println("sensor.Enable_X() failed");
    while (1) {}
  }

  if (sensor.Enable_G() != LSM6DSV16X_OK) {
    Serial.println("sensor.Enable_G() failed");
    while (1) {}
  }

  Serial.println("LSM6DSV16X ready");
}

void loop() {
  int32_t accel[3] = {0};
  int32_t angrate[3] = {0};

  if (sensor.Get_X_Axes(accel) == LSM6DSV16X_OK && sensor.Get_G_Axes(angrate) == LSM6DSV16X_OK) {
    Serial.print("Accel-X[mg]:");
    Serial.print(accel[0]);
    Serial.print(",Accel-Y[mg]:");
    Serial.print(accel[1]);
    Serial.print(",Accel-Z[mg]:");
    Serial.println(accel[2]);

    Serial.print("AngRate-X[mdps]:");
    Serial.print(angrate[0]);
    Serial.print(",AngRate-Y[mdps]:");
    Serial.print(angrate[1]);
    Serial.print(",AngRate-Z[mdps]:");
    Serial.println(angrate[2]);
  } else {
    Serial.println("Read failed");
  }

  delay(500);
}
