//------------------------------------------------------------------------------
//
// File Name:	Animation.cpp
// Author(s):	Brandon Wolenetz
// Project:		BetaEngine
// Course:		CS230
//
// Copyright © 2019 DigiPen (USA) Corporation.
//
//------------------------------------------------------------------------------

#include "stdafx.h"

#include "Animation.h"

// public funcs

//! Construct a new animation resource.
/*!
  /param name The name of the animation.
  /param spriteSource The sprite source used by this animation.
  /param frameCount The number of frames in this animation.
  /param frameStart The starting frame in the sprite source for this animation.
  /param duration The time that each frame will be displayed.
*/
Animation::Animation(const std::string& name, const SpriteSource* spriteSource, unsigned frameCount, unsigned frameStart, float frameDuration) :
    m_accumulator(0), m_currentVirtualFrame(0), m_name(name), m_spriteSource(spriteSource), m_frameCount(frameCount), m_frameStart(frameStart), m_frameDuration(frameDuration) {

}

//! Reset the current frame to 0 and return the starting frame.
unsigned Animation::Play() const {
    m_currentVirtualFrame = 0;
    m_accumulator = 0;
    return m_frameStart;
}

//! Get the current frame of the animation based on time.
/*!
  /param dt The change in time since the last update.
  /param playbackSpeed How fast the animation is playing (1.0 = normal speed).
  /param loop Whether the animation should loop.
  /param isDone Output param. True if animation is on its last frame, false otherwise.
  /returns The frame in the sprite source for the current frame of the animation.
*/
unsigned Animation::GetCurrentFrameIndex(float dt, float playbackSpeed, bool looping, bool* isDone) const {
    m_currentVirtualFrame = GetVirtualIndex(dt, playbackSpeed);

    if (looping) {
        if (m_currentVirtualFrame > m_frameCount) {
            m_currentVirtualFrame = 0;
        }
    } else {
        if (m_currentVirtualFrame >= m_frameCount) {
            m_currentVirtualFrame = m_frameCount;
        }
    }

    if (isDone != nullptr) {
        *isDone = m_currentVirtualFrame == m_frameCount;
    }

    return m_currentVirtualFrame + m_frameStart;
}

//! Get the name of the animation.
const std::string& Animation::GetName() const {
    return m_name;
}

//! Get the sprite source used by this animation.
const SpriteSource* Animation::GetSpriteSource() const {
    return m_spriteSource;
}

//! set the animations sprite source
/*!
  /parama spriteSource the sprite source to use
*/
void Animation::SetSpriteSource(SpriteSource* spriteSource) {
    m_spriteSource = spriteSource;
}


// private funcs

//! Calculate the current frame in the animation based on the amount of time
//! that has passed.
/*!
  /param dt The change in time since the last update.
  /param playbackSpeed How fast the animation is playing (1.0 = normal speed).
*/
unsigned Animation::GetVirtualIndex(float dt, float playbackSpeed) const {

    m_accumulator += dt * playbackSpeed;

    if (m_frameDuration <= 0) {
        ++m_currentVirtualFrame;
        return m_currentVirtualFrame;
    }

    while (m_accumulator >= m_frameDuration) {
        ++m_currentVirtualFrame;
        m_accumulator -= m_frameDuration;
    }

    return m_currentVirtualFrame;
}