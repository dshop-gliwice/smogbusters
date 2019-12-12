$fn=64;

sHeight=7.2;
zOffset=0;

module screwMount(){
  difference(){
      cylinder(h = sHeight-1.5,
           d = 6.3  ,
           center = false);
      cylinder(h = sHeight,
           d = 3.4,
           center = false);
  } 
}

module spacer(){
    cube([5.5, 4, sHeight-1.5], false);  
}

module screwMountFill(){
    cylinder(h = sHeight-1.5,
           d = 4,
           center = false);
}


module main(){
  union(){

   //screw mounts
   translate([5.7, 5.9, zOffset])
     screwMount();
   translate([20.8, 5.9, zOffset])
     screwMount();

    //sensor channel
    difference(){
     union(){
       translate([1.2, 11.5, zOffset])
         cube([24,4,sHeight-2.5],false);
       translate([13.5, 13.5, zOffset])
         cylinder(h = sHeight-2.5,
           d = 10  ,
           center = false);
      }
      translate([13.5, 13.5, zOffset])
        cylinder(h = sHeight-1.3,
           d = 5,
           center = false);
    } 


   //screw mounts connections
   translate([3.1, 3.2, zOffset])
    screwMountFill();
   translate([23.4, 3.2, zOffset])
    screwMountFill();
    
   //back spacers
   translate([1.2, 21, zOffset])
    spacer();
   translate([19.5, 21, zOffset])
    spacer();
    
   //front wall
   translate([0, 0, zOffset])
    cube([26,2,sHeight],false);

   //side walls
   translate([0, 0, zOffset])
    cube([2, 26, sHeight],false);    
   translate([24.5, 0, zOffset])
    cube([2, 26, sHeight],false); 
  }  
}


main();

