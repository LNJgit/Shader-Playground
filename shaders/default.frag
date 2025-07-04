#version 330 core
out vec4 FragColor;

void main() {
    vec2 uv = gl_FragCoord.xy / vec2(800.0, 600.0);
    FragColor = vec4(uv.x, uv.y, 0.5, 1.0);
}
