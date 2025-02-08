#version 330 core

in vec2 texCoords;

out vec4 fragColor;

uniform sampler2D tex;

void main(){
	vec4 color = texture(tex,texCoords);
	if(color.x >= 1.0f)
		discard;
	fragColor = color;
}