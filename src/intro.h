
#define WIN32_LEAN_AND_MEAN
#define WIN32_EXTRA_LEAN

#include <windows.h>
#include <GL/gl.h>
#include "glext.h"
#include "config.h"
#include "shader_code.inl"
#include "4klang.h"
#if defined(DEBUG) || defined(CAPTURE)
#include <iostream>
#include <stdio.h>
#include <sstream>
#include <iomanip>
#endif


#ifdef CAPTURE
static FILE *captureStream;
static GLubyte backbufferData[XRES*YRES * 3];
#endif


#pragma bss_seg(".introBSS")
static GLfloat texData[XRES*YRES * 4];
static GLuint backbufferTex;
static int	pid1, pid2;

#pragma data_seg(".glCreateShaderProgramv")
static const char* sglCreateShaderProgramv = "glCreateShaderProgramv";

#pragma data_seg(".glUseProgram")
static const char* sglUseProgram = "glUseProgram";

#pragma data_seg(".glUniform3f")
static const char* sglUniform3f = "glUniform3f";

#ifdef DEBUG
void initShader(int *pid, const char *fs)
{
	*pid = ((PFNGLCREATESHADERPROGRAMVPROC)wglGetProcAddress(sglCreateShaderProgramv))(GL_FRAGMENT_SHADER, 1, &fs);
	char buff[0xFFFF];
	((PFNGLGETPROGRAMINFOLOGPROC)wglGetProcAddress("glGetProgramInfoLog"))(pid[0], 0xFFFF, NULL, buff);
	printf(buff);
	if (buff) {
		//FILE *log =	fopen("error.log", "w");
		//fputs(buff, log);
		//fclose(log);
	}
}
#else
#pragma code_seg(".initShader")
__forceinline void initShader(int *pid, const char *fs)
{
	*pid = ((PFNGLCREATESHADERPROGRAMVPROC)wglGetProcAddress(sglCreateShaderProgramv))(GL_FRAGMENT_SHADER, 1, &fs);
}
#endif

#ifndef DEBUG
#pragma code_seg(".intro_init")
#endif
__forceinline void intro_init(void)
{
	glGenTextures(1, &backbufferTex);

#ifdef CAPTURE
	std::stringstream args;
	args << "ffmpeg.exe -y -f rawvideo -vcodec rawvideo -s " << XRES << "x" << YRES << " -pix_fmt rgb24 -framerate 60 -i - -c:v libx264 -crf 14 -preset medium -tune film -vf vflip,setpts=N/(62.508*TB) capture_" << XRES << "x" << YRES << ".mp4";
	//old
	//args << "ffmpeg.exe -y -f rawvideo -vcodec rawvideo -s " << XRES << "x" << YRES << " -pix_fmt rgb24 -framerate 60 -i - -c:v libx264 -crf 18 -preset slow -vf vflip capture_" << XRES << "x" << YRES << ".mp4";
	captureStream = _popen(args.str().c_str(), "wb");
#endif

	initShader(&pid1, Intro);
	initShader(&pid2, Intro2);
}

#ifndef DEBUG
#pragma code_seg(".intro_do")
#endif
void intro_do(float tn)
{
	float t = tn;// +48.0f;// +(float)((SAMPLES_PER_TICK * 620)) / 44100.0f;
	//if (tn > 180.0f) t = 0.0f;  //ende :P
	
	((PFNGLUSEPROGRAMPROC)wglGetProcAddress(sglUseProgram))(pid1);
	((PFNGLUNIFORM3FPROC)wglGetProcAddress(sglUniform3f))(0, t, XRES, YRES);
	glRects(-1, -1, 1, 1);


	glBindTexture(GL_TEXTURE_2D, backbufferTex);
	// glReadPixels(0, 0, XRES, YRES, GL_RGBA, GL_FLOAT, texData);
	// glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA32F, XRES, YRES, 0, GL_RGBA, GL_FLOAT, texData);
	glCopyTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA32F, 0, 0, XRES, YRES, 0); // this is new
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP);
	

	((PFNGLUSEPROGRAMPROC)wglGetProcAddress(sglUseProgram))(pid2);
	((PFNGLUNIFORM3FPROC)wglGetProcAddress(sglUniform3f))(0, t, XRES, YRES);
	glRects(-1, -1, 1, 1);


#ifdef CAPTURE
	glReadPixels(0, 0, XRES, YRES, GL_RGB, GL_UNSIGNED_BYTE, backbufferData);
	fwrite(backbufferData, 1, XRES*YRES * 3, captureStream);
	fflush(captureStream);
#endif
}