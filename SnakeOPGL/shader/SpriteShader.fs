#version 330 core

in vec2 texCoords;

out vec4 fragColor;

uniform vec4 aColor;
uniform sampler2D tex;
uniform bool buffed;
uniform bool useTexture;
//uniform 
void main(){
	vec4 color;
	if(useTexture){
		color = texture(tex,texCoords);
		if(buffed && (color.x > 0.1f && color.y > 0.1f && color.z > 0.1f))
			color = aColor;
	}else{
		color = aColor;
	}
	
	fragColor = color;
}