#version 330 core

in vec4 clipSpace;
in vec2 texCoords;

out vec4 out_color;

// Values that stay constant for the whole mesh.
uniform sampler2D reflectionTexture;
uniform sampler2D refractionTexture;
uniform sampler2D dudvMap;

uniform float amplitude;
uniform float speed;

void main()
{
	vec2 ndc = (clipSpace.xy/clipSpace.w)/2.0 + 0.5;
	vec2 refractTexCoords = vec2(ndc.x, ndc.y);
	vec2 reflectTexCoords = vec2(ndc.x, -ndc.y);

	vec2 dist1 = (texture(dudvMap, vec2(texCoords.x, texCoords.y+speed)).rg * 2.0 -1.0) * 0.009f;
	vec2 dist2 = (texture(dudvMap, vec2(-texCoords.x + speed, texCoords.y)).rg * 2.0 -1.0) * 0.009f;
	vec2 totalDist = dist1+dist2;

	reflectTexCoords += totalDist;
	refractTexCoords += totalDist;
	
	reflectTexCoords.x = clamp(reflectTexCoords.x, 0.01, 0.99);
	reflectTexCoords.y = clamp(reflectTexCoords.y, -0.99, -0.01);
    
	refractTexCoords = clamp(refractTexCoords, 0.01, 0.99);

	vec4 reflectCol = texture(reflectionTexture, reflectTexCoords);
	vec4 blue = vec4(0,0,0.2,0.3);
	vec4 refractCol = texture(refractionTexture, refractTexCoords);

    out_color = mix(reflectCol, refractCol, 0.5);
	out_color = mix(out_color, blue, 0.1);
} 

