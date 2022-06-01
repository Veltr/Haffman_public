#version 330 core
const vec3 camPos = vec3(0., 0., -2.2);

const vec2 iResolution = vec2(1, 1);
const float iTime = 0.f;

in vec2 fc;
out vec4 col;

vec2 intSphere(vec3 ro, vec3 rd, vec3 ce, float ra) {
    vec3 oc = ro - ce;
    float b = dot(oc, rd);
    float c = dot(oc, oc) - ra * ra;
    float h = b*b - c;
    if(h < 0.0) return vec2(-1.0);
    h = sqrt(h);
    return vec2(-b - h, -b + h);
}
vec2 intBox(vec3 ro, vec3 rd, vec3 boxSize, out vec3 outNormal) {
    vec3 m = 1. / rd;
    vec3 n = m * ro;
    vec3 k = abs(m) * boxSize;
    vec3 t1 = -n - k;
    vec3 t2 = -n + k;
    float tN = max(max(t1.x, t1.y), t1.z);
    float tF = min(min(t2.x, t2.y), t2.z);
    if(tN > tF || tF < 0.) return vec2(-1.);
    outNormal = -sign(rd) * step(t1.yzx, t1.xyz) * step(t1.zxy, t1.xyz);
    return vec2(tN, tF);
}

vec3 getDir(vec2 fc) {
    vec2 r = iResolution.xy;
    fc /= r;
    fc -= .5;
    fc.x *= r.x / r.y;
    return normalize(vec3(fc.xy, 1.2));
}
vec3 calcG(vec3 G_l, vec3 p0, vec3 p1, vec3 color, float alpha) {
    float beta = 1. - alpha;
    float leng = length(p1 - p0);
    vec3 a = log(beta) * color;
    float b = -log(beta);
    vec3 c = (a + b * G_l) * exp(-leng * b);
    vec3 G_0 = (c - a) / b;
    return G_0;
}
vec3 calcG_(vec3 G_l, vec3 p0, vec3 p1, vec3 pivot, vec3 size, float alpha) {
    float beta = 1. - alpha;
    vec3 dir = normalize(p1 - p0);
    float leng = length(p1 - p0);
    vec3 K = dir / size;
    vec3 B = (p0 - pivot) / size;
    vec3 a = log(beta) * K;
    vec3 b = log(beta) * B;
    vec3 c = vec3(-log(beta));
    vec3 d = (a + c * (a * leng + b + c * G_l)) / exp(leng * c);
    vec3 G_0 = ((d - a) / c - b) / c;
    return G_0;
}

mat2 rot(float angle) {
    return mat2(cos(angle), sin(angle), -sin(angle), cos(angle));
}
float part(vec2 z) {
    float l = z.x + z.y;
    return l < .5 ? 0. : l < 1. ? 1. : l < 1.5 ? 0. : 1.;
}
vec3 houndstooth(vec2 z) {
    z /= iResolution.y;
    z = mod(z * 10., 2.);
    return vec3(z.x < 1. ? (z.y < 1. ? part(z) : (0.)) : (z.y < 1. ? (1.) : 1.-part(z-1.)));
}

void main() {
    col = vec4(1.0f, 0.0f, 1.0f, 1.0f);
    vec3 background = houndstooth(fc);
    float angle = .2 * iTime;
    vec3 camPos_ = camPos;
    camPos_.zy *= rot(.57);
    camPos_.xz *= rot(angle);

    vec3 dir = getDir(fc);
    dir.zy *= rot(.6);
    dir.xz *= rot(angle);

    vec3 norm;
    vec2 i0 = intBox(camPos_, dir, vec3(.5, .5, .5), norm);
    if(i0.x < 0.) {
        col = vec4(background, 1.0f);
    } else {
        vec3 p0 = camPos_ + dir * i0.x;
        vec3 p1 = camPos_ + dir * i0.y;

        //col = vec4(calcG(background, p0, p1, vec3(1., 0., 0.), .9), 1.);
        vec3 col_ = calcG_(background, p0, p1, vec3(-.5), vec3(1.), .6 + sin(iTime * 2.) * .399);
        col = vec4(col_, 1.0f);
    }
}
