precision mediump float;

struct LightData
{
   vec4 ambient;
   vec4 diffuse;
   vec4 specular;
   vec4 position;
   bool enabled;
};
uniform LightData lights[4];

uniform vec4 materialAmbient;
uniform vec4 materialDiffuse;
uniform vec4 materialSpecular;
uniform vec4 materialEmission;
uniform float materialShininess;

varying vec3 position;
varying vec3 normal;
varying vec2 texcoord;

varying vec3 lightDir;
varying vec4 ambient;
varying vec4 diffuse;
varying vec4 specular;

void main()
{
  vec4 color=vec4(0.1,0.1,0.1,1); //global ambient
  vec3 N=normalize(normal);
  vec3 L=normalize(lightDir);
  float NdotL = max(dot(N,L),0.0);

  if (NdotL > 0.0)
  {
    color += (diffuse * NdotL + ambient);
    vec3 halfV = normalize( L + vec3( 0.0, 0.0, 1.0 ) );

    float NdotHV = max(dot(N,halfV),0.0);
    color += specular * pow(NdotHV,materialShininess);
  }

  gl_FragColor = min(color,1.0);
}