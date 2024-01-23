#version 330 core
out vec4 FragColor;  
in vec3 fs_vertexColor;
in vec2 fs_texCoord;


uniform vec4 color;
uniform sampler2D texture0;
uniform sampler2D texture1;

  
void main()
{
	vec4 meanVec = vec4((color.x + fs_vertexColor.x), (color.y + fs_vertexColor.y), (color.z + fs_vertexColor.z), color.w); 
    FragColor = mix(texture(texture0, fs_texCoord), texture(texture1, fs_texCoord), 0.2) * meanVec ;  
}