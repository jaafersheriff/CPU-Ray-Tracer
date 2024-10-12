camera {
  location  <0, 0, 20>
  up        <0,  1,  0>
  right     <1.33333, 0,  0>
  look_at   <0, 0, 0>
}


light_source {<-1, 100, 1> color rgb <3.5, 3.5, 3.5>}

sphere { <0, 0, 3>, 3
  pigment { color rgbf <1.0, 1.0, 1.0, 0.95> }
  finish { ambient 0.02 diffuse 0.4 specular 10.0 roughness 0.03 refraction 1.0 ior 1.02 }
  scale <1.0, 1.5, 1.0>
}

sphere { <1, 0, -5>, 3
  pigment { color rgbf <1.0, 1.0, 1.0, 0.95>}
  finish { ambient 0.02 diffuse 0.4 specular 10.0 roughness 0.03 refraction 1.0 ior 1.15 }
  scale <2.5, 1, 1>
}

sphere { <2, 5, -10>, 3
  pigment { color rgb <1.0, 0.0, 0.0>}
  finish { ambient 0.02 diffuse 0.4 specular 10.0 reflection 0.1}
}


plane {<0, 1, 0>, -8
  pigment { color rgb <0.4, 0.4, 0.4> }
  finish { ambient 0.4 diffuse 0.8 reflection 0.8}
}

plane {<1, 0, 0>, -15
	pigment { color rgb <0.0, 1.0, 0.0> }
	finish {ambient 0.4 diffuse 0.8 reflection 0.6}
}

plane {<-1, 0, 0>, -15
	pigment { color rgb <0, 0, 1.0> }
	finish {ambient 0.4 diffuse 0.8 reflection 0.6}
}

plane {<0, 0, 1>, -15
	pigment { color rgb <1.0 0.0 1.0> }
	finish {ambient 0.4 diffuse 0.8 reflection 0.6}
}
