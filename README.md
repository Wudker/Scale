# Load Cell Digital Scale

## Description

Load Cell Digital Scale is a compact electronic scale built using a strain gauge load cell, HX711 amplifier module and OLED display.

The main goal of the project was to create a simple standalone weighing device capable of measuring mass, displaying the result locally and allowing the user to tare the scale using a physical button.

The project is currently a working prototype. The basic measurement and display functions are implemented, but the device still requires proper validation and possible additional compensation to improve measurement accuracy and long-term stability.

## Features

* Mass measurement using a load cell
* HX711-based signal acquisition
* OLED user interface
* Manual tare button
* Automatic tare on startup
* LED status indicator
* Simple exponential filtering
* Displaying result in grams or kilograms
* Compact 3D printed enclosure

## Hardware

* Arduino-compatible microcontroller
* Strain gauge load cell
* HX711 amplifier / ADC module
* SSD1306 OLED display
* Tare push button
* Status LED
* 3D printed case and weighing platform

## Software

* C/C++
* Arduino framework
* HX711 library
* Adafruit SSD1306 library
* Adafruit GFX library
* I2C communication
* Basic signal filtering
* Serial output for debugging

## Measurement principle

The load cell changes its electrical output depending on the applied mechanical force. Because the signal is very small, it is amplified and converted to digital form using the HX711 module.

The microcontroller reads the value from the HX711, applies a calibration factor and displays the calculated mass on the OLED screen. A simple exponential filter is used to reduce rapid fluctuations in the measured value.

The scale can be reset to zero using the tare button. Taring is also performed automatically during startup.

## Calibration

The current calibration factor was determined experimentally using a known reference mass.

Further calibration is required to verify the scale across a wider measurement range and to check whether additional compensation is needed.

Possible sources of measurement error include:

* load cell nonlinearity,
* mechanical deformation of the platform,
* zero drift,
* temperature influence,
* unstable mounting of the load cell,
* noise in the measured signal.

## Challenges

Main development challenges:

* obtaining stable readings from the load cell,
* reducing noise and small fluctuations,
* mechanical mounting of the weighing platform,
* selecting a proper calibration factor,
* validating measurement accuracy,
* determining if software compensation is required.

## Current status

Working prototype built and tested.

The device can measure mass, display the result on the OLED screen and perform tare operation using a physical button.

Future improvements:

* full measurement validation,
* testing repeatability,
* overload detection,
* compensation for drift and nonlinear behavior.
