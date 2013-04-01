uniform   mat4  MVP;

attribute vec4  aVert;
attribute vec2  aUVs;

varying   vec2  vUVs;

void main(){
    gl_Position = MVP * aVert;
    vUVs = aUVs;
}
