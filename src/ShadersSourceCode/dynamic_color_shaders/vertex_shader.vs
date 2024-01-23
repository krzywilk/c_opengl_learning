#version 330 core
layout (location = 0) in vec3 aPos;   // the position variable has attribute position 0
layout (location = 1) in vec3 vertexColor; // the color variable has attribute position 1
layout (location = 2) in vec2 aTexCoord;

out vec3 fs_vertexColor; // output a color to the fragment shader
out vec2 fs_texCoord;


void main()
{
    gl_Position = vec4(aPos, 1.0);
    fs_vertexColor = vertexColor; // set ourColor to the input color we got from the vertex data
    fs_texCoord = aTexCoord;

}   