// Pin assignments
#define PIN_VOL_POT_CH0 A0
#define PIN_VOL_POT_CH1 A1
#define PIN_VOL_POT_CH2 A2
#define PIN_VOL_POT_CH3 A3

#define n_channels 3
#define n_pins 4
int pins_mute_btn[n_pins] = {12, 10, 11, 13};
int pins_mute_led[n_pins] = {7, 2, 3, 5};
int pins_vol_pot[n_pins] = {A1, A5, A4, A2};

#define BTN_DOWN LOW
#define BTN_UP HIGH

#define TRUE 1
#define FALSE 0

// Status variables
unsigned int channel_is_muted[n_pins] = {1, 1, 1, 1}; // Defaults get updated once computer is connected
int current_vols[n_pins] = {-1, -1, -1, -1}; // -1 means it will always report a new value on boot
int refresh_requested = FALSE;


void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
  // Set read/write mode on each pin
  for (int p=0; p<n_pins; p++) {
    pinMode(pins_mute_btn[p], INPUT);
    pinMode(pins_mute_led[p], OUTPUT);
    pinMode(pins_vol_pot[p], INPUT);
  }
  // Get the loop to request a state update from the host
  refresh_requested = TRUE;
}


void set_mute_leds() {
  for (int ch=0; ch<n_channels; ch++) {
    if (channel_is_muted[ch]) {
      digitalWrite(pins_mute_led[ch], HIGH);
    } else {
      digitalWrite(pins_mute_led[ch], LOW);
    }
  }
}


void toggle_mute(int channel) {
  Serial.print("MUTE CH");
  Serial.print(channel);
  Serial.print(" ");
  if (channel_is_muted[channel]) {
    channel_is_muted[channel] = FALSE;
  } else {
    channel_is_muted[channel] = TRUE;
  }
  Serial.println(channel_is_muted[channel]);
  // Refresh the mute LED states
  set_mute_leds();
}


void check_volume_pots() {
  int new_vol;
  for (int ch=0; ch<n_channels; ch++) {
    new_vol = analogRead(pins_vol_pot[ch]) / 1023.0 * 100;
    new_vol = new_vol / 5 * 5; // Round to the nearest 3
    if (new_vol != current_vols[ch]) {
      current_vols[ch] = new_vol;
      Serial.print("VOLUME CH");
      Serial.print(ch);
      Serial.print(" ");
      Serial.println(current_vols[ch]);
    }
  }
}


void loop() {
  // put your main code here, to run repeatedly:

  // Check if we need to request new data from the host
  if (refresh_requested) {
    Serial.println("REFRESH");
    refresh_requested = FALSE;
  }

  // Check for states coming in on the serial connectio
  if (Serial.available()) {
    String command = Serial.readStringUntil('\n');
    if (command.substring(0, 4) == "MUTE") {
      int channel = command.substring(7, 8).toInt();
      int new_state = command.substring(9, 10).toInt();
      channel_is_muted[channel] = new_state;
    }
    set_mute_leds();
  }

  // Check if a button was pressed
  for (int p=0; p<n_channels; p++) { 
    if (digitalRead(pins_mute_btn[p]) == BTN_DOWN) {
      toggle_mute(p);
      set_mute_leds();
      // Block until the switch is released
      while (digitalRead(pins_mute_btn[p]) == BTN_DOWN) {
      }
    }
  }
  
  // Check if the volume pot has changed
  check_volume_pots();
}
