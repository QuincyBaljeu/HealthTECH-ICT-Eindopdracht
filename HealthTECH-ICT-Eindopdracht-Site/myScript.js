var options = {

    //connection attempt timeout in seconds
    timeout: 3,

    //Gets Called if the connection has successfully been established
    onSuccess: function () {
        alert("Connected");
    },

    //Gets Called if the connection could not be established
    onFailure: function (message) {
        alert("Connection failed: " + message.errorMessage);
    }
  };

  function connect(){
    var mqttBrokerLink = document.getElementById("in_brokerLink").value;
    var mqttBrokerPort = document.getElementById("in_brokerIp").value;
    
    console.log(mqttBrokerLink);
    console.log(mqttBrokerPort);

    client = new Paho.MQTT.Client(mqttBrokerLink, parseInt(mqttBrokerPort), "myclientid_" + parseInt(Math.random() * 100, 10));
   
    client.onMessageArrived = function(message){
        console.log(message);
    }

    client.connect(options);
  }

  function subscribe(){
        var mqttBrokerTopic = document.getElementById("in_brokerTopic").value;

        client.subscribe(mqttBrokerTopic, {qos: 2});
  }