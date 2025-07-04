#version 330 core
out vec4 FragColor;

uniform vec2 iResolution;

void main() {
    vec2 uv = gl_FragCoord.xy / iResolution ;
    FragColor = vec4(uv.x, uv.y, 0.5, 1.0);
}
