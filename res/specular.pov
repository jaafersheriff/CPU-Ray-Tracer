// spheres with specular com roughness 0.001ponents

//default camera pointing down negative z
camera {
location  <0, 0, 14>
up        <0,  1,  0>
right     <1.33333, 0,  0>
look_at   <0, 0, 0>
}


light_source {<-100, 100, 100> color rgb <1.5, 1.5, 1.5>}

sphere { <-3.5, -1.4, 0>, 1
  pigment { color rgb <0.1, 0.3, 1.0>}
  finish {ambient 0.2 diffuse 0.4 specular 0.3 roughness 0.25}
}

sphere { <1, -0.8, 0>,1.5
  pigment { color rgb <1.0, 0.2, 0.7>}
  finish {ambient 0.2 diffuse 0.4 specular 0.4 roughness 0.1}
}

sphere { <-2.5, 2.2, -4>,2
  pigment { color rgb <0.2, 0.8, 1.0>}
  finish {ambient 0.2 diffuse 0.4 specular 0.4 roughness 0.1}
}

sphere { <2.8, 1.2, -4>, 2.5
  pigment { color rgb <1.0, 0.7, 0.2>}
  finish {ambient 0.2 diffuse 0.4 specular 0.4 roughness 0.05}
}

sphere { <0, 4, 0>, 1.1
  pigment { color rgb <0.1, 1.0, 0.5>}
  finish {ambient 0.2 diffuse 0.4 specular 0.6 roughness 0.05}
}

plane {<0, 1, 0>, -4
      pigment {color rgb <0.2, 0.6, 0.8>}
      finish {ambient 0.4 diffuse 0.8}
}

