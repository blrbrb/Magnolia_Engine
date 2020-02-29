#version 120

vec4 vert_pos;

uniform sampler2D texture;
uniform bool hasTexture;
uniform vec2 light;

void main()
{
 //Ambient lightPos
 vec4 ambient = vec4(0.02, 0.02, 0.02, 1);

 //Convert lightPos to view coords
 vec2 light_tmp =  (gl_ModelViewProjectionMatrix * vec4(light, 0, 1)).xy;

 //Calculate the vector from light to pixel (Make circular)
 vec2 lightToFrag = light_tmp - vert_pos.xy;
    lightToFrag.y = lightToFrag.y;

 //Length of the vector (distance)
 float vecLength = clamp(length(lightToFrag) * 1, 0, 1);

 //lookup the pixel in the texture
 vec4 pixel = texture2D(texture, gl_TexCoord[0].xy);

 //multiply it by the color and lighting
 if(hasTexture == true)
 {
  gl_FragColor = gl_Color * pixel * (clamp(ambient + vec4(1-vecLength, 1-vecLength, 1-vecLength, 1), 0, 1));
 }
 else
 {
  gl_FragColor = gl_Color;
 }
}
