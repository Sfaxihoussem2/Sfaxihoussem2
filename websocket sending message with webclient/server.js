// if use a public server change the port of your server 
// if use a public server secure change 'ws' with 'wss'
const WebSocket = require('ws');

// Create a WebSocket server instance
const wss = new WebSocket.Server({ port: 8080 });

// Handle incoming connections
wss.on('connection', (ws) => {
  console.log('Client connected');

  // Handle messages from the client
  ws.on('message', (message) => {
    console.log(`Received message: ${message}`);

    // Broadcast the message to all connected clients
    wss.clients.forEach((client) => {
      if (client.readyState === WebSocket.OPEN) {
        client.send(message);
      }
    });
  });

  // Handle disconnections
  ws.on('close', () => {
    console.log('Client disconnected');
  });
});