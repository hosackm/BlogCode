#include "io.h"
#include "portmidi.h"

#include <stdio.h>

#define BUFFERSIZE 512

#define NOTE_ON 144
#define NOTE_OFF 128

static unsigned int io_initialized = 0;

void midi_init()
{
    if(!io_initialized)
    {
        Pm_Initialize();
        io_initialized = 1;
    }
}

void midi_terminate()
{
    if(io_initialized)
    {
        Pm_Terminate();
        io_initialized = 0;
    }
}

int midi_loop(void* userData)
{
    int i, num_events;
    PmStream *stream;
    PmEvent events[BUFFERSIZE];
    synth s = (synth)userData;

    Pm_OpenInput(&stream, 0, NULL, BUFFERSIZE, NULL, NULL);

    /* Infinite Loop for MIDI */
    for(;;)
    {
        if(Pm_Poll(stream))
        {
            num_events = Pm_Read(stream, events, BUFFERSIZE);
            for(i = 0; i < num_events; ++i)
            {
                PmMessage msg = events[i].message;
                unsigned int key, vel, status;
                key = Pm_MessageData1(msg);
                vel = Pm_MessageData2(msg);
                status = Pm_MessageStatus(msg);

                switch(status)
                {
                case NOTE_ON:
                    synth_add_note(s, key, vel);
                    break;
                case NOTE_OFF:
                default:
                    synth_delete_note(s, key);
                    break;
                }
            }
        }
    }

    Pm_Close(stream);
}

void list_devices()
{
    int i;

    printf("Available Devices\n");
    printf("=================\n");
    for(i = 0; i < Pm_CountDevices(); ++i)
    {
        printf("%s\n%s\n", Pm_GetDeviceInfo(i)->interf, Pm_GetDeviceInfo(i)->name);
    }
}
