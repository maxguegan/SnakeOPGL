#version 330 core

in vec2 texCoords;

out vec4 fragColor;

uniform sampler2D tex;

void main(){
	vec4 color = texture(tex,texCoords);
	if(color.x >= 0.8f && color.y >= 0.8f && color.z >= 0.8f)
	 discard;
	fragColor = color;
}