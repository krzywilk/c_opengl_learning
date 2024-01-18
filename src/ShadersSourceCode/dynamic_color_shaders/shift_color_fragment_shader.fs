#version 330 core
out vec4 FragColor;  
in vec3 fs_vertexColor;

uniform vec4 color;
  
void main()
{
	vec4 meanVec = vec4((color.x + fs_vertexColor.x), (color.y + fs_vertexColor.y), (color.z + fs_vertexColor.z), color.w); 
    FragColor = meanVec;
}