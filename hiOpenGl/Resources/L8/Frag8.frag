#version 330 core
out vec4 FragColor;

in vec2 TexCoord;
in vec3 Color;

uniform sampler2D texture1;
uniform sampler2D texture2;
uniform float mixValue;

void main(){
    //FragColor = mix(texture(texture1, TexCoord), texture(texture2, TexCoord), 0.2);
    FragColor = vec4(1.0f, 1.0f, 1.0f, 1.0f);
    //FragColor *= mix(texture(texture1, TexCoord), texture(texture2, TexCoord), mixValue);
    FragColor *= vec4(Color, 1.0f);
}
