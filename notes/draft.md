

**Be carefull with dividing , in case if we get 0 there**

**
# Camera 
we have its position, direction (normalized vector) and angle of view


# Ray

**R(t) = O + t * D**
O - origin
D - normalized vector
t >= ray distance (t is a different dot on ray)

# Objects

## Sphere

we have center
diameter => parser will give us radius because we need r for calculations
color
C - sphere center

**|R(t) - C|^2 = r^2**
(O + t*D - C)^2 = r^2
(O - C + t*D ) * (O - C + t*D) = r^2
(O - C) = k
(k + t*D)^2= r^2
k^2 + 2*t*D *k + (t*D)^2 = r^2
t^2 * D^2 + t * 2 * D *k  + (k^2- r^2) = 0
a = d^2
b = 2 * (D * k)
c = k^2 - r^2
typical quadratic equation
a * t^2 + bt + c = 0
D (discriminant) = b^2 - 4 * a * c
if D (discriminant) < 0 there is no real roots
**t = (−b ± √(b² − 4ac)) / (2a)**

// (a+b)^2 = a^2 + 2ab + b^2

## Plane

P0 - dot on plane
N - plane normal (vector is perpendicular to the plane)
color

P - dot we checking
**N * (P - P0) = 0**
N * (R(t) - P0) = 0
N * (O + t * D - P0) = 0
N * O + t * D * N - N * P0 = 0
t = N * (P0 - O) / D * N
avoid divide by 0 (N * D != 0)
P = R(t) - our intersection



## Cylinder

center
normalized vector of axis of cylinder (the direction along which it is extended // oriented vector)
diameter (? parser will give radius?)
color
for lateral plane
**|(R(t) - C) - ((R(t) - C) * V) * V^2 | = r^2**
distance from ray to cylinder axe equal its radius
V - unit vector along the axis of the cylinder (normalized, |V| = 1)
