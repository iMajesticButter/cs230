//------------------------------------------------------------------------------
//
// File Name:	Animator.h
// Author(s):	Brandon Wolenetz
// Project:		BetaEngine
// Course:		CS230
//
// Copyright © 2019 DigiPen (USA) Corporation.
//
//------------------------------------------------------------------------------

#pragma once


class Sprite;
class Animation;

class Animator {
public:

    //! Construct a new animation controller object.
    Animator(Sprite* sprite_);

    //! Update the animation.
    /*!
      /param dt Change in time (in seconds) since the last game loop.
    */
    void Update(float dt);

    //! Play an animation.
    /*!
      /param animationIndex The index of the animation to play.
      /param laybackSpeed The speed at which to play the animation.
      /param oop Whether the animation should go back to the beginning after it reaches the end.
    */
    void Play(size_t animationIndex = 0, float playbackSpeed = 1.0f, bool loop = false);

    //! Add an animation to the controller.
    /*!
      /param animation The animation resource that will be added to the controller.
      /returns The index of the animation in the controller, for use with the Play function.
    */
    size_t AddAnimation(const Animation* animation);

    //! Get the index of the currently playing animation, for use with the Play function.
    size_t GetCurrentAnimationIndex() const;

    //! Get the index of the animation with the specified name
    /*!
      /param name The name of the animation for which the index was requested.
      /returns The index of the given animation if it was found, or 0.
    */
    size_t GetAnimationIndex(const std::string& name) const;

    //! Determine if the animation has reached the end of its sequence.
    /*!
      /returns True if the animation is done, false otherwise.
    */
    bool IsDone() const;

    //! Set the time to wait between frames for the currently playing animation.
    /*!
      /param duration The amount of time to wait between frames (in seconds).
    */
    void SetPlaybackSpeed(float speed);

private:

    //! The current animation being played.
    size_t m_animationIndex;

    //! How fast animations will play.
    float m_playbackSpeed;

    //! True if the animation is running; false if the animation has stopped.
    bool m_running;

    //! True if the animation loops back to the beginning.
    bool m_looping;

    //! True if the end of the animation has been reached, false otherwise.
    bool m_done;

    //! Components
    Sprite* m_sprite;

    //! List of animations used by this controller
    Beta::Array<const Animation*> m_animationList;

};