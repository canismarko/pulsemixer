#include <Wire.h>
#include <Vector.h>
#include "channel.h"

// Define channels and their i2c addresses
#define N_CHANNELS 4
Channel channels[N_CHANNELS];
gpio_bank channelAddrs[] = {0x20, 0x21, 0x22, 0x23};
// channels[0].setAddr(0x20);
// channels[1].setAddr(0x20);
// channels[2].setAddr(0x20);
// channels[3].setAddr(0x20);

// Arduino pins
#define PIN_INT_BTN 2
#define PIN_INT_ROT 3
#define PIN_INT_CH0 7
#define PIN_INT_CH1 6
#define PIN_INT_CH2 5
#define PIN_INT_CH3 4
int channel_pins[] = {PIN_INT_CH0, PIN_INT_CH1, PIN_INT_CH2, PIN_INT_CH3};
#define PIN_PAGE_BTN 9
#define PIN_IO_BTN 10
#define PIN_IO_LED 12
#define PIN_STREAM_DEV_BTN 11
#define PIN_STREAM_DEV_LED 8

// i2c address for GPIO port expanders
#define GPIO_CH0 0x20
#define GPIO_CH1 0x21
#define GPIO_CH2 0x22
#define GPIO_CH3 0x23

#define TICK 1000

// Masks for GPIO pin assignments
#define BTN_MUTE B00000001
#define BTN_VOL  B00000010
#define ROT_VOLB B00100000
#define ROT_VOLA B01000000
#define ROT_VOLS (ROT_VOLA | ROT_VOLB)

// Flag states
#define IN 0
#define OUT 1
#define STREAM 0
#define DEVICE 1

// #define DEBUG

// Variables for tracking rotary encoder
byte volOldPins[] = {0, 0, 0, 0}; // will hold state of pins last time encoder was read

int rotationCounters[] = {0, 0, 0, 0};

// State variables
bool muteButtonsPressed[] = {0, 0, 0, 0};
bool io_flag = OUT;
unsigned int current_page = 0;
bool stream_dev_flag = DEVICE;
byte inputALast = 0;

// Flags for tracking buttons presses, etc
bool page_button_pressed = false;
bool io_button_pressed = false;
bool stream_dev_button_pressed = false;


void attachInterrupts() {
//  attachInterrupt(digitalPinToInterrupt(PIN_INT_ROT), isr_channel_button, FALLING);
  attachInterrupt(digitalPinToInterrupt(PIN_INT_ROT), isr_master_button_and_volume, FALLING);
  attachInterrupt(digitalPinToInterrupt(PIN_INT_BTN), isr_master_button_and_volume, FALLING);
}


void isr_master_button_and_volume() {
  // Serial.println("Vol int called");
  // Master section buttons and volume rotary encoders got mixed together, so sort them out
  if (digitalRead(PIN_PAGE_BTN) == LOW) {
    page_button_pressed = true;
  } else if (digitalRead(PIN_IO_BTN) == LOW) {
    io_button_pressed = true;
  } else if (digitalRead(PIN_STREAM_DEV_BTN) == LOW) {
    stream_dev_button_pressed = true;
  } else {
    // Not any of the master buttons, so it's probably a volume knob
    for (int i_ch=0; i_ch<N_CHANNELS; i_ch++) {
      if (digitalRead(channel_pins[i_ch]) == LOW) {
        channels[i_ch].setInterruptFlag();
      }
    }
  }
}


void updateMasterOutputs() {
  digitalWrite(PIN_IO_LED, io_flag);
  digitalWrite(PIN_STREAM_DEV_LED, stream_dev_flag);  
}


String readSerialLine() {
  String newLine = Serial.readStringUntil('\n');
  return newLine;
}


// This is a reset function to reset the arduino when request by the host
void(* resetFunc) (void) = 0;  // declare reset fuction at address 0

void restart() {
  #ifdef DEBUG
  Serial.println("Resetting device...");
  #endif
  // Clear the outputs during the reset
  channels[0].setShortName("Resettin");
  channels[1].setShortName("g...");
  channels[2].setShortName("Please");
  channels[3].setShortName("wait...");
  for (int i=0; i<N_CHANNELS; i++) {
    channels[i].updateOutputs();
  }
  resetFunc();
}


