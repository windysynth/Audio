/* Audio Library for Teensy 3.X
 * Copyright (c) 2014, Paul Stoffregen, paul@pjrc.com
 *
 * Development of this audio library was funded by PJRC.COM, LLC by sales of
 * Teensy and Audio Adaptor boards.  Please support PJRC's efforts to develop
 * open source software by purchasing Teensy or other PJRC products.
 *
 * Permission is hereby granted, free of charge, to any person obtaining a copy
 * of this software and associated documentation files (the "Software"), to deal
 * in the Software without restriction, including without limitation the rights
 * to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
 * copies of the Software, and to permit persons to whom the Software is
 * furnished to do so, subject to the following conditions:
 *
 * The above copyright notice, development funding notice, and this permission
 * notice shall be included in all copies or substantial portions of the Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 * IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 * FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
 * AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 * LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
 * OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN
 * THE SOFTWARE.
 */

#ifndef filter_onepole_h_
#define filter_onepole_h_

#include <Arduino.h>     // github.com/PaulStoffregen/cores/blob/master/teensy4/Arduino.h
#include <AudioStream.h> // github.com/PaulStoffregen/cores/blob/master/teensy4/AudioStream.h

class AudioFilterOnepole : public AudioStream
{
public:
	AudioFilterOnepole(void) : AudioStream(1, inputQueueArray) {
		// by default, the filter will pass everything
        frequency(20000.0);
        highpassOn(false);
	}
	virtual void update(void);
    void frequency(float freq){
        if (freq < 1.0f) {freq = 1.0f;}
        else if ( freq > AUDIO_SAMPLE_RATE_EXACT/2.1f ) {freq = AUDIO_SAMPLE_RATE_EXACT/2.1f;}
        // k = 1-e^(-2*pi*Fc/Fs)
        k = 1.0f-exp(freq * (-2.0f*3.141592654f/AUDIO_SAMPLE_RATE_EXACT) );
    }
    void highpassOn(bool hpOn){
       highpass_on = hpOn; 
    }

private:
	audio_block_t *inputQueueArray[1];
    float k;
    bool highpass_on;
    float accum;
};

#endif
