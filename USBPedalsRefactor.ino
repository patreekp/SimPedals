#include <Joystick.h>

// ===============================
// USER CONFIGURATION
// ===============================

// Usa autocalibrazione dinamica dei min/max
#define ENABLE_AUTOCALIBRATION true

// Usa la mappatura finale (raw → 0..1023)
// Se autocalibration è OFF, usa i range manuali
#define ENABLE_MAPPING true

// ===============================
// PIN CONFIG
// ===============================
constexpr int PIN_THROTTLE = A0;
constexpr int PIN_BRAKE    = A2;
constexpr int PIN_CLUTCH   = A1;

// ===============================
// RANGE MANUALI ORIGINALI
// Usati quando AUTOCALIBRATION = false
// ===============================
const int THR_MIN_RAW = 80;
const int THR_MAX_RAW = 380;

const int BRK_MIN_RAW = 100;
const int BRK_MAX_RAW = 1023;

const int CLU_MIN_RAW = 105;
const int CLU_MAX_RAW = 970;

// ===============================
// JOYSTICK CONFIG
// ===============================
Joystick_ Joystick(
  JOYSTICK_DEFAULT_REPORT_ID, JOYSTICK_TYPE_JOYSTICK,
  0, 0,
  false,
  false, false, false,
  true, false, false,
  true, false, true,
  false
);

// ===============================
// AUTOCALIBRATION STORAGE
// (usati SOLO se ENABLE_AUTOCALIBRATION = true)
// ===============================
int thrMin = 4095, thrMax = 0;
int brkMin = 4095, brkMax = 0;
int cluMin = 4095, cluMax = 0;

// ===============================
// FUNCTIONS
// ===============================
int readRaw(int pin) {
  int val = analogRead(pin);
  return (val < 1 ? 0 : val);
}

void updateAutoRange(int raw, int &minVal, int &maxVal) {
#if ENABLE_AUTOCALIBRATION
  if (raw < minVal) minVal = raw;
  if (raw > maxVal) maxVal = raw;
#endif
}

int mapValue(int raw, int minVal, int maxVal) {
#if ENABLE_MAPPING
  if (maxVal - minVal < 5) return raw;
  int mapped = map(raw, minVal, maxVal, 0, 1023);
  if (mapped < 0) mapped = 0;
  if (mapped > 1023) mapped = 1023;
  return mapped;
#else
  return raw;
#endif
}

// ===============================
// SETUP
// ===============================
void setup() {
  Joystick.begin();

#if ENABLE_AUTOCALIBRATION
  // Range finale = 0..1023 (mappatura attiva)
  Joystick.setThrottleRange(0, 1023);
  Joystick.setBrakeRange(0, 1023);
  Joystick.setRyAxisRange(0, 1023);
#else
  // Range manuali originali
  Joystick.setThrottleRange(THR_MIN_RAW, THR_MAX_RAW);
  Joystick.setBrakeRange(BRK_MIN_RAW, BRK_MAX_RAW);
  Joystick.setRyAxisRange(CLU_MIN_RAW, CLU_MAX_RAW);
#endif
}

// ===============================
// LOOP
// ===============================
void loop() {

  // -------- THROTTLE --------
  int thrRaw = readRaw(PIN_THROTTLE);

  if (ENABLE_AUTOCALIBRATION)
    updateAutoRange(thrRaw, thrMin, thrMax);

  int thrVal = ENABLE_AUTOCALIBRATION
               ? mapValue(thrRaw, thrMin, thrMax)
               : thrRaw;

  Joystick.setThrottle(thrVal);

  // -------- BRAKE --------
  int brRaw = readRaw(PIN_BRAKE);

  if (ENABLE_AUTOCALIBRATION)
    updateAutoRange(brRaw, brkMin, brkMax);

  int brVal = ENABLE_AUTOCALIBRATION
              ? mapValue(brRaw, brkMin, brkMax)
              : brRaw;

  Joystick.setBrake(brVal);

  // -------- CLUTCH --------
  int clRaw = readRaw(PIN_CLUTCH);

  if (ENABLE_AUTOCALIBRATION)
    updateAutoRange(clRaw, cluMin, cluMax);

  int clVal = ENABLE_AUTOCALIBRATION
              ? mapValue(clRaw, cluMin, cluMax)
              : clRaw;

  Joystick.setRyAxis(clVal);

  delay(10);
}
