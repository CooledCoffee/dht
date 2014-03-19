all:
	sdcc -mmcs51 --iram-size 256 --xram-size 0 --code-size 8192 --nooverlay --noinduction --verbose --debug -V --std-sdcc89 --model-small example.c
	makebin -p example.ihx example.bin
	echo success

clean:
	rm example.*
