#version 440 core
in vec3 ex_Color;

out vec4 color;

void main()
{
	//color = mix(texture(textura1, ex_texCoord), texture(textura2, ex_texCoord), 0.3);
	color = vec4(ex_Color, 1.0f);
}
