using UnityEngine;

using NativeWebSocket;
using System.Threading.Tasks;
using UnityEngine.Experimental.GlobalIllumination;
using UnityEngine.UI;
using TMPro;

public class WebSocketClient : MonoBehaviour
{

	private bool isLedOn = false; //Variable to keep track of the LED state

	[SerializeField]
	private Light lightBulbDigitalLight; //Variable to keep track of the Light Bulb Light

	[SerializeField]
	private Light lightBulbAnalogLight; //Variable to keep track of the Light Bulb Light

    [SerializeField]
	private string IPAdress = "10.204.0.6"; //The IP Adress of the Server you want to connect to
    [SerializeField]
	private int Port = 7890; //The Port your WebSocket Connection will "talk" to
    
	private WebSocket webSocket;

	private void initWebSocket() //Starts WebSocket Client Connection
	{
		webSocket = new WebSocket($"ws://{IPAdress}:{Port}");
		//while (webSocket.State == WebSocketState.Connecting) { 
		webSocket.Connect();
			//await Task.Delay(100);
		

		webSocket.OnOpen += WebSocket_OnOpen;
		webSocket.OnError += WebSocket_OnError;
		webSocket.OnClose += WebSocket_OnClose;
		webSocket.OnMessage += WebSocket_OnMessage;

	}

	private void WebSocket_OnOpen() //Alerts on console when WebSocket Connection is Successfull
	{
		Debug.Log("Connecion opened!");
		string message = "Hello from Unity! = Device name: " + SystemInfo.deviceName + " | Device Mac Address: " + SystemInfo.deviceUniqueIdentifier;
		SendWebSocketMessage(message);
	}

	private void WebSocket_OnError(string error) //Alerts on console when WebSocket Connection is Unsuccessfull
	{
		Debug.Log($"Error: {error}");
	}

	private void WebSocket_OnClose(WebSocketCloseCode closeCode) //Alerts on console when WebSocket Connection is Closed
	{
		Debug.Log("Connection closed!");
	}

	private void WebSocket_OnMessage(byte[] data) //Receives webSocket message and handles it respectively depending on what it contains
	{
		string socketMessage = System.Text.Encoding.UTF8.GetString(data);
		//Debug.Log(System.Text.Encoding.UTF8.GetString(data));
		Debug.Log("Received message from server: ");
        Debug.Log(socketMessage);

		if(socketMessage.Contains("Pot value")) { //If the message contains "Potentiometer" it changes the intensity of the light bulb
			string[] splitMessage = socketMessage.Split(':');
			float potentiometerValue = float.Parse(splitMessage[1]);
			lightBulbAnalogLight.intensity = potentiometerValue/10;
		}

		if(socketMessage.Contains("Button Pressed")) { //If the message contains "Button Pressed", turn on or off the light bulb
			//string[] splitMessage = socketMessage.Split(':');
			//float potentiometerValue = float.Parse(splitMessage[1]);
			lightBulbDigitalLight.enabled = !lightBulbDigitalLight.enabled;
		}  

        
	}
	
	
		
	public async void SendWebSocketMessage(string text) //Sends Websocket Message to Server for the ESP32 to receive
	{

		Debug.Log("Sending message to server: " + text);

		if (webSocket.State == WebSocketState.Open)
		{
			// Sending plain text socket
			await webSocket.SendText(text);
		}
	}

	public void turnOnOffLED() //Sends a message to the ESP32 to turn on or off the LED
	{
		if(isLedOn) SendWebSocketMessage("LEDonoff=OFF");
		else SendWebSocketMessage("LEDonoff=ON");
		isLedOn = !isLedOn;
	}
	
	public void changeLEDIntensity(Slider intensity) //Sends a message to the ESP32 to change the intensity of the LED
	{
		string sliderName = intensity.name;
		TextMeshProUGUI sliderText = intensity.GetComponentInChildren<TextMeshProUGUI>();
		string[] splitMessage = sliderName.Split(' ');
		SendWebSocketMessage(splitMessage[0] + "LEDintensity=" + intensity.value);
		sliderText.text = splitMessage[0] + " LED Intensity: " + intensity.value + "%";
		


		// if(sliderName.Contains("Slider")) { //If the message contains "Slider", change the intensity of the light bulb
		// 	string[] splitMessage = socketMessage.Split(':');
		// 	string[] splitMessage2 = splitMessage[1].Split('=');
		// 	string ledColor = splitMessage2[0];
		// 	float ledIntensity = float.Parse(splitMessage2[1]);
		// 	if(ledColor == "Red") 
		// 	if(ledColor == "Green") lightBulbAnalogLight.color = Color.green;
		// 	if(ledColor == "Blue") lightBulbAnalogLight.color = Color.blue;
		// 	lightBulbAnalogLight.intensity = ledIntensity/10;
		// }



	}

	// Start is called before the first frame update
	void Start()
	{
		initWebSocket();
		Debug.Log("Started");
	}

	// Update is called once per frame
	void Update()
	{
		webSocket.DispatchMessageQueue();

    }
	

	private async void OnApplicationQuit() //Closes Websocket Connection Correctly when app is closed
	{
		await webSocket.Close();
	}


	
}


