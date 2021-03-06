$(function(){
  $("#status").html("Connecting");

  var lastHorizontalSent = 0;
  var currentHorizontal = 0;

  var lastVerticalSent = 0;
  var currentVertical = 0;

  var lastLaserSent = false;
  var currentLaser = false;

  var lastBananasSent = false;
  var currentBananas = false;

  var deviceId;
  var particle = new Particle();
  var token = "9065cadab38b15148ca87e8710f73cae44859102";

  var devicesPr = particle.listDevices({ auth: token });

  devicesPr.then(
    function(devices){
      console.log('Devices: ', devices);
      for (var i = 0; i < devices.body.length; i++) {
        var device = devices.body[i];
        if(device.name=="coffemaker"){
          console.log("GOT IT");
          console.log(device);
          deviceId = device.id;
          $("#status").html("Connected");
        }
      }
    },
    function(err) {
      console.log('List devices call failed: ', err);
    }
  );


  $("input[id=laser]").on("click",function(){
    currentLaser = ! currentLaser;
    console.log("Laser: "+currentLaser);
  });

  $("input[id=horizontal]").on("mouseup",function(){
    currentHorizontal = parseInt($("input[id=horizontal]").val());
    console.log("Horizontal: "+currentHorizontal);
  });

  $("input[id=vertical]").on("mouseup",function(){
    currentVertical = parseInt($("input[id=vertical]").val());
    console.log("Vertical: "+currentVertical);
  });

  $("input[id=bananas]").on("click",function(){
    currentBananas = ! currentBananas;
    console.log("Bananas: "+currentBananas);
  });

  setInterval(function(){
    if(deviceId){
      $("#status").html("Connected");
      if(currentLaser != lastLaserSent){
        lastLaserSent = currentLaser;
        console.log("send value:"+currentLaser);
        particle.callFunction({ deviceId: deviceId, name: 'setLaser', argument: String(currentLaser), auth: token });
        $("#status").html("Sending");
      }
      if(currentBananas != lastBananasSent){
        lastBananasSent = currentBananas;
        console.log("send value:"+currentBananas);
        particle.callFunction({ deviceId: deviceId, name: 'setGoBananas', argument: String(currentBananas), auth: token });
        $("#status").html("Sending");
      }
      if(currentHorizontal != lastHorizontalSent){
        lastHorizontalSent = currentHorizontal;
        console.log("send value:"+currentHorizontal);
        particle.callFunction({ deviceId: deviceId, name: 'horizontal', argument: String(currentHorizontal), auth: token });
        $("#status").html("Sending");
      }
      if(currentVertical != lastVerticalSent){
        lastVerticalSent = currentVertical;
        console.log("send value:"+currentVertical);
        particle.callFunction({ deviceId: deviceId, name: 'vertical', argument: String(currentVertical), auth: token });
        $("#status").html("Sending");
      }
      if(currentLaser) {
        document.getElementById("laser").style.background='red';
      } else {
        document.getElementById("laser").style.background='#FFFFFF';
      }
      if(currentBananas) {
        document.getElementById("bananas").style.background='yellow';
      } else {
        document.getElementById("bananas").style.background='#FFFFFF';
      }
    }
  },200);
});
