$fn=64;

wHeight=4; //wall height
wThick=2; //wall thickness
bWidth=15.5; //board width
bHeight=11.8; //board height

module screwMount(){
  difference(){
    cylinder(h = wHeight-1.5,
             d = 6.3 ,
        center = false);
    cylinder(h = wHeight-1.3,
             d = 3.4,
        center = false);
  } 
}

module spacer(){
  cube([3, 4, wHeight-1.5], false);  
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
    translate([wThick+2.7+10, wThick+2.9, 0])
      screwMount();
 
   //screw mounts connections
   translate([wThick+0.6, wThick+0.4, 0])
     screwMountFill();
   translate([wThick+2.7+2.1+10, wThick+0.6, 0])
     screwMountFill();
        
   //back spacers
   translate([wThick-0.5, wThick+4.6, 0])
     spacer();
   translate([wThick+bWidth-2.5, wThick+4.6, 0])
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

