sound_maker: example.cpp sound_maker.cpp sound_maker.hpp
	g++ example.cpp sound_maker.cpp -o sound_maker.exe -std=c++11 -g

clean:
	rm -rf "sound_maker" *.exe sound_maker
	
