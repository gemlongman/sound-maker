// author: etratipza@gmail.com
// date: 03-17-2018
// inspired by: 
//		http://www.topherlee.com/software/pcm-tut-wavformat.html
//		http://www.cplusplus.com/forum/beginner/166954/

#include <iostream>
#include <fstream>
#include <string>
#include <cmath>
#include "sound_maker.hpp"

SoundMaker::SoundMaker( std::string file_name = "sound.wav" ) {
	this->file.open( file_name, std::ios::binary );
	this->header_size = this->set_header( this->file );
	this->size_pos = 4;
}

size_t SoundMaker::set_header( std::ofstream& f ) {
	f << "RIFF----WAVEfmt ";
	this->put_bits( f,     16, 4 );  // length of format data
	this->put_bits( f,      1, 2 );  // PCM - integer samples
	this->put_bits( f,      2, 2 );  // two channels (stereo file)
	this->put_bits( f,  44100, 4 );  // samples per second (Hz)
	this->put_bits( f, 176400, 4 );  // (Sample Rate * BitsPerSample * Channels) / 8
	this->put_bits( f,      4, 2 );  // bytes needed for 2 channels in one sample
	this->put_bits( f,     16, 2 );  // bits per sample
	f << "data----";	

	return f.tellp();
}


size_t SoundMaker::done() {
	this->file_size = this->file.tellp();
	this->data_size = this->file_size - this->header_size;

	// Write data size in header
	this->file.seekp( this->header_size - 4 );
	this->put_bits( this->file, this->data_size, 4);

	// Write file size in header
	this->file.seekp( this->size_pos );
	this->put_bits( this->file, this->file_size - 8, 4 );	

	this->file.close();
	return this->file_size;	
}


void SoundMaker::add_sample( int channel_1, int channel_2 ) {
	this->put_bits( this->file, channel_1, 2 );
	this->put_bits( this->file, channel_2, 2 );
}


// Function that will convert frequency and time duration into .wav file samples
void SoundMaker::GenerateWave( double freq, double amount_time = 1.0 ) {
	
	double frequency = freq;
	double seconds = amount_time;

	double chan_1 = 0.0; // channel 1
	double chan_2 = 0.0; // channel 2
	
	double amplitude = (double) 32760.0;
	int period;
	frequency == 0.0 ? period = -1 : period = (int) (hz / (2.0 * frequency)) ; // number of samples in a wave length

	double step = max_amplitude / period;

	long long samples = hz * seconds;
	int x;
	double value;

	for ( long long n = 0; n < samples; n++ ) {
		
		chan_2 += step;
		x = n % (2 * period);
		value = sin( ((two_pi * n * frequency)  / hz ));

		// Channel 1 has sine wave
		chan_1 = amplitude * value;

		// Channel 2 will have a half circle wave
		chan_2 = sqrt(  pow(2*32760.0, 2) * (1.0 - ( pow(x - (period) ,2) / pow(period,2))) ) - 32760.0;

		if (frequency == 0.0)
			chan_2 = 0.0;

		this -> add_sample( (int) (chan_1), (int) (chan_2) ); // Add sample to .wav file

	}
}

// Function that will convert frequency and time duration into .wav file samples
// void generate_data( SoundMaker& S, double freq, double amount_time = 1.0 ) {
	
// 	double frequency = freq;
// 	double seconds = amount_time;

// 	double chan_1 = 0.0; // channel 1
// 	double chan_2 = 0.0; // channel 2
	
// 	double amplitude = (double) 32760.0;
// 	int period;
// 	frequency == 0.0 ? period = -1 : period = (int) (hz / (2.0 * frequency)) ; // number of samples in a wave length

// 	double step = max_amplitude / period;

// 	int samples = hz * seconds;
// 	int x;
// 	double value;

// 	for ( int n = 0; n < samples; n++ ) {
		
// 		chan_2 += step;
// 		x = n % (2 * period);
// 		value = sin( ((two_pi * n * frequency)  / hz ));

// 		// Channel 1 has sine wave
// 		chan_1 = amplitude * value;

// 		// Channel 2 will have a half circle wave
// 		chan_2 = sqrt(  pow(2*32760.0, 2) * (1.0 - ( pow(x - (period) ,2) / pow(period,2))) ) - 32760.0;

// 		if (frequency == 0.0)
// 			chan_2 = 0.0;

// 		S.add_sample( (int) (chan_1), (int) (chan_2) ); // Add sample to .wav file

// 	}
// }
