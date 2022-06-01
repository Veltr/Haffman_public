#version 330 core
layout (location = 0) in vec3 aPos;
layout (location = 1) in vec3 aColor;
out vec3 ourColor;
out vec2 fc;

const vec2 res = vec2(800, 600);

uniform float xOffset;

void main(){
    gl_Position = vec4(aPos.x + xOffset, aPos.y, aPos.z, 1.0);
    //ourColor = aColor;
    ourColor = aPos;
    //ourColor = vec3(aPos.x / res.x, aPos.y / res.y, 1.0f);
    //fc = aPos.xz;
}
