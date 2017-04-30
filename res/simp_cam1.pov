// cs174, assignment 1 sample file (RIGHT HANDED)

//camera pointing down positive x - case 1
camera {
location  <-14, 0,0>
up        <0,  1,  0>
right     <0, 0,  1.3333>
look_at   <0, 0, 0>
}


light_source {<-100, 100, 100> color rgb <1.5, 1.5, 1.5>}

sphere { <-3.5, 0, 0>, 1
  pigment { color rgb <1.0, 0.0, 1.0>}
  finish {ambient 0.2 diffuse 0.4 specular 0.1 roughness 0.1}
}

sphere { <1, 0, 0>,1.5
  pigment { color rgb <0.0, 1.0, 1.0>}
  finish {ambient 0.2 diffuse 0.4 specular 0.1 roughness 0.1}
}

sphere { <-2.5, 0, -4>,2
  pigment { color rgb <1.0, 1.0, 0.0>}
  finish {ambient 0.2 diffuse 0.4 specular 0.1 roughness 0.1}
}

sphere { <2.8, 0, -4>, 2.5
  pigment { color rgb <0.1, 1.0, 0.5>}
  finish {ambient 0.2 diffuse 0.4 specular 0.1 roughness 0.1}
}

sphere { <0, 4, 0>, 1.1
  pigment { color rgb <0.1, 0.1, 1.0>}
  finish {ambient 0.2 diffuse 0.4 specular 0.1 roughness 0.1}
}

plane {<0, 1, 0>, -4
      pigment {color rgb <0.2, 0.6, 0.8>}
      finish {ambient 0.4 diffuse 0.8}
}

