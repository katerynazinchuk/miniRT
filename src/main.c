// when light hits the spot ofr can be connected with the sourse of light only then we use property - colour
// so on the beggining we create an object with all nessesary properties and only that, give permision to use some
//closer the light - brighter the color. and oposite
/*for each pixel,
    color c;
    for each shape in the scene
        send a ray through each pixel and see if it collides with a shape
        if it does
            color = calculate color of ray
        else, color = background color
    return color

To calculate color of ray...
    color c = 0,0,0 // rgb
    for each light source in the scene
        make a new ray (shad_ray) that starts at where the original ray hit the shape...
        ... and ends at the light source
        see if the shadow ray hits a shape on its way to the light
        if it does, 
            calculate ambient color using ambient color of shape material and...
            ... ambient light intensity 
        if not,
            calculate shading with sum of ambient/diffuse/specular components 
*/