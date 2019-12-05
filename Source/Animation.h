//------------------------------------------------------------------------------
//
// File Name:	Animation.h
// Author(s):	Brandon Wolenetz
// Project:		BetaEngine
// Course:		CS230
//
// Copyright © 2019 DigiPen (USA) Corporation.
//
//------------------------------------------------------------------------------

#pragma once

class SpriteSource;

class Animation {
public:

    // public funcs

    //! Construct a new animation resource.
    /*!
      /param name The name of the animation.
      /param spriteSource The sprite source used by this animation.
      /param frameCount The number of frames in this animation.
      /param frameStart The starting frame in the sprite source for this animation.
      /param duration The time that each frame will be displayed.
    */
    Animation(const std::string& name = "", const SpriteSource* spriteSource = nullptr, unsigned frameCount = 1, unsigned frameStart = 0, float frameDuration = 0.0f);

    //! Reset the current frame to 0 and return the starting frame.
    unsigned Play() const;

    //! Get the current frame of the animation based on time.
    /*!
      /param dt The change in time since the last update.
      /param playbackSpeed How fast the animation is playing (1.0 = normal speed).
      /param loop Whether the animation should loop.
      /param isDone Output param. True if animation is on its last frame, false otherwise.
      /returns The frame in the sprite source for the current frame of the animation.
    */
    unsigned GetCurrentFrameIndex(float dt, float playbackSpeed, bool looping, bool* isDone = nullptr) const;

    //! Get the name of the animation.
    const std::string& GetName() const;

    //! Get the sprite source used by this animation.
    const SpriteSource* GetSpriteSource() const;

    //! set the animations sprite source
    /*!
      /parama spriteSource the sprite source to use
    */
    void SetSpriteSource(SpriteSource* spriteSource);

private:

    // private funcs

    //! Calculate the current frame in the animation based on the amount of time
    //! that has passed.
    /*!
      /param dt The change in time since the last update.
      /param playbackSpeed How fast the animation is playing (1.0 = normal speed).
    */
    unsigned GetVirtualIndex(float dt, float playbackSpeed) const;


    // private vars

    //! Time accumulated between last call to GetCurrentFrameIndex and current call
    mutable float m_accumulator;

    //! Current frame of the animation (from 0 to frameCount)
    mutable unsigned m_currentVirtualFrame;

    //! The amount of time to display each frame.
    float m_frameDuration;

    //! Animation attributes
    unsigned m_frameCount;
    unsigned m_frameStart;

    //! Name of animation
    std::string m_name;

    //! Sprite source used for this animation.
    const SpriteSource* m_spriteSource;

};