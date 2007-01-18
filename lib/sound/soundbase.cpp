/*
* This file is part of Warzone 2100, an open-source, cross-platform, real-time strategy game
* Copyright (C) 2007  Giel van Schijndel, Warzone Ressurection Project
*
* This program is distributed under the terms of the GNU General Public License as published by
* the Free Software Foundation; either version 2 of the License, or (at your option) any later version.
*
* $Revision$
* $Id$
* $HeadURL$
*/

#include "soundbase.h"

static const float Pi = 3.1415926535897932384626433832795028841971693993751058209749445923078164062862089986280348253421170679;

soundBase::soundBase(bool init) : sndDevice(NULL), sndContext(NULL), sndExtEAX((alIsExtensionPresent("EAX2.0") == AL_TRUE)?true:false)
{
    if ( init )
    {
        // Open the OS's default sound device, if this fails we get a NULL which we can check for on usage
        // OpenAL also ignores NULLs anyway
        sndDevice = alcOpenDevice(NULL);

        if (sndDevice)
        {
            // Create a new rendering context and make it current
            sndContext = alcCreateContext(sndDevice, NULL);
            alcMakeContextCurrent(sndContext);
        }
    }
}

soundBase::~soundBase()
{
    if ( sndDevice != NULL )
    {
        if ( sndContext != NULL )
        {
            alcMakeContextCurrent(NULL);
            alcDestroyContext(sndContext);
            sndContext = NULL;
        }

        alcCloseDevice(sndDevice);
        sndDevice = NULL;
    }

}

void soundBase::setListenerPos(float x, float y, float z)
{
    if (sndContext && sndDevice)
        alListener3f( AL_POSITION, x, y, z );
    // else throw an exception
}

void soundBase::setListenerVel(float x, float y, float z)
{
    if (sndContext && sndDevice)
        alListener3f( AL_VELOCITY, x, y, z );
    // else throw an exception
}

void soundBase::setListenerRot(float pitch, float yaw, float roll)
{
    // TODO: implement some kind of conversion from pitch, yaw and roll to two "at" and "up" vectors
}

void soundBase::updateStreams()
{
    for ( std::map<sndStreamID, std::auto_ptr<soundStream> >::iterator i = sndStreams.begin(); i != sndStreams.end(); i++ )
    {
        (*i).second->update();
    }
}
