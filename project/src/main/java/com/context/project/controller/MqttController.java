package com.context.project.controller;

import org.springframework.beans.factory.annotation.Autowired;
import org.springframework.http.ResponseEntity;
import org.springframework.web.bind.annotation.PostMapping;
import org.springframework.web.bind.annotation.RequestBody;
import org.springframework.web.bind.annotation.RestController;

import com.context.project.MqttGateway;
import com.google.gson.Gson;
import com.google.gson.JsonObject;

@RestController
public class MqttController {
	@Autowired
	MqttGateway mqtGateway;
	@PostMapping("/sendMessage")
	public ResponseEntity<?> publish(@RequestBody String mqttMessage){
		
		try {
		JsonObject convertObject = new Gson().fromJson(mqttMessage, JsonObject.class);
		//mqtGateway.senToMqtt(convertObject.get("message").toString(), convertObject.get("topic").toString());
		
		//Ajout pour re4soudre le probleme d'envoie
		String message = convertObject.get("message").getAsString();
        String topic = convertObject.get("topic").getAsString();

        System.out.println("Extracted message: " + message);
        System.out.println("Extracted topic: " + topic);

        mqtGateway.senToMqtt(message, topic);
		
		//fin d'ajout
		
		return ResponseEntity.ok("Success");
		}catch(Exception ex) {
			ex.printStackTrace();
			return ResponseEntity.ok("fail");
		}
	}

}
