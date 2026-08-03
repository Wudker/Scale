# Load Cell Digital Scale

Load Cell Digital Scale is a compact standalone weighing device built around a strain-gauge load cell, HX711 converter and SSD1306 OLED display. The microcontroller converts the measured signal using an experimentally determined calibration factor and applies exponential filtering to reduce short-term fluctuations. Measurements are displayed in grams or kilograms, while automatic startup tare and a physical button provide zero adjustment. The electronics and weighing platform are integrated into a compact 3D-printed enclosure.

## Technologies

`Arduino` `C/C++` `Load cell` `HX711` `SSD1306 OLED` `Adafruit GFX` `I2C` `Exponential filtering` `3D printing`

## Usage and development status

Place the scale on a stable surface and power it on without any load to allow automatic taring. Use the physical button whenever manual re-taring is required, then place the object on the platform and read its mass from the display. The prototype has been built and tested, but broader validation is still required to evaluate repeatability, drift, nonlinearity and temperature effects. Future improvements may include overload detection and additional measurement compensation.
