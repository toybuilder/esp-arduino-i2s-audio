#include <ESP_I2S.h>
// Simple example to play an MP3 audio
// Using Arduino esp32 support version 3.0.5

// ESP-I2S support:
// see https://docs.espressif.com/projects/arduino-esp32/en/latest/api/i2s.html#sample-code
// see source at https://github.com/espressif/arduino-esp32/tree/master/libraries/ESP_I2S/src
I2SClass I2S;



// Using Arduino INCBIN library to embed the MP3 file
// See INCBIN documentation about the location of the audio file. https://reference.arduino.cc/reference/en/libraries/incbin/
// Easiest is to use absolute path for the audio filename
#include "incbin.h"
//INCBIN (Sound,"nogood.mp3"); // replace filename with your MP3 file
//INCBIN (Sound,"good.mp3"); // replace filename with your MP3 file
INCBIN (Sound,"good2.mp3"); // replace filename with your MP3 file

// Note: Not all mp3 files work.  Specifically, MP3 recorded using Windows Sound Recorder would not play in my testing.
// Also, be careful about the size of the sound file, as it will take space out of the heap to store the data
// These short sound files were tested and worked:
// https://pixabay.com/users/brvhrtz-33128829/ stab-f-01-brvhrtz-224599.mp3
// https://pixabay.com/users/ribhavagrawal-39286533/  coin-recieved-230517.mp3
// nogood.mp3 is an example of a MP3 file that DOES NOT work

// nogood.mp3 was recorded using Windows Sound Recorder.
// good.mp3 is a re-encoding done by https://restream.io/tools/mp3-converter -- that works.
// good2.mp3 is nogood.mp3 after its ID3 tag (and any other properties) removed per https://www.frightideas.com/blog/post/removing-id3-tags

// Filed https://github.com/espressif/arduino-esp32/issues/10469

void play_audio() {
  I2S.setPins(23, 4, 33, -1, -1); //SCK, WS, SDOUT, SDIN, MCLK
  I2S.begin(I2S_MODE_STD, 16000, I2S_DATA_BIT_WIDTH_16BIT, I2S_SLOT_MODE_STEREO);
  I2S.playMP3((uint8_t*)gSoundData,gSoundSize);
  I2S.end();
}
