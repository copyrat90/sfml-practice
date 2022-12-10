#version 300 es
precision highp float;

out vec4 fragColor;

uniform sampler2D u_postEffectRequired;
uniform vec2 u_internalResolution;

uniform float u_hazeRadians;

void main()
{
    // gl_FragCoord를 0 ~ 1 범위로 정규화해 UV 좌표 계산
    vec2 uv = gl_FragCoord.xy / u_internalResolution;
    float uvDiffX = 1. / u_internalResolution.x; // UV 좌표 기준 1px

    // 시시각각 달라지는 각도(u_hazeRadians)에 각 Y좌표별 Phase offset을 두어 떨림 구현
    float amplitude = sin(u_hazeRadians + gl_FragCoord.y / 3.);
    float direction = (amplitude > 0.5) ? 1. : (amplitude < -0.5) ? -1. : 0.;

    // `direction` 변수값에 따라 1px 왼쪽 or 1px 오른쪽 or 중앙 픽셀을 읽어 현재 픽셀 색칠
    fragColor = texture(u_postEffectRequired, vec2(uv.x + uvDiffX * direction, uv.y));
}
