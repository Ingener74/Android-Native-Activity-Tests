
uniform mat4 uMVP;
uniform mat4 uModelview;
uniform mat4 uNormal;

struct LightData
{   
   vec4 ambient;
   vec4 diffuse;
   vec4 specular;
   vec4 position;
   bool enabled;
};
uniform LightData lights[4];

uniform vec4  materialAmbient;
uniform vec4  materialDiffuse;
uniform vec4  materialSpecular;
uniform vec4  materialEmission;
uniform float materialShininess;

attribute vec3 aPosition;
attribute vec3 aNormal;
attribute vec2 aTexcoord;

varying vec3 position;
varying vec3 normal;
varying vec2 texcoord;

varying vec3 lightDir;
varying vec4 ambient;
varying vec4 diffuse;
varying vec4 specular;

void main()
{
  vec4 pos=vec4(aPosition,1);
  gl_Position = uMVPMatrix * pos;

  position=(uModelviewMatrix * pos).xyz;
  normal=normalize((uNormalMatrix*vec4(aNormal,1)).xyz);
  texcoord = aTexcoord;

  lightDir=normalize(vec3(lights[0].position)-position);

  ambient=materialAmbient*lights[0].ambient;
  diffuse=materialDiffuse*lights[0].diffuse;
  specular=materialSpecular*lights[0].specular;

}