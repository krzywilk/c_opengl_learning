#version 330 core
out vec4 FragColor;  
in vec2 fs_texCoord;


uniform vec4 color;
uniform sampler2D texture0;
uniform sampler2D texture1;

  
void main()
{
	vec4 meanVec = color; 
    FragColor = mix(texture(texture0, fs_texCoord), texture(texture1, fs_texCoord), 0.2) + meanVec ;  
}