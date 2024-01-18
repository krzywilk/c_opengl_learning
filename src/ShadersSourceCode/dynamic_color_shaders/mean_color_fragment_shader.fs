#version 330 core
out vec4 FragColor;  
in vec3 fs_vertexColor;

uniform vec4 color;
  
void main()
{
	vec4 meanVec = vec4((color.x + fs_vertexColor.x)/2, (color.y + fs_vertexColor.y)/2, (color.z + fs_vertexColor.z)/2, color.w); 
    FragColor = meanVec;
}