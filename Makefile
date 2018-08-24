sound_maker: 
	g++ example.cpp SoundMaker/sound_maker.cpp -o sound_maker.exe -std=c++11 -g
	
clean:
	rm -rf "sound_maker" *.exe sound_maker
	
