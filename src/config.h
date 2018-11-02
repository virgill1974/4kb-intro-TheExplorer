

#ifndef _CONFIG_H_
#define _CONFIG_H_

// HACKS - Don't use unless you're really in desperate size problems 
//------------------------------------------------------------------
//#define PFD_HACK
#define WAVHDR_PREPARE_HACK

// FEATURES - Use whenever you can, at the expense of some size
//-------------------------------------------------------------
#define SHADER_WARMUP
#define USE_SOUND_THREAD		// Real time playback (Saves 10 bytes, only multicore cpu)

// CONFIG FLAGS - Change at will
//------------------------------
//#define WINDOWED				// Prevents fullscreen
//#define CAPTURE				// Capture video
//#define CAPTURE_SOUND		// Capture sound

//#define XRES        320		//4:3
//#define YRES        200

//#define XRES        640		//4:3
//#define YRES        480
 
//#define XRES        1024		//4:3
//#define YRES        768

// HD Ready 720p
#define XRES        1280		//16:9
#define YRES        720

//#define XRES		  1280
//#define YRES		  800

//#define XRES		  1680
//#define YRES		  1050

// Full HD 1080p
//#define XRES        1920		//16:9
//#define YRES        1080

// 4k
//#define XRES		3840 
//#define YRES		2160 
#endif

