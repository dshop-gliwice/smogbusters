$fn=64;

wHeight=4; //wall height
wThick=2; //wall thickness
bWidth=10.5; //board width
bHeight=11.8; //board height

module screwMount(){
  difference(){
    cylinder(h = wHeight-1.5,
             d = 6.3,
        center = false);
    cylinder(h = wHeight-1.3,
             d = 3.4,
        center = false);
  } 
}

module spacer(){
  cube([bWidth, 4, wHeight-1.5],false);  
}

module screwMountFill(){
  cylinder(h = wHeight-1.5,
           d = 2,
      center = false);
}

module main(){
  union(){
    //screw mounts
    translate([wThick+2.7, wThick+2.9, 0])
      screwMount();

    //screw mounts connections
    translate([wThick+0.6, wThick+0.4, 0])
      screwMountFill();
        
    //back spacer
    translate([wThick, wThick+4.6, 0])
      spacer();

    //front wall
    translate([0, 0, 0])
      cube([wThick*2+bWidth, wThick, wHeight], false);
    //back wall
    translate([0, wThick+bHeight, 0])
      cube([wThick*2+bWidth, wThick, wHeight], false);

    //side walls
    translate([0, 0, 0])
      cube([wThick, wThick+bHeight, wHeight], false);    
    translate([wThick+bWidth, 0, 0])
      cube([wThick, wThick+bHeight, wHeight], false);
  }  
}


main();

