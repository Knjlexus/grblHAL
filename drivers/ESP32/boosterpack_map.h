/*
  boosterpack_map.h - An embedded CNC Controller with rs274/ngc (g-code) support

  Driver code for ESP32

  Part of GrblHAL

  Copyright (c) 2020 Terje Io

  Grbl is free software: you can redistribute it and/or modify
  it under the terms of the GNU General Public License as published by
  the Free Software Foundation, either version 3 of the License, or
  (at your option) any later version.

  Grbl is distributed in the hope that it will be useful,
  but WITHOUT ANY WARRANTY; without even the implied warranty of
  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
  GNU General Public License for more details.

  You should have received a copy of the GNU General Public License
  along with Grbl.  If not, see <http://www.gnu.org/licenses/>.
*/

#define IOEXPAND 0

#if SDCARD_ENABLE

// Pin mapping when using SPI mode.
// With this mapping, SD card can be used both in SPI and 1-line SD mode.
// Note that a pull-up on CS line is required in SD mode.
#define PIN_NUM_MISO 19
#define PIN_NUM_MOSI 23
#define PIN_NUM_CLK  18
#define PIN_NUM_CS   5

#endif // SDCARD_ENABLE

// timer definitions
#define STEP_TIMER_GROUP TIMER_GROUP_0
#define STEP_TIMER_INDEX TIMER_0

// Define step pulse output pins.
#define X_STEP_PIN      GPIO_NUM_26
#define Y_STEP_PIN      GPIO_NUM_27
#define Z_STEP_PIN      GPIO_NUM_14
#define STEP_MASK       (1ULL << X_STEP_PIN|1ULL << Y_STEP_PIN|1ULL << Z_STEP_PIN) // All step bits

// Define step direction output pins. NOTE: All direction pins must be on the same port.
#define X_DIRECTION_PIN     GPIO_NUM_2
#define Y_DIRECTION_PIN     GPIO_NUM_15
#define Z_DIRECTION_PIN     GPIO_NUM_12
#define DIRECTION_MASK      (1ULL << X_DIRECTION_PIN|1ULL << Y_DIRECTION_PIN|1ULL << Z_DIRECTION_PIN) // All direction bits

// Define stepper driver enable/disable output pin(s).
#define STEPPERS_DISABLE_PIN    IOEXPAND
#define STEPPERS_DISABLE_MASK   (1ULL << STEPPERS_DISABLE_PIN)

// Define homing/hard limit switch input pins and limit interrupt vectors.
#define X_LIMIT_PIN     GPIO_NUM_4
#define Y_LIMIT_PIN     GPIO_NUM_16
#define Z_LIMIT_PIN     GPIO_NUM_32
#define LIMIT_MASK      (1ULL << X_LIMIT_PIN|1ULL << Y_LIMIT_PIN|1ULL << Z_LIMIT_PIN) // All limit bits

// Define spindle enable and spindle direction output pins.
#define SPINDLE_ENABLE_PIN      IOEXPAND
#define SPINDLE_DIRECTION_PIN   IOEXPAND
#define SPINDLE_MASK            (1ULL << SPINDLE_ENABLE_PIN|1ULL << SPINDLE_DIRECTION_PIN)
#define SPINDLEPWMPIN           GPIO_NUM_17

// Define flood and mist coolant enable output pins.

#define COOLANT_FLOOD_PIN   IOEXPAND
#define COOLANT_MIST_PIN    IOEXPAND
#define COOLANT_MASK        (1UL << COOLANT_FLOOD_PIN|1ULL << COOLANT_MIST_PIN)

// Define user-control CONTROLs (cycle start, reset, feed hold) input pins.
#define RESET_PIN           GPIO_NUM_35
#define FEED_HOLD_PIN       GPIO_NUM_39
#define CYCLE_START_PIN     GPIO_NUM_36
#define SAFETY_DOOR_PIN     GPIO_NUM_34
#define CONTROL_MASK        (1UL << RESET_PIN|1UL << FEED_HOLD_PIN|1UL << CYCLE_START_PIN|1UL << SAFETY_DOOR_PIN)

// Define probe switch input pin.
#define PROBE_PIN       GPIO_NUM_13

#if KEYPAD_ENABLE
#define KEYPAD_STROBE_PIN   GPIO_NUM_33
#endif

#if MPG_MODE_ENABLE
#define MPG_RX_PIN      GPIO_NUM_33
#define MPG_ENABLE_PIN  GPIO_NUM_25
#endif

#if IOEXPAND_ENABLE || KEYPAD_ENABLE || EEPROM_ENABLE || (TRINAMIC_ENABLE && TRINAMIC_I2C)
// Define I2C port/pins
#define I2C_PORT  I2C_NUM_1
#define I2C_SDA   GPIO_NUM_21
#define I2C_SCL   GPIO_NUM_22
#define I2C_CLOCK 100000
#endif

#if IOEXPAND_ENABLE
typedef union {
    uint8_t mask;
    struct {
        uint8_t stepper_enable_z :1,
                stepper_enable_y :1,
                mist_on          :1,
                flood_on         :1,
                reserved         :1,
                spindle_dir      :1,
                stepper_enable_x :1,
                spindle_on       :1;
    };
} ioexpand_t;
#endif

