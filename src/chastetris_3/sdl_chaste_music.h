/*
I don't know what I am doing with this file! The goal is to be able to play music.

The include file at:

/usr/include/SDL2/SDL_mixer.h

Is exceptionally helpful for documentation since it is lacking on the website.

*/



int audio_open = 0;
Mix_Chunk *wave = NULL;

int audio_rate;
Uint16 audio_format;
int audio_channels;
int loops = 0;
int reverse_stereo = 0;
int reverse_sample = 0;



static void CleanUp(int exitcode)
{
    if (wave) {
        Mix_FreeChunk(wave);
        wave = NULL;
    }
    if (audio_open) {
        Mix_CloseAudio();
        audio_open = 0;
    }
    SDL_Quit();

    exit(exitcode);
}




/*
this function is meant to return 0 if everything is fine. Nonzero if any error happens.
*/
int chaste_audio_init()
{
 /* Initialize variables */
 audio_rate = MIX_DEFAULT_FREQUENCY;
 audio_format = MIX_DEFAULT_FORMAT;
 audio_channels = MIX_DEFAULT_CHANNELS;

 /*loops = -1;*/ /*for infinite loop*/
 
     /* Initialize the SDL library */
    if (SDL_Init(SDL_INIT_AUDIO) < 0)
    {
     SDL_Log("Couldn't initialize SDL: %s\n",SDL_GetError());
     return(1);
    }
 
     /* Open the audio device */
    if (Mix_OpenAudio(audio_rate, audio_format, audio_channels, 4096) < 0) {
        SDL_Log("Couldn't open audio: %s\n", SDL_GetError());
        CleanUp(2);
    } else {
        Mix_QuerySpec(&audio_rate, &audio_format, &audio_channels);
        SDL_Log("Opened audio at %d Hz %d bit%s %s", audio_rate,
            (audio_format&0xFF),
            (SDL_AUDIO_ISFLOAT(audio_format) ? " (float)" : ""),
            (audio_channels > 2) ? "surround" :
            (audio_channels > 1) ? "stereo" : "mono");
        if (loops) {
          SDL_Log(" (looping)\n");
        } else {
          putchar('\n');
        }
    }
    audio_open = 1;
 
 
 printf("Audio Initialization successful\n\n");
 return 0;
}

/*load the audio file and return a Mix_Chunk pointer.*/
Mix_Chunk *chaste_audio_load(char *filename)
{
 Mix_Chunk *new_wave = NULL;
 /* Load the requested wave file */
 new_wave = Mix_LoadWAV(filename);
 if (new_wave == NULL)
 {
  SDL_Log("Couldn't load %s: %s\n",filename, SDL_GetError());
  CleanUp(2);
 }

 printf("Audio Loading of %s successful\n",filename);
 return new_wave;
}



int chaste_audio_play(Mix_Chunk *music)
{
 /* Play and then exit */
 Mix_PlayChannel(0,music,loops);

 /*printf("Audio Playback started\n");*/
 return 0;
}

int chaste_audio_stop()
{
 Mix_HaltChannel(0);
 /*printf("Audio Playback stopped\n");*/
 return 0;
}

int still_playing()
{
 return(Mix_Playing(0));
}

/*
 gcc main.c -o main `sdl2-config --cflags --libs` -lSDL2_mixer
 
 
 ./chaste_playwave "Sonic_the_Hedgehog_3_Ice_Cap_Zone_(Pulse_Mix)_OC_ReMix.mp3"
 
*/
