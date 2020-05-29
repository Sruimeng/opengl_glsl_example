#version 330 core
out vec4 FragColor;

in vec2 TexCoords;

uniform sampler2D screenTexture;
const float offset = 1.0/1024;  

//void main()
//{
//	FragColor = texture(screenTexture, TexCoords);
//}

//灰度图
//void main()
//{
//	vec3 col = vec3(texture(screenTexture, TexCoords));
//	float average = (col.x+col.y+col.z)/3.0f;
//	FragColor = vec4(average,average,average,1.0);
//}

//加权灰度图
void main()
{
	vec3 col = vec3(texture(screenTexture, TexCoords));
	float average = 0.2126 * FragColor.r + 0.7152 * FragColor.g + 0.0722 * FragColor.b;
	if(col.x!=1.0f&&col.y!=1.0f&&col.z!=1.0f){
		FragColor = vec4(average,average,average,1.0);
	}else{
		FragColor = texture(screenTexture, TexCoords);
	}
	
}