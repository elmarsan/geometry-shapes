#pragma once

#include "math.h"

enum Camera_Movement
{
    FORWARD,
    BACKWARD,
    LEFT,
    RIGHT
};

// Default camera values
const float YAW = -90.0f;
const float PITCH = 0.0f;
const float SPEED = 5.5f;
const float SENSITIVITY = 1.0f;
const float ZOOM = 90.0f;

class Camera
{
   public:
    // camera Attributes
    vec3 Position;
    vec3 Front;
    vec3 Up;
    vec3 Right;
    vec3 WorldUp;
    
    // euler Angles
    float Yaw;
    float Pitch;

    // camera options
    float MovementSpeed;
    float MouseSensitivity;
    float Zoom;

    // constructor with vectors
    Camera(vec3 position = vec3{0.0f, 0.0f, 0.0f}, vec3 up = vec3{0.0f, 1.0f, 0.0f}, float yaw = YAW,
           float pitch = PITCH)
        : Front(vec3(0.0f, 0.0f, -1.0f)), MovementSpeed(SPEED), MouseSensitivity(SENSITIVITY), Zoom(ZOOM)
    {
        Position = position;
        WorldUp = up;
        Yaw = yaw;
        Pitch = pitch;
        Update();
    }

    // returns the view matrix calculated using Euler Angles and the LookAt Matrix
    mat4 GetViewMatrix() { return lookAt(Position, Position + Front, Up); }

    void Move(Camera_Movement direction, float deltaTime)
    {
        float velocity = MovementSpeed * deltaTime;
        if (direction == FORWARD)
            Position += Front * velocity;
        if (direction == BACKWARD)
            Position -= Front * velocity;
        if (direction == LEFT)
            Position -= Right * velocity;
        if (direction == RIGHT)
            Position += Right * velocity;
    }

    void SetEulerAngles(float xoffset, float yoffset, bool constrainPitch = true)
    {
        xoffset *= MouseSensitivity;
        yoffset *= MouseSensitivity;

        Yaw += xoffset;
        Pitch += yoffset;

        // make sure that when pitch is out of bounds, screen doesn't get flipped
        if (constrainPitch)
        {
            if (Pitch > 89.0f)
                Pitch = 89.0f;
            if (Pitch < -89.0f)
                Pitch = -89.0f;
        }

        // update Front, Right and Up Vectors using the updated Euler angles
        Update();
    }

    void SetZoom(float yoffset)
    {
        Zoom -= (float)yoffset;
        if (Zoom < 1.0f)
            Zoom = 1.0f;
        if (Zoom > 45.0f)
            Zoom = 45.0f;
    }

    // calculates the front vector from the Camera's (updated) Euler Angles
    void Update()
    {
        vec3 front{
            cos(radians(Yaw)) * cos(radians(Pitch)),
            sin(radians(Pitch)),
            sin(radians(Yaw)) * cos(radians(Pitch)),
        };

        Front = front.normalize();
        Right = front.cross(WorldUp).normalize();
        Up = Right.cross(Front).normalize();
    }
};
