#include "data.hpp"

const char *vertexShaderSrc = R"(
#version 330 core
layout (location = 0) in vec3 aPos;

uniform mat4 model;
uniform mat4 proj;

void main()
{
    gl_Position = proj * model * vec4(aPos.x, aPos.y, aPos.z, 1.0);
}
)";

const char *fragmentShaderSrc = R"(
#version 330 core
out vec4 FragColor;

uniform vec2 resolution;
uniform vec4 bgColor;
uniform vec4 borderColor;
uniform vec2 size;
uniform vec2 origin;
uniform vec4 radius;

float roundedBoxSDF(vec2 CenterPosition, vec2 Size, vec4 Radius)
{
    Radius.xy = (CenterPosition.x > 0.0) ? Radius.xy : Radius.zw;
    Radius.x  = (CenterPosition.y > 0.0) ? Radius.x  : Radius.y;
    
    vec2 q = abs(CenterPosition)-Size+Radius.x;
    return min(max(q.x,q.y),0.0) + length(max(q,0.0)) - Radius.x;
}

void main() {

    // Normalized dimensions (half-width, half-height)
    vec2 halfSize = size * 0.5;

    // Centered coordinates
    vec2 p = origin + vec2(halfSize.x, -halfSize.y);
    
    
    // Calculate distance
    float distance = roundedBoxSDF(gl_FragCoord.xy - p, halfSize, radius);


    // Smooth edges (anti-aliasing)
    float edge = smoothstep(0.5, -0.5, distance);
    
    // Output color
    FragColor = bgColor * vec4(1.0, 1.0, 1.0, edge); // Orange with rounded alpha
}
)";

const float quadVerts[18] = {
    1.0f, 1.0f, 0.0f, // top right
    1.0f, 0.0f, 0.0f, // bottom right
    0.0f, 1.0f, 0.0f, // top left
                      //
    1.0f, 0.0f, 0.0f, // bottom right
    0.0f, 0.0f, 0.0f, // bottom left
    0.0f, 1.0f, 0.0f  // top left
};
