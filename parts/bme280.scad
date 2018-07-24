$fn=64;

sHeight=7.2;

module screwMount(){
  difference(){
      cylinder(h = sHeight-1.5,
           d = 6.3,
           center = false);
      cylinder(h = sHeight-1.3,
           d = 3.4,
           center = false);
  } 
}

module spacer(){
    cube([5.5,4,sHeight-1.5],false);  
}

module screwMountFill(){
    cylinder(h = sHeight-1.5,
           d = 4,
           center = false);
}


module main(){
  union(){
   //screw mounts
   translate([5.4, 5.6, 0])
    screwMount();
   translate([20.6, 5.6, 0])
    screwMount();
    
   //screw mounts connections
   translate([2.9, 3, 0])
    screwMountFill();
   translate([23.1, 3, 0])
    screwMountFill();
    
   //back spacers
   translate([1.2,21,0])
    spacer();
   translate([19,21,0])
    spacer();
    
   //front wall
   translate([0,0,0])
    cube([26,2,sHeight],false);

   //side walls
   translate([0,0,0])
    cube([2,26,sHeight],false);    
   translate([24,0])
    cube([2,26,sHeight],false);
  }  
}


main();

