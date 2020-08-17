#version 330 core
out vec4 FragColor;

in vec2 TexCoords;

uniform sampler2D screenTexture;
const float offset = 1.0/1024;  
uniform int uv;
//void main()
//{
//	FragColor = texture(screenTexture, TexCoords);
//}

//∑¥œ‡
//void main()
//{
//	FragColor = vec4(vec3(1.0 - texture(screenTexture, TexCoords)), 1.0);
//}

void main()
{
	FragColor = texture(screenTexture, TexCoords);
	//if(uv==0){
	//	FragColor = vec4(vec3(0.5), 1.0);
	//}else{
	//	FragColor = vec4(vec3(0.0), 1.0);
	//}
	//vec3 col = vec3(texture(screenTexture, TexCoords));
	//if(col.x!=1.0f&&col.y!=1.0f&&col.z!=1.0f){
	//	FragColor = vec4(vec3(1.0 - col), 1.0);
	//}else{
	//	FragColor = texture(screenTexture, TexCoords);
	//}
	
}