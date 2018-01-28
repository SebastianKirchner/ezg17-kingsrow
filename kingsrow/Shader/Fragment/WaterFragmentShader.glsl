#version 330 core

in vec4 clipSpace;
in vec2 texCoords;
in vec3 P;

out vec4 out_color;

// Values that stay constant for the whole mesh.
uniform sampler2D reflectionTexture;
uniform sampler2D refractionTexture;
uniform sampler2D dudvMap;
uniform sampler2D normalMap;

uniform float amplitude;
uniform float speed;
uniform vec3 cameraPos;
uniform vec3 lightPos;

void main()
{

	float slowspeed = speed / 15.0;
    vec3 lightDir = normalize(P - lightPos.xyz);
    vec3 viewDir = normalize(cameraPos.xyz - P);
	
	vec3 lightColor = vec3(1.0,1.0,1.0);
	vec2 normCoords = clipSpace.xy/clipSpace.w;
	vec2 ndc = normCoords/2.0 + 0.5;
	vec2 refractTexCoords = vec2(ndc.x, ndc.y);
	vec2 reflectTexCoords = vec2(ndc.x, -ndc.y);

	vec2 dist = texture(dudvMap, vec2(texCoords.x + slowspeed, texCoords.y)).rg*0.001;
	dist = texCoords + vec2(dist.x, dist.y + slowspeed);
	vec2 totalDist = (texture(dudvMap, dist).rg * 2.0 -1.0)*0.005;

	reflectTexCoords += totalDist;
	refractTexCoords += totalDist;
	
	reflectTexCoords.x = clamp(reflectTexCoords.x, 0.000001, 0.999999);
	reflectTexCoords.y = clamp(reflectTexCoords.y, -0.999999, -0.000001);
    
	refractTexCoords = clamp(refractTexCoords, 0.000001, 0.999999);

	vec4 reflectCol = texture(reflectionTexture, reflectTexCoords);
	vec4 blue = vec4(0,0,0.2,0.3);
	vec4 refractCol = texture(refractionTexture, refractTexCoords);

	float refractFactor = max(dot(viewDir, vec3(0,1,0)), 0);

	vec4 normalMapCol = texture(normalMap, dist);
	vec3 normal = vec3(normalMapCol.r *2.0 - 1.0, normalMapCol.b, normalMapCol.g * 2.0 -1.0);
	normal = normalize(normal);

	vec3 reflectLight = reflect(normalize(lightDir), normal);
	float specular = max(dot(reflectLight, viewDir), 0.0);
	specular = pow(specular, 20);
	vec3 highlights = lightColor * specular * 0.4;

    out_color = mix(reflectCol, refractCol, 0.6) + vec4(highlights, 0.0);
	out_color = mix(out_color, blue, 0.1);
} 

