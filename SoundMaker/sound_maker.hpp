// author: etratipza@gmail.com
// date: 03-17-2018
// inspired by: 
//		http://www.topherlee.com/software/pcm-tut-wavformat.html
//		http://www.cplusplus.com/forum/beginner/166954/

#ifndef SOUND_MAKER_H
#define SOUND_MAKER_H


#include <iostream>
#include <fstream>
#include <string>

constexpr double two_pi = 6.283185307179586476925286766559;
constexpr double max_amplitude = 32760;
constexpr double hz = 44100.0;

class SoundMaker {
	public:
		SoundMaker(std::string file_name);		
		size_t done();
		void add_sample( int channel_1, int channel_2 );
		void GenerateWave( double freq, double amount_time);// 20 < f < 20000 ,0 < t < ( long long / 44100)

	private:
		std::ofstream file;
		size_t set_header( std::ofstream& f );
		size_t header_size; // minus size of data
		size_t size_pos;    // position to insert final file size
		size_t file_size;   // file size
		size_t data_size;   // size of data section
		
		template <typename B>
		std::ostream& put_bits( std::ostream& outs, B value, unsigned bytes = sizeof(B) ) {
			char bits;
			for ( bytes = bytes; bytes > 0; bytes-- ) {
				bits = static_cast<char> (value & 0xFF);
				outs.put( bits );
				value >>= 8; // shift value a byte
			}
			return outs;
		}
};

//extern void generate_data( SoundMaker& S, double freq, double amount_time);

#endif