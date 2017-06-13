// csc473, assignment 1 sample file (RIGHT HANDED)

camera {
  location  <0, 1, 18>
  up        <0,  1,  0>
  right     <1.33333, 0,  0>
  look_at   <0, 0, 0>
}


light_source {<4.9, 4.9, 10> color rgb <1.0, 1.0, 1.0>}


// globe
sphere { <2.5, -2.15, 3>, 2.2
  pigment { color rgb <1.0, 0.0, 1.0>}
  finish {ambient 0.2 diffuse 0.8 specular 0.5 roughness 0.6 }
  texture world.bmp
}

sphere { <-2.5, -2.15, 3>, 2.2
  pigment { color rgb <1.0, 0.0, 1.0>}
  finish {ambient 0.2 diffuse 0.8 specular 0.5 roughness 0.6}
  translate <0, 0, 0>
  texture checkerboard.bmp
}

sphere {<0, 2, -3> 3
   pigment { color rgb <1, 1, 1> }
   finish {ambient 0.2 diffuse 0.8 roughness 0.02 reflection 0.7 }
}

// Floor
plane {<0, 1, 0>, -5
  pigment {color rgb <1.0, 1.0, 1.0>}
  finish {ambient 0.4 diffuse 1.0 reflection 0.7}
}

// Background
plane {<0, 0, 1>, -5
  pigment {color rgb <1.0, 1.0, 1.0>}
  finish {ambient 0.4 diffuse 1.0 reflection 0.7}
}


// Background
plane {<-1, 0, 0>, -5
  pigment {color rgb <1.0, 1.0, 1.0>}
  finish {ambient 0.4 diffuse 1.0 reflection 0.7}
}


// Background
plane {<0, -1, 0>, -5
  pigment {color rgb <1.0, 1.0, 1.0>}
  finish {ambient 0.4 diffuse 1.0 reflection 0.7}
}

// Background
plane {<1, 0, 0>, -5
  pigment {color rgb <1.0, 1.0, 1.0>}
  finish {ambient 0.4 diffuse 1.0 reflection 0.7}
}