void updateChannelsFromHost() {
  Serial.print("!REFRESH CHANNELS ");
  Serial.println(N_CHANNELS);
  String line, command, property, shortname, tuplestr, channel_id;
  int segment_start, segment_end=0, name_start, name_end;
  line = readSerialLine();
  #ifdef DEBUG
  Serial.print("Channel list from host: ");
  Serial.println(line);
  #endif
  // Iterate through the channel names returned via serial port
  for (int ch=0; ch < N_CHANNELS; ch++) {
    segment_start = line.indexOf('"', segment_end + 1) + 1;
    segment_end = line.indexOf('"', segment_start);
    tuplestr = line.substring(segment_start, segment_end);
    #ifdef DEBUG
    Serial.print("Tuplestr (");
    Serial.print(segment_start);
    Serial.print("-");
    Serial.print(segment_end);
    Serial.print("): ");
    Serial.println(tuplestr);
    #endif
    // Get the channel number
    channel_id = tuplestr.substring(1, tuplestr.indexOf(','));
    name_start = tuplestr.indexOf("'");
    name_end = tuplestr.indexOf("'", name_start+1);
    shortname = tuplestr.substring(name_start+1, name_end);
    // Set the extracted number and name to the channel
    if (channel_id == "") {
      channels[ch].setID(-1);
    } else {
      channels[ch].setID(channel_id.toInt());
    }
    #ifdef DEBUG
    Serial.print("Found channel ");
    Serial.print(channels[ch].getID());
    Serial.print(": ");
    Serial.println(shortname);
    #endif
    channels[ch].setShortName(shortname);
  }
}


void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);

  // Set up the i2c interface
  Wire.begin();
  
  // Initialize each channel
  for (int ch=0; ch<N_CHANNELS; ch++) {
    channels[ch].setupI2C(channelAddrs[ch]);
  }

  // Attach hardware interrupts to service routines
  pinMode(PIN_INT_ROT, INPUT);
  pinMode(PIN_INT_BTN, INPUT);
  pinMode(PIN_INT_CH0, INPUT);
  pinMode(PIN_INT_CH1, INPUT);
  pinMode(PIN_INT_CH2, INPUT);
  pinMode(PIN_INT_CH3, INPUT);
  pinMode(PIN_PAGE_BTN, INPUT);
  pinMode(PIN_IO_BTN, INPUT);
  pinMode(PIN_IO_LED, OUTPUT);
  pinMode(PIN_STREAM_DEV_BTN, INPUT);
  pinMode(PIN_STREAM_DEV_LED, OUTPUT);
  attachInterrupts();

  // Clear any interrupts from initialization
  for (int ch=0; ch<N_CHANNELS; ch++) {
    channels[ch].readInterruptState();
  }

  // Ask the host for channel names, etc
  updateChannelsFromHost();
  updateMasterOutputs();
}


void check_serial_input() {
  // Get any pending messages
  Serial.setTimeout(100);
  String serial_input = Serial.readStringUntil('\n');
  if (serial_input.length() > 0) {
    Serial.print("Received input: ");
    Serial.println(serial_input);
  }
  // Process the received serial input
  if (serial_input.compareTo(String("?RESET")) == 0) {
    restart();
  }
  // Reset to default serial timeout
  Serial.setTimeout(1000);
}


void loop() {
  // Check for button presses in the master section
  if (page_button_pressed) {
    page_button_pressed = false;
  }
  if (io_button_pressed) {
    io_flag = !io_flag;
    io_button_pressed = false;
    updateMasterOutputs();
  }
  if (stream_dev_button_pressed) {
    stream_dev_flag = !stream_dev_flag;
    stream_dev_button_pressed = false;
    updateMasterOutputs();
  }
  
  // Update each channel
  bool vol_touched = false;
  for (int i_ch=0; i_ch < N_CHANNELS; i_ch++) {
    vol_touched |= channels[i_ch].processInterrupts();
  }
  if (!vol_touched) {
    for (int i_ch=0; i_ch < N_CHANNELS; i_ch++) {
      channels[i_ch].updateOutputs();
    }
  }

  // Respond to serial updates from the host
  check_serial_input();
}
