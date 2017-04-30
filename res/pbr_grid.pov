// csc473, assignment 1 sample file (RIGHT HANDED)

camera {
  location  <0, 0, 12>
  up        <0,  1,  0>
  right     <1.33333, 0,  0>
  look_at   <0, 0, 0>
}

light_source {<-100, 100, 100> color rgb <0.75, 0.25, 0.25>}
light_source {<100, 100, 100> color rgb <0.0, 0.4, 0.75>}


// row 0

sphere { <-4, -4, 0>, 0.8
  pigment { color rgb <1.0, 1.0, 1.0>}
  finish {ambient 0.1 diffuse 0.6 specular 0.6 roughness 0.1 metallic 0.1 ior 1.6}
}

sphere { <-2, -4, 0>, 0.8
  pigment { color rgb <1.0, 1.0, 1.0>}
  finish {ambient 0.1 diffuse 0.6 specular 0.6 roughness 0.3 metallic 0.1 ior 1.6}
}

sphere { <0, -4, 0>, 0.8
  pigment { color rgb <1.0, 1.0, 1.0>}
  finish {ambient 0.1 diffuse 0.6 specular 0.6 roughness 0.5 metallic 0.1 ior 1.6}
}

sphere { <2, -4, 0>, 0.8
  pigment { color rgb <1.0, 1.0, 1.0>}
  finish {ambient 0.1 diffuse 0.6 specular 0.6 roughness 0.7 metallic 0.1 ior 1.6}
}

sphere { <4, -4, 0>, 0.8
  pigment { color rgb <1.0, 1.0, 1.0>}
  finish {ambient 0.1 diffuse 0.6 specular 0.6 roughness 0.9 metallic 0.1 ior 1.6}
}


// row 1

sphere { <-4, -2, 0>, 0.8
  pigment { color rgb <1.0, 1.0, 1.0>}
  finish {ambient 0.1 diffuse 0.6 specular 0.6 roughness 0.1 metallic 0.3 ior 1.6}
}

sphere { <-2, -2, 0>, 0.8
  pigment { color rgb <1.0, 1.0, 1.0>}
  finish {ambient 0.1 diffuse 0.6 specular 0.6 roughness 0.3 metallic 0.3 ior 1.6}
}

sphere { <0, -2, 0>, 0.8
  pigment { color rgb <1.0, 1.0, 1.0>}
  finish {ambient 0.1 diffuse 0.6 specular 0.6 roughness 0.5 metallic 0.3 ior 1.6}
}

sphere { <2, -2, 0>, 0.8
  pigment { color rgb <1.0, 1.0, 1.0>}
  finish {ambient 0.1 diffuse 0.6 specular 0.6 roughness 0.7 metallic 0.3 ior 1.6}
}

sphere { <4, -2, 0>, 0.8
  pigment { color rgb <1.0, 1.0, 1.0>}
  finish {ambient 0.1 diffuse 0.6 specular 0.6 roughness 0.9 metallic 0.3 ior 1.6}
}


// row 2

sphere { <-4, 0, 0>, 0.8
  pigment { color rgb <1.0, 1.0, 1.0>}
  finish {ambient 0.1 diffuse 0.6 specular 0.6 roughness 0.1 metallic 0.5 ior 1.6}
}

sphere { <-2, 0, 0>, 0.8
  pigment { color rgb <1.0, 1.0, 1.0>}
  finish {ambient 0.1 diffuse 0.6 specular 0.6 roughness 0.3 metallic 0.5 ior 1.6}
}

sphere { <0, 0, 0>, 0.8
  pigment { color rgb <1.0, 1.0, 1.0>}
  finish {ambient 0.1 diffuse 0.6 specular 0.6 roughness 0.5 metallic 0.5 ior 1.6}
}

sphere { <2, 0, 0>, 0.8
  pigment { color rgb <1.0, 1.0, 1.0>}
  finish {ambient 0.1 diffuse 0.6 specular 0.6 roughness 0.7 metallic 0.5 ior 1.6}
}

sphere { <4, 0, 0>, 0.8
  pigment { color rgb <1.0, 1.0, 1.0>}
  finish {ambient 0.1 diffuse 0.6 specular 0.6 roughness 0.9 metallic 0.5 ior 1.6}
}


// row 3

sphere { <-4, 2, 0>, 0.8
  pigment { color rgb <1.0, 1.0, 1.0>}
  finish {ambient 0.1 diffuse 0.6 specular 0.6 roughness 0.1 metallic 0.7 ior 1.6}
}

sphere { <-2, 2, 0>, 0.8
  pigment { color rgb <1.0, 1.0, 1.0>}
  finish {ambient 0.1 diffuse 0.6 specular 0.6 roughness 0.3 metallic 0.7 ior 1.6}
}

sphere { <0, 2, 0>, 0.8
  pigment { color rgb <1.0, 1.0, 1.0>}
  finish {ambient 0.1 diffuse 0.6 specular 0.6 roughness 0.5 metallic 0.7 ior 1.6}
}

sphere { <2, 2, 0>, 0.8
  pigment { color rgb <1.0, 1.0, 1.0>}
  finish {ambient 0.1 diffuse 0.6 specular 0.6 roughness 0.7 metallic 0.7 ior 1.6}
}

sphere { <4, 2, 0>, 0.8
  pigment { color rgb <1.0, 1.0, 1.0>}
  finish {ambient 0.1 diffuse 0.6 specular 0.6 roughness 0.9 metallic 0.7 ior 1.6}
}


// row 4

sphere { <-4, 4, 0>, 0.8
  pigment { color rgb <1.0, 1.0, 1.0>}
  finish {ambient 0.1 diffuse 0.6 specular 0.6 roughness 0.1 metallic 0.9 ior 1.6}
}

sphere { <-2, 4, 0>, 0.8
  pigment { color rgb <1.0, 1.0, 1.0>}
  finish {ambient 0.1 diffuse 0.6 specular 0.6 roughness 0.3 metallic 0.9 ior 1.6}
}

sphere { <0, 4, 0>, 0.8
  pigment { color rgb <1.0, 1.0, 1.0>}
  finish {ambient 0.1 diffuse 0.6 specular 0.6 roughness 0.5 metallic 0.9 ior 1.6}
}

sphere { <2, 4, 0>, 0.8
  pigment { color rgb <1.0, 1.0, 1.0>}
  finish {ambient 0.1 diffuse 0.6 specular 0.6 roughness 0.7 metallic 0.9 ior 1.6}
}

sphere { <4, 4, 0>, 0.8
  pigment { color rgb <1.0, 1.0, 1.0>}
  finish {ambient 0.1 diffuse 0.6 specular 0.6 roughness 0.9 metallic 0.9 ior 1.6}
}


// plane

plane {<0, 1, 0>, -6
  pigment {color rgb <0.4, 0.2, 0.6>}
  finish {ambient 0.4 diffuse 0.8}
}
