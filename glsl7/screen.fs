#version 330 core
out vec4 FragColor;

in vec2 TexCoords;

uniform sampler2D screenTexture;
const float offset = 1.0 / 20.0;  

void main()
{
    vec2 offsets[9] = vec2[](
        vec2(-offset,  offset), // 左上
        vec2( 0.0f,    offset), // 正上
        vec2( offset,  offset), // 右上
        vec2(-offset,  0.0f),   // 左
        vec2( 0.0f,    0.0f),   // 中
        vec2( offset,  0.0f),   // 右
        vec2(-offset, -offset), // 左下
        vec2( 0.0f,   -offset), // 正下
        vec2( offset, -offset)  // 右下
    );

    vec3 sampleTex[9];
	int num=0;
	vec3 f=vec3(0.0);
    for(int i = 0; i < 9; i++)
    {
        sampleTex[i] = vec3(texture(screenTexture, TexCoords.st + offsets[i]));
		if(sampleTex[i].z<1.0f){
			num++;
			f.x=max(sampleTex[i].x,f.x);
			f.y=max(sampleTex[i].y,f.y);
			f.z=max(sampleTex[i].z,f.z);
		}
    }
    if(num>0&&sampleTex[4].x<1.0){
		FragColor=vec4(f,1.0);
	}else{
		FragColor = texture(screenTexture, TexCoords);
	}
}