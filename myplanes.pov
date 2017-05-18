// plane test (RIGHT HANDED)

camera {
  location  <0, 0, 16>
  up        <0,  1,  0>
  right     <1.33333, 0,  0>
  look_at   <0, 0, 0>
}

light_source {<1, 1, 1> color rgb <0.7, 0.7, 0.7>}

//right wall - note distance is along normal thus to move right is negative for this normal
plane {<-1, 0, 0>, -6
  pigment {color rgb <0.8, 0.0, 0.0>}
  finish {ambient 0.4 diffuse 0.8, reflection 0.5}
}

//bottom
plane {<0, 1, 0>, -6
  pigment {color rgb <0.0, 0.8, 0.0>}
  finish {ambient 0.4 diffuse 0.8, reflection 0.5}
}

//back
plane {<0, 0, 1>, -6
  pigment {color rgb <0.0, 0.0, 0.8>}
  finish {ambient 0.4 diffuse 0.8, reflection 0.5}
}

//left
plane {<1, 0, 0>, -5
  pigment {color rgbf <0.0, 0.8, 0.8>}
  finish {ambient 0.4 diffuse 0.8, reflection 0.5}
}

sphere { <-2, 1, 2>, 3
  pigment { color rgbf <1.0, 1.0, 1.0, 0.95> }
  finish { ambient 0.02 diffuse 0.4 specular 10.0 roughness 0.03 refraction 1.0 ior 1.02 }
}

sphere { <0, 3, 0>, 1.5
  pigment { color rgb <1.0, 0.0, 1.0> }
  finish { ambient 0.2 diffuse 0.4 specular 10.0}
}

